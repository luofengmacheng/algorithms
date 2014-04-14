/*
 * author:	luo feng
 * date:	2014/4/2 - 2014/4/14
 * title:	Red Black Tree
 * language:	C++
 * info:	2014/4/8 insert
 * 		2014/4/9 predecessor, successor
 *		2014/4/11 erase(not yet)
 *		2014/4/13 test this program
 * problem:	
 * bug 1:   在对树进行调整时（rbt_insert_fixup），由于调整时可能会涉及到根节点，但是修改过程中并没有判断根节点，
 *          因此，可能会出现根节点还是指向原来所指的节点，但是树的根已经改变了，导致遍历整个树时节点丢失和内存泄漏。
 *          比如：              5(BLACK)
 * 		               /
 *                       (RED)4
 *                           /
 *                     (RED)3
 *          当插入5，4，3之后，树的结构如上图，此时，pnode指向节点3，而且需要对pnode->parent->parent进行右单旋转操作，但是如果进行这样的操作之后：
 *          pnode = pnode->parent->parent;
 *          right_rotate(pnode);
 *          pnode所指向的树确实变成了希望的那样，但是，此时指向根节点的指针_rbt还是指向节点5，但是，实际应该指向4，
 *          因此，这里进行旋转操作时应该判断pnode->parent->parent是否等于_rbt，然后对_rbt进行相应的修改。
 *          或者如SGI STL中在根节点的上面再设置一个节点，那么此时就不需要判断了，但是这样依旧会引发bug 2。
 *
 * bug 2:   在对某个子树进行旋转时（left_rotate or right_rotate or double rotate），由于是用临时节点来依次往上进行调整，
 *          因此，在旋转时使用的临时节点进行旋转，但是，并没有修改当前子树根节点的父节点的子树指针，因此，这棵树有可能已经不能如预期一样了。
 *          比如：
 *			        4(BLACK)
 * 		               / \
 *                     (BLACK)3   5(BLACK)
 *                                 \
 *                                  8(RED)
 *                                 /
 *                                7(RED)
 *          对于上面的树，当前pnode指向节点7，那么就需要进行调整，而且先要对节点8进行右单旋转操作：
 *          pnode = pnode->parent;
 *          right_rotate(pnode);
 *          此时，pnode指向节点7，但是，从当前的right_rotate代码中可以看到，它修改了7的父节点的指针，没有修改7的父节点的子指针
 *          因此，这里相当就形成了一个环路，节点7的父指针指向节点5。
 *          这里的根本问题就在旋转函数，旋转函数在旋转的时候，需要改变父节点的子指针，之前使用的旋转函数拷贝的avl的代码，
 *          但是，那个程序中没有修改父节点的子指针，使用的是递归，没有该问题，这里是从下往上走，因此，会造成该问题。
 *
 * 声明：   本程序没有进行严格的测试，因此，不能保证所有的测试用例都能够正常运行。
 */

#include <iostream>
#include <utility>
#include <vector>
#include <iterator>
using namespace std;

enum COLOR {
	RED, BLACK
};

//红黑树的前向声明，主要是为了将红黑树设定为迭代器的友元，使其可以访问迭代器的私有成员
template < typename K, typename V >
class red_black_tree;

template < typename K, typename V >
struct rbt_node_base {
	pair<K, V> data;
	rbt_node_base *left, *right, *parent;
	COLOR color;

	rbt_node_base(K k, V v) : left(NULL), right(NULL), parent(NULL)
	{
		data.first = k;
		data.second = v;
		color = RED;
	}
	K key()
	{
		return data.first;
	}
	V& value()
	{
		return data.second;
	}
};

template < typename K, typename V >
static rbt_node_base<K, V> *predecessor(rbt_node_base<K, V> *pnode)
{
	if(pnode == NULL) {
		return NULL;
	}

	if(pnode->left) {
		rbt_node_base<K, V> *qnode = pnode->left;
		while(qnode->right) {
			qnode = qnode->right;
		}
		return qnode;
	}
	else {
		while(pnode->parent && pnode == pnode->parent->left) {
			pnode = pnode->parent;
		}
		return pnode->parent;
	}
	return NULL;
}

template < typename K, typename V >
rbt_node_base<K, V> *successor(rbt_node_base<K, V> *pnode)
{
	if(pnode == NULL) {
		return NULL;
	}

	if(pnode->right) {
		rbt_node_base<K, V> *qnode = pnode->right;
		while(qnode->left) {
			qnode = qnode->left;
		}
		return qnode;
	}
	else {
		while(pnode->parent && pnode == pnode->parent->right) {
			pnode = pnode->parent;
		}
		return pnode->parent;
	}
	return NULL;
}

template < typename K, typename V >
class rbt_iterator {
	rbt_node_base<K, V> *cur;
	typedef rbt_node_base<K, V> rbt_node;

public:
	friend red_black_tree<K, V>;
	typedef pair<K, V> value_type;
	typedef value_type *pointer;
	typedef value_type &reference;
	rbt_iterator& operator++();
	const rbt_iterator operator++(int);
	rbt_iterator& operator--();
	const rbt_iterator operator--(int);

	bool operator==(const rbt_iterator&);
	bool operator!=(const rbt_iterator&);
	reference operator*();
	pointer operator->();
};

template < typename K, typename V >
rbt_iterator<K, V>& rbt_iterator<K, V>::operator++()
{
	cur = successor(cur);

	return *this;
}

template < typename K, typename V >
const rbt_iterator<K, V> rbt_iterator<K, V>::operator++(int)
{
	rbt_iterator iter(*this);
	this->operator++();

	return iter;
}

template < typename K, typename V >
rbt_iterator<K, V>& rbt_iterator<K, V>::operator--()
{
	cur = predecessor(cur);

	return *this;
}

template < typename K, typename V >
const rbt_iterator<K, V> rbt_iterator<K, V>::operator--(int)
{
	rbt_iterator iter(*this);
	this->operator--();

	return iter;
}

template < typename K, typename V >
bool rbt_iterator<K, V>::operator==(const rbt_iterator<K, V> &iter)
{
	return cur == iter.cur;
}

template < typename K, typename V >
bool rbt_iterator<K, V>::operator!=(const rbt_iterator<K, V> &iter)
{
	return cur != iter.cur;
}

template < typename K, typename V >
typename rbt_iterator<K, V>::reference
rbt_iterator<K, V>::operator*()
{
	return (*cur).data;
}

template < typename K, typename V >
typename rbt_iterator<K, V>::pointer
rbt_iterator<K, V>::operator->()
{
	return &(cur->data);
}

template < typename K, typename V >
class red_black_tree {
protected:
	typedef rbt_node_base<K, V> _rbt_node;
	typedef rbt_iterator<K, V> _rbt_iterator;
public:
	typedef K key_type;
	typedef V mapped_type;
	typedef pair<K, V> value_type;
	typedef value_type *pointer;
	typedef value_type *reference;
	typedef _rbt_node rbt_node;
	typedef _rbt_iterator iterator;
	typedef void (*Function)(value_type);

	red_black_tree()
	{
		_rbt = NULL;
	}
	template < typename input_iterator >
	red_black_tree(input_iterator first, input_iterator last)
	{
		_rbt = NULL;
		typename iterator_traits<input_iterator>::value_type x;
		while(first != last) {
			x = *first;
			insert(x.first, x.second);
			++first;
		}
	}
	~red_black_tree();

	void insert(key_type, mapped_type);
	void erase(key_type);

	bool empty()
	{
		return _rbt == NULL;
	}
	iterator find(key_type);
	void traverse(Function);
	iterator begin();
	iterator end();

private:
	rbt_node *rbt_alloc_node(key_type key, mapped_type mapped)
	{
		return new rbt_node(key, mapped);
	}
	void rbt_free_node(rbt_node *&pnode)
	{
		delete pnode;
		pnode = NULL;
	}

	void left_rotate(rbt_node *&);
	void right_rotate(rbt_node*&);
	void double_lr_rotate(rbt_node *&);
	void double_rl_rotate(rbt_node *&);

	void rbt_insert_fixup(rbt_node *&);
	void rbt_erase_fixup(rbt_node *&);
	void rbt_erase_node(rbt_node *&);

	void rbt_destroy_node(rbt_node *&);
	void rbt_traverse_node(rbt_node *, Function);

	rbt_node *_rbt;
};

template < typename K, typename V >
void red_black_tree<K, V>::rbt_destroy_node(rbt_node *&pnode)
{
	if(pnode) {
		rbt_destroy_node(pnode->left);
		rbt_destroy_node(pnode->right);
		rbt_free_node(pnode);
	}
}

template < typename K, typename V >
red_black_tree<K, V>::~red_black_tree()
{
	if(_rbt) {
		rbt_destroy_node(_rbt);
	}
}

template < typename K, typename V >
void red_black_tree<K, V>::left_rotate(rbt_node *&pnode)
{
	rbt_node *rchild = pnode->right;
	pnode->right = rchild->left;
	if(pnode->right) {
		pnode->right->parent = pnode;
	}
	rchild->parent = pnode->parent;
	// following code cannot be replaced by last sentence "pnode = lchild", look bug 2
        //之前没有下面这个if
	if(pnode->parent) {
		if(pnode->parent->left == pnode) {
			pnode->parent->left = rchild;
		}
		else {
			pnode->parent->right = rchild;
		}
	}
	rchild->left = pnode;
	pnode->parent = rchild;
	pnode = rchild;
}

template < typename K, typename V >
void red_black_tree<K, V>::right_rotate(rbt_node *&pnode)
{
	rbt_node *lchild = pnode->left;
	pnode->left = lchild->right;
	if(pnode->left) {
		pnode->left->parent = pnode;
	}
	lchild->parent = pnode->parent;
	// following code cannot be replaced by last sentence "pnode = lchild", look bug 2
        // 之前没有下面这个if
	if(pnode->parent) {
		if(pnode->parent->left == pnode) {
			pnode->parent->left = lchild;
		}
		else {
			pnode->parent->right = lchild;
		}
	}
	lchild->right = pnode;
	pnode->parent = lchild;
	pnode = lchild;
}

template < typename K, typename V >
void red_black_tree<K, V>::double_lr_rotate(rbt_node *&pnode)
{
	left_rotate(pnode->left);
	right_rotate(pnode);
}

template < typename K, typename V >
void red_black_tree<K, V>::double_rl_rotate(rbt_node *&pnode)
{
	right_rotate(pnode->right);
	left_rotate(pnode);
}

template < typename K, typename V >
void red_black_tree<K, V>::rbt_insert_fixup(rbt_node *&pnode)
{
	rbt_node *uncle = NULL;
	while(pnode->parent && pnode->parent->parent && pnode->parent->color == RED) {
		if(pnode->parent->parent && pnode->parent == pnode->parent->parent->left) {
			if(pnode->parent->parent->right == NULL) {
				if(pnode == pnode->parent->right) {
					pnode = pnode->parent;
					left_rotate(pnode);
					pnode = pnode->left;
				}
				pnode = pnode->parent->parent;
				if(pnode == _rbt) {
					right_rotate(_rbt);
					_rbt->left->color = BLACK;
					break;
				}
				else {
					right_rotate(pnode);
					pnode->left->color = BLACK;
				}
			}
			else {
				uncle = pnode->parent->parent->right;
			    if(uncle->color == RED) {
			    	pnode->parent->color = BLACK;
				    uncle->color = BLACK;
				    pnode->parent->parent->color = RED;
				    pnode = pnode->parent->parent;
			    }
			    else {
				    if(pnode == pnode->parent->right) {
					     pnode = pnode->parent;
					     left_rotate(pnode);
				    }
				    pnode->color = BLACK;
				    pnode->parent->color = RED;
				    pnode = pnode->parent;
				    if(pnode == _rbt) {
				    	right_rotate(_rbt);
				    	break;
				    }
				    else {
				    	right_rotate(pnode);
				    }
			    }
			}
		}
		else if(pnode->parent->parent && pnode->parent == pnode->parent->parent->right) {
			if(pnode->parent->parent->left == NULL) {
				if(pnode == pnode->parent->left) {
					pnode = pnode->parent;
					right_rotate(pnode);
					pnode = pnode->right;
				}
				pnode = pnode->parent->parent;
				if(pnode == _rbt) {
					left_rotate(_rbt);
					_rbt->right->color = BLACK;
					break;
				}
				else {
					left_rotate(pnode);
					pnode->right->color = BLACK;
				}
			}
			else {
				uncle = pnode->parent->parent->left;
			    if(uncle->color == RED) {
				    pnode->parent->color = BLACK;
				    uncle->color = BLACK;
				    pnode->parent->parent->color = RED;
				    pnode = pnode->parent->parent;
			    }
			    else {
				    if(pnode == pnode->parent->left) {
					    pnode = pnode->parent;
					    right_rotate(pnode);
				    }
				    pnode->color = BLACK;
				    pnode->parent->color = RED;
				    pnode = pnode->parent;
				    if(pnode == _rbt) {
				    	left_rotate(_rbt);
				    }
				    else {
				    	left_rotate(pnode);
				    }
			    }
			}
		}
	}
	_rbt->color = BLACK;
}

template < typename K, typename V >
void red_black_tree<K, V>::insert(key_type key, mapped_type mapped)
{
	// p is father of pnode
	rbt_node *pnode = _rbt;
	rbt_node *p = NULL;
	while(pnode) {
		p = pnode;
		if(key < pnode->key()) {
			pnode = pnode->left;
		}
		else {
			pnode = pnode->right;
		}
	}
	pnode = rbt_alloc_node(key, mapped);
	pnode->parent = p;
	if(p == NULL) {
		_rbt = pnode;
	}
	else if(pnode->key() < p->key()) {
		p->left = pnode;
	}
	else {
		p->right = pnode;
	}
	rbt_insert_fixup(pnode);
}

template < typename K, typename V >
void red_black_tree<K, V>::rbt_erase_fixup(rbt_node *&pnode)
{
}

template < typename K, typename V >
void red_black_tree<K, V>::rbt_erase_node(rbt_node *&pnode)
{
	// qnode is the node which will be erased
	rbt_node *qnode = NULL, *rnode = NULL;

	// if pnode has less than two children, pnode will be erased
	if(pnode->left == NULL || pnode->right == NULL) {
		qnode = pnode;
	}
	else {
		// if pnode has two children, pnode's successor will be erased
		qnode = successor(pnode);
	}
	// rnode will replace qnode
	if(qnode->left) {
		rnode = qnode->left;
	}
	else {
		rnode = qnode->right;
	}
	// the following two operations will make rnode to the child of qnode's parent
	rnode->parent = qnode->parent;
	if(qnode->parent == NULL) {
		_rbt = rnode;
	}
	else if(qnode == qnode->parent->left) {
		qnode->parent->left = rnode;
	}
	else {
		qnode->parent->right = rnode;
	}
	if(qnode != pnode) {
		// pnode has two children
		pnode->data = qnode->data;
	}
	if(qnode->color == BLACK) {
		rbt_free_node(qnode);
		rbt_erase_fixup(rnode);
	}
}

template < typename K, typename V >
void red_black_tree<K, V>::erase(key_type key)
{
	rbt_node *pnode = _rbt;
	while(pnode) {
		if(key < pnode->key()) {
			pnode = pnode->left;
		}
		else if(key > pnode->key()) {
			pnode = pnode->right;
		}
		else {
			break;
		}
	}
	if(key == pnode->key()) {
		rbt_erase_node(pnode);
	}
}

template < typename K, typename V >
void red_black_tree<K, V>::rbt_traverse_node(rbt_node *pnode, Function func)
{
	if(pnode) {
		rbt_traverse_node(pnode->left, func);
		func(pnode->data);
		rbt_traverse_node(pnode->right, func);
	}
}

template < typename K, typename V >
void red_black_tree<K, V>::traverse(Function func)
{
	if(_rbt) {
		rbt_traverse_node(_rbt, func);
	}
}

template < typename K, typename V >
typename red_black_tree<K, V>::iterator
red_black_tree<K, V>::begin()
{
	iterator iter;
	if(_rbt == NULL) {
		iter.cur = NULL;
		return iter;
	}
	rbt_node *pnode = _rbt;
	while(pnode->left) {
		pnode = pnode->left;
	}
	iter.cur = pnode;
	return iter;
}

// 由于最右节点的下一个节点就是空节点(参看successor)，因此可以直接将end迭代器置为0
template < typename K, typename V >
typename red_black_tree<K, V>::iterator
red_black_tree<K, V>::end()
{
	iterator iter;
	iter.cur = NULL;
	return iter;
}

void print(pair<int, int> p)
{
	cout << p.first << " " << p.second << endl;
}

int main()
{
	vector<pair<int, int> > vec;
	vec.push_back(make_pair(5, 5));
	vec.push_back(make_pair(2, 2));
	vec.push_back(make_pair(7, 7));
	vec.push_back(make_pair(3, 3));
	//vec.push_back(make_pair(7, 7));
	vec.push_back(make_pair(9, 9));

	red_black_tree<int, int> rbt(vec.begin(), vec.end());

	// 下面是访问红黑树的两种方式:
	// 一种是使用红黑树提供的traverse函数，它的参数是函数指针或者函数对象
	// 函数指针或者函数对象的参数是pair
	//rbt.traverse(print);

	// 另外一种是使用它的迭代器
	for(red_black_tree<int, int>::iterator iter = rbt.begin();
		                               iter != rbt.end(); ++iter) {
		cout << iter->first << " " << iter->second << endl;
	}
	
	return 0;
}
