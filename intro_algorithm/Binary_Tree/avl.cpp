/*
 * author:	luo feng
 * date:	2014/3/31 - 2014/4/1
 * title:	Balanced Binary Tree(so called AVL)
 * language:	C++
 * info:	按照STL的规则实现了平衡二叉树，主要的操作是：增加关键字，删除关键字，查找关键字，遍历整个二叉树。平衡二叉树的操作跟二叉查找树类似，不同的是节点中增加了一个表示当前子树的高度，用这个字段来判断是否平衡，并进行相应的调整。
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

template < typename K, typename V, typename H = int >
struct avl_node_base {
	K key;
	V value;
	H height;
	avl_node_base *left, *right;
	avl_node_base(K k, V v, H h) : key(k), value(v), height(h), left(NULL), right(NULL) { }
};

template < typename K, typename V >
struct avl_iterator {
	avl_node_base<K, V> *cur;

	typedef avl_node_base<K, V> *pointer;
	typedef avl_node_base<K, V>& reference;
	//avl_iterator& operator++();
	//const avl_iterator operator++(int);
	//avl_iterator& operator--();
	//const avl_iterator operator--(int);
	bool operator==(const avl_iterator&);
	bool operator!=(const avl_iterator&);

	avl_node_base<K, V>& operator*();
	avl_node_base<K, V>* operator->();
};

template < typename K, typename V >
bool avl_iterator<K, V>::operator==(const avl_iterator &iter)
{
	return cur == iter.cur;
}

template < typename K, typename V >
bool avl_iterator<K, V>::operator!=(const avl_iterator &iter)
{
	return cur != iter.cur;
}

template < typename K, typename V >
avl_node_base<K, V>& avl_iterator<K, V>::operator*()
{
	return *cur;
}

template < typename K, typename V >
avl_node_base<K, V>* avl_iterator<K, V>::operator->()
{
	return cur;
}

template < typename K, typename V >
class avl_search_tree {
protected:
	typedef avl_node_base<K, V> _avl_node;
	typedef avl_iterator<K, V> _avl_iterator;

public:
	typedef K key_type;
	typedef V value_type;
	typedef _avl_iterator iterator;
	typedef _avl_node avl_node;
	typedef void (*Function)(key_type, value_type);

	avl_search_tree()
	{
		_avl_tree = NULL;
	}
	template < typename input_iterator >
	avl_search_tree(input_iterator first, input_iterator last)
	{
		_avl_tree = NULL;
		typename iterator_traits<input_iterator>::value_type x;
		while(first != last) {
			x = *first;
			insert(x.first, x.second);
			++first;
		}
	}
	~avl_search_tree();

	void insert(key_type, value_type);
	void erase(key_type);

	bool empty()
	{
		return _avl_tree == NULL;
	}
	iterator find(key_type);
	void traverse(Function);

private:
	int get_height(avl_node* pnode)
	{
		if(pnode == NULL)
			return -1;
		return pnode->height;
	}
	avl_node* avl_alloc_node(key_type key, value_type value)
	{
		return new avl_node(key, value, 0);
	}
	void avl_free_node(avl_node *&pnode)
	{
		delete pnode;
		pnode = NULL;
	}
	void single_left_rotate(avl_node*&);
	void single_right_rotate(avl_node*&);
	void double_lr_rotate(avl_node*&);
	void double_rl_rotate(avl_node*&);
	void insert_key(avl_node*&, key_type, value_type);
	void erase_key(avl_node*&, key_type);
	iterator find_key(avl_node*, key_type);
	void avl_destroy_node(avl_node*&);
	void traverse_node(avl_node*, Function);

	avl_node *_avl_tree;
};

template < typename K, typename V >
void avl_search_tree<K, V>::avl_destroy_node(avl_node *&avl_tree)
{
	if(avl_tree) {
		avl_destroy_node(avl_tree->left);
		avl_destroy_node(avl_tree->right);
		//avl_free_node(avl_tree);
		//avl_tree = NULL;
		delete avl_tree;
	}
}

template < typename K, typename V >
avl_search_tree<K, V>::~avl_search_tree()
{
	avl_destroy_node(_avl_tree);
}

template < typename K, typename V >
void avl_search_tree<K, V>::single_left_rotate(avl_node *&pnode)
{
	avl_node *lchild = pnode->left;
	pnode->left = lchild->right;
	pnode->height = max(get_height(pnode->left), get_height(pnode->right)) + 1;
	lchild->right = pnode;
	lchild->height = max(get_height(lchild->left), get_height(lchild->right)) + 1;
	pnode = lchild;
}

template < typename K, typename V >
void avl_search_tree<K, V>::single_right_rotate(avl_node *&pnode)
{
	avl_node *rchild = pnode->right;
	pnode->right = rchild->left;
	pnode->height = max(get_height(pnode->left), get_height(pnode->right)) + 1;
	rchild->left = pnode;
	rchild->height = max(get_height(rchild->left), get_height(rchild->right)) + 1;
	pnode = rchild;
}

template < typename K, typename V >
void avl_search_tree<K, V>::double_lr_rotate(avl_node *&pnode)
{
	single_right_rotate(pnode->left);
	single_left_rotate(pnode);
}

template < typename K, typename V >
void avl_search_tree<K, V>::double_rl_rotate(avl_node *&pnode)
{
	single_left_rotate(pnode->right);
	single_right_rotate(pnode);
}

//用递归的方法插入关键字，插入了之后，要判断当前子树是否平衡，如果不平衡，就要进行调整。操作完了之后要进行节点的高度的更新。
template < typename K, typename V >
void avl_search_tree<K, V>::insert_key(avl_node *&avl_tree, K key, V value)
{
	if(avl_tree == NULL) {
		avl_tree = avl_alloc_node(key, value);
		return;
	}
	if(key < avl_tree->key) {
		insert_key(avl_tree->left, key, value);
		if(get_height(avl_tree->left) - get_height(avl_tree->right) >= 2) {
			if(avl_tree->left && get_height(avl_tree->left->left) > get_height(avl_tree->left->right)) {
				single_left_rotate(avl_tree);
			}
			else {
				double_lr_rotate(avl_tree);
			}
		}
	}
	else if(key > avl_tree->key) {
		insert_key(avl_tree->right, key, value);
		if(get_height(avl_tree->right) - get_height(avl_tree->left) >= 2) {
			if(avl_tree->right && get_height(avl_tree->right->right) > get_height(avl_tree->right->left)) {
				single_right_rotate(avl_tree);
			}
			else {
				double_rl_rotate(avl_tree);
			}
		}
	}
	else {
		return;
	}
	avl_tree->height = max(get_height(avl_tree->left), get_height(avl_tree->right)) + 1;
}

template < typename K, typename V >
void avl_search_tree<K, V>::insert(key_type key, value_type value)
{
	insert_key(_avl_tree, key, value);
}

//跟插入关键字类似，不同的是当找到关键字之后，要根据关键字所在的节点是否有左右孩子进行节点的删除。
//当然，最后还是要进行节点的高度的更新。
template < typename K, typename V >
void avl_search_tree<K, V>::erase_key(avl_node *&avl_tree, key_type key)
{
	if(avl_tree == NULL) {
		return;
	}

	if(key < avl_tree->key) {
		erase_key(avl_tree->left, key);
		if(get_height(avl_tree->left) - get_height(avl_tree->right) >= 2) {
			if(avl_tree->left && get_height(avl_tree->left->left) > get_height(avl_tree->left->right)) {
				single_left_rotate(avl_tree);
			}
			else {
				double_lr_rotate(avl_tree);
			}
		}
	}
	else if(key > avl_tree->key) {
		erase_key(avl_tree->right, key);
		if(get_height(avl_tree->right) - get_height(avl_tree->left) >= 2) {
			if(avl_tree->right && get_height(avl_tree->right->right) > get_height(avl_tree->right->left)) {
				single_right_rotate(avl_tree);
			}
			else {
				double_rl_rotate(avl_tree);
			}
		}
	}
	else {
		if(avl_tree->left && avl_tree->right) {
			avl_node *rmin = avl_tree->right;
			while(rmin->left) {
				rmin = rmin->left;
			}
			avl_tree->key = rmin->key;
			avl_tree->value = rmin->value;
			erase_key(avl_tree->right, rmin->key);
			if(get_height(avl_tree->right) - get_height(avl_tree->left) >= 2) {
				if(avl_tree->right && get_height(avl_tree->right->right) > get_height(avl_tree->right->left)) {
					single_right_rotate(avl_tree);
				}
				else {
					double_rl_rotate(avl_tree);
				}
			}
		}
		else if(avl_tree->left && avl_tree->right == NULL) {
			avl_node *pnode = avl_tree;
			avl_tree = pnode->left;
			avl_free_node(pnode);
		}
		else if(avl_tree->left == NULL && avl_tree->right) {
			avl_node *pnode = avl_tree;
			avl_tree = pnode->right;
			avl_free_node(pnode);
		}
		else {
			avl_free_node(avl_tree);
			avl_tree = NULL;
		}
	}
	if(avl_tree) {
		avl_tree->height = max(get_height(avl_tree->left), get_height(avl_tree->right)) + 1;
	}
}

template < typename K, typename V >
void avl_search_tree<K, V>::erase(key_type key)
{
	erase_key(_avl_tree, key);
}

template < typename K, typename V >
typename avl_search_tree<K, V>::iterator
avl_search_tree<K, V>::find_key(avl_node *avl_tree, key_type key)
{
	if(avl_tree == NULL) {
		iterator iter;
		iter.cur = NULL;
		return iter;
	}

	if(key < avl_tree->key) {
		return find_key(avl_tree->left, key);
	}
	else if(key > avl_tree->key) {
		return find_key(avl_tree->right, key);
	}
	else {
		iterator iter;
		iter.cur = avl_tree;
		return iter;
	}
}

template < typename K, typename V >
typename avl_search_tree<K, V>::iterator
avl_search_tree<K, V>::find(key_type key)
{
	return find_key(_avl_tree, key);
}

template < typename K, typename V >
void avl_search_tree<K, V>::traverse_node(avl_node *avl_tree, Function func)
{
	if(avl_tree) {
		traverse_node(avl_tree->left, func);
		func(avl_tree->key, avl_tree->value);
		cout << "height:" << avl_tree->height << endl;
		traverse_node(avl_tree->right, func);
	}
}

template < typename K, typename V >
void avl_search_tree<K, V>::traverse(Function func)
{
	traverse_node(_avl_tree, func);
}

void print(int x, int y)
{
	cout << "key = " << x << " value = " << y << endl;
}

int main()
{
	vector<pair<int, int> > vec;
	vec.push_back(make_pair(5, 5));
	vec.push_back(make_pair(4, 4));
	vec.push_back(make_pair(3, 3));
	vec.push_back(make_pair(8, 8));
	vec.push_back(make_pair(7, 7));
	vec.push_back(make_pair(9, 9));
	avl_search_tree<int, int> avl(vec.begin(), vec.end());

	avl.traverse(print);
	cout << endl;
	avl.erase(5);
	avl.traverse(print);
	cout << endl;
	avl.erase(7);
	avl.traverse(print);
	cout << endl;
	avl_search_tree<int, int>::iterator iter = avl.find(4);
	//if(iter != avl_search_tree<int, int>::null_iterator) {
		cout << iter->key << " " << iter->value << endl;
		cout << (*iter).key << " " << (*iter).value << endl;
	//}
	
	return 0;
}
