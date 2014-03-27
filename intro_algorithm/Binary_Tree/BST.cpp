#include <iostream>
#include <iterator>
using namespace std;



template < typename K, typename V >
class binary_search_tree {
	struct bst_node {
		K key;
		V value;
		bst_node *left, *right;
		bst_node(K k, V v) : key(k), value(v), left(NULL), right(NULL) { }
	};

	bst_node *_bst_tree;

public:
	typedef K key_type;
	typedef V value_type;
	typedef void (*Function)(key_type, value_type);
	//typedef std::iterator<input_iterator_tag, bst_node> iterator;
	struct bst_iterator : std::iterator<input_iterator_tag, bst_node>
    {
	    typename iterator<input_iterator_tag, bst_node>::pointer cur;
	    bst_iterator& operator++()
	    {

	    }
	    bst_iterator& operator--()
	    {

	    }
    };
	friend struct bst_iterator;
	
	typedef bst_iterator iterator;

	binary_search_tree()
	{
		_bst_tree = NULL;
	}
	~binary_search_tree();

	typename binary_search_tree<K, V>::iterator insert(key_type, value_type);
	void erase(key_type);

	bool empty()
	{
		return _bst_tree == NULL;
	}
	typename binary_search_tree<K, V>::iterator find(key_type);
	void traverse(Function);
	

private:
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

void print(int x, int y)
{
	cout << "key = " << x << " value = " << y << endl;
}

int main()
{
	binary_search_tree<int, int> bt;
	int a[] = {5, 2, 4, 4, 8, 8, 3, 3, 7, 7, 9, 9};
	for(int i = 0; i < 12;) {
		bt.insert(a[i], a[i + 1]);
		i += 2;
	}
	bt.traverse(print);
	cout << endl;
	bt.erase(5);
	cout << endl;
	bt.traverse(print);

	return 0;
}