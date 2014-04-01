/*
 * author:	luo feng
 * date:	2014/3/27 - 2014/3/28
 * title:	Binary Search Tree
 * language:	C++
 * info:	按照STL的规则实现了二叉查找数（二叉排序树），由于只有节点的前趋和后继需要使用到节点的父节点指针，为了方便，没有在节点中设置父节点指针，因此，也没有实现迭代器的自增和自减操作。另外，to_linked_list()为july的微软面试100题中的第一题，其实本不应该作为成员函数的。
 */

#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

template < typename K, typename V >
struct bst_node_base {
	K key;
	V value;
	bst_node_base *left, *right;
	bst_node_base(K k, V v) : key(k), value(v), left(NULL), right(NULL) { }
};

template < typename K, typename V >
struct bst_iterator {
	bst_node_base<K, V> *cur;

	typedef bst_node_base<K, V> *pointer;
	typedef bst_node_base<K, V>& reference;
	//bst_iterator& operator++();
	//const bst_iterator operator++(int);
	//bst_iterator& operator--();
	//const bst_iterator operator--(int);
	bool operator==(const bst_iterator&);
	bool operator!=(const bst_iterator&);
};

template < typename K, typename V >
bool bst_iterator<K, V>::operator==(const bst_iterator &iter)
{
	return cur == iter.cur;
}

template < typename K, typename V >
bool bst_iterator<K, V>::operator!=(const bst_iterator &iter)
{
	return cur != iter.cur;
}

template < typename K, typename V >
class binary_search_tree {
protected:
	typedef bst_node_base<K, V> _bst_node;
	typedef bst_iterator<K, V> _bst_iterator;
public:
	friend struct bst_iterator<K, V>;
	
	typedef K key_type;
	typedef V value_type;
	typedef _bst_iterator iterator;
	typedef _bst_node bst_node;
	typedef void (*Function)(key_type, value_type);

	binary_search_tree()
	{
		_bst_tree = NULL;
	}
	template <typename input_iterator>
	binary_search_tree(input_iterator first, input_iterator last)
	{
		_bst_tree = NULL;
		typename iterator_traits<input_iterator>::value_type x;
		while(first != last) {
			x = *first;
			insert(x.first, x.second);
			++first;
		}
	}
	~binary_search_tree();

	iterator insert(key_type, value_type);
	void erase(key_type);
	void to_linked_list();

	bool empty()
	{
		return _bst_tree == NULL;
	}
	iterator find(key_type);
	void traverse(Function);

private:
	bst_node* get_min();
	bst_node* get_max();
	void to_linked_list_node(bst_node *&, bst_node *&, bst_node *&);
	bst_node *bst_alloc_node(K key, V value)
	{
		return new bst_node(key, value);
	}
	void bst_free_node(bst_node *pnode)
	{
		delete pnode;
	}
	void bst_destroy_node(bst_node *);
	void bst_traverse_node(bst_node *, Function);

	bst_node *_bst_tree;
};

template < typename K, typename V >
void binary_search_tree<K, V>::bst_destroy_node(bst_node *pnode)
{
	if(pnode) {
		bst_destroy_node(pnode->left);
		bst_destroy_node(pnode->right);
		delete pnode;
	}
}

template < typename K, typename V >
void binary_search_tree<K, V>::bst_traverse_node(bst_node *pnode, Function func)
{
	if(pnode) {
		bst_traverse_node(pnode->left, func);
		func(pnode->key, pnode->value);
		bst_traverse_node(pnode->right, func);
	}
}

template < typename K, typename V >
binary_search_tree<K, V>::~binary_search_tree()
{
	bst_destroy_node(_bst_tree);
}

template < typename K, typename V >
typename binary_search_tree<K, V>::iterator
binary_search_tree<K, V>::insert(key_type key, value_type value)
{
	typename binary_search_tree<K, V>::iterator iter;
	if(empty()) {
		_bst_tree = bst_alloc_node(key, value);
		iter.cur = _bst_tree;
		return iter;
	}

	bst_node *in_node = bst_alloc_node(key, value);
	bst_node *pnode = _bst_tree;
	while(pnode) {
		if(key < pnode->key && pnode->left) {
			pnode = pnode->left;
		}
		else if(key < pnode->key && !(pnode->left)) {
			pnode->left = in_node;
			iter.cur = in_node;
			return iter;
		}
		if(key > pnode->key && pnode->right) {
			pnode = pnode->right;
		}
		else if(key > pnode->key && !(pnode->right)) {
			pnode->right = in_node;
			iter.cur = in_node;
			return iter;
		}
	}
	iter.cur = NULL;
	return iter;
}

template < typename K, typename V >
typename binary_search_tree<K, V>::iterator
binary_search_tree<K, V>::find(key_type key)
{
	bst_node *pnode = _bst_tree;
	while(pnode) {
		if(key == pnode->key) {
			return pnode;
		}
		if(key < pnode->key && pnode->left) {
			pnode = pnode->left;
		}
		else if(key > pnode->key && pnode->right) {
			pnode = pnode->right;
		}
	}
	return NULL;
}

template < typename K, typename V >
void binary_search_tree<K, V>::traverse(Function func)
{
	bst_traverse_node(_bst_tree, func);
}

template < typename K, typename V >
void binary_search_tree<K, V>::erase(key_type key)
{
	bst_node *pnode = _bst_tree;
	bst_node *ppnode = _bst_tree;
	while(pnode) {
		if(key == pnode->key) {
			break;
		}
		if(key < pnode->key) {
			if(pnode != ppnode) {
				ppnode = pnode;
			}
			pnode = ppnode->left;
		}
		if(key > pnode->key) {
			if(pnode != ppnode) {
				ppnode = pnode;
			}
			pnode = ppnode->right;
		}
	}
	if(pnode) {
		if(pnode->left == NULL && pnode->right == NULL) {
			bst_free_node(pnode);
			if(pnode == ppnode) {
				_bst_tree = NULL;
			}
			else if(ppnode->left == pnode) {
				ppnode->left = NULL;
			}
			else if(ppnode->right == pnode) {
				ppnode->right = NULL;
			}
		}
		else if(pnode->left == NULL && pnode->right) {
			bst_node *qnode = pnode->right;
			if(pnode == ppnode) {
				_bst_tree = pnode->right;
			}
			if(ppnode->left == pnode) {
				ppnode->left = qnode;
			}
			if(ppnode->right == pnode) {
				ppnode->right = qnode;
			}
			bst_free_node(pnode);
		}
		else if(pnode->left && pnode->right == NULL) {
			bst_node *qnode = pnode->left;
			if(pnode == ppnode) {
				_bst_tree = pnode->left;
			}
			if(ppnode->left == pnode) {
				ppnode->left = qnode;
			}
			if(ppnode->right == pnode) {
				ppnode->right = qnode;
			}
			bst_free_node(pnode);
		}
		else if(pnode->left && pnode->right) {
			bst_node *qnode = pnode->right;
			ppnode = pnode;
			while(qnode->left) {
				ppnode = qnode;
				qnode = qnode->left;
			}
			pnode->key = qnode->key;
			pnode->value = qnode->value;
			if(qnode->right) {
				ppnode->right = qnode->right;
			}
			else if(qnode->right == NULL) {
				ppnode->left = NULL;
			}
			bst_free_node(qnode);
		}
	}
}

template < typename K, typename V >
typename binary_search_tree<K, V>::bst_node*
binary_search_tree<K, V>::get_min()
{
	if(_bst_tree == NULL)
		return NULL;
	bst_node* pnode = _bst_tree;
	while(pnode->left) {
		pnode = pnode->left;
	}
	return pnode;
}

template < typename K, typename V >
typename binary_search_tree<K, V>::bst_node*
binary_search_tree<K, V>::get_max()
{
	if(_bst_tree == NULL)
		return NULL;
	bst_node* pnode = _bst_tree;
	while(pnode->right) {
		pnode = pnode->right;
	}
	return pnode;
}

template < typename K, typename V >
void binary_search_tree<K, V>::to_linked_list_node(bst_node *&root, bst_node *&start_node, bst_node *&end_node)
{
	if(root == NULL) {
		start_node = NULL;
		end_node = NULL;
		return;
	}

	bst_node *s1, *e1, *s2, *e2;
	to_linked_list_node(root->left, s1, e1);
	to_linked_list_node(root->right, s2, e2);
	root->left = e1;
	root->right = s2;
	start_node = s1;
	end_node = e2;
	if(e1) {
		e1->right = root;
	}
	else {
		start_node = root;
	}
	if(s2) {
		s2->left = root;
	}
	else {
		end_node = root;
	}
}

template < typename K, typename V >
void binary_search_tree<K, V>::to_linked_list()
{
	bst_node *s, *e;
	to_linked_list_node(_bst_tree, s, e);
	bst_node* pnode = s;
	while(pnode) {
		s = pnode->right;
		cout << pnode->key << endl;
		bst_free_node(pnode);
		pnode = s;
	}
	_bst_tree = NULL;
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
	binary_search_tree<int, int> bt(vec.begin(), vec.end());

	bt.traverse(print);
	cout << endl;
	bt.to_linked_list();

	return 0;
}
