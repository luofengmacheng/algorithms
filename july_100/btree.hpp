/*
 * author:	luo feng
 * date:	2014/6/27
 * title:	Binary Tree implementation
 * language:	C++
 */

#ifndef _BTREE_H
#define _BTREE_H

#include <queue>
#include <cstddef>

using namespace std;

template < typename T >
struct bnode_base {
	T data;
	bnode_base *left;
	bnode_base *right;
	bnode_base(T t) : data(t), left(NULL), right(NULL) { }
};

template < typename T >
class btree {
protected:
	//typedef bnode_base<T> bnode;
	
public:
	typedef void (*Function)(T t);
	typedef bnode_base<T> bnode;

	btree()
	{
		root = NULL;
	}

	template < typename input_iterator >
	btree(input_iterator first, input_iterator last);
	~btree();

	bool empty()
	{
		return root == NULL;
	}

	void traverse(Function);
	bnode *get_root()
	{
		return root;
	}

	void destroy_btree(bnode *pnode);

private:
	bnode *make_bnode(T t)
	{
		bnode *pnode = new bnode(t);
		return pnode;
	}

	void destroy_bnode(bnode *pnode)
	{
		delete pnode;
	}
	void traverse_bnode(bnode*, Function);

	bnode *root;
};

template < typename T >
template < typename input_iterator >
btree<T>::btree(input_iterator first, input_iterator last)
{
	root = NULL;
	queue<bnode *> que;

	if(first == last) {
		return;
	}
	root = make_bnode(*first);
	que.push(root);
	++first;

	while(first != last) {
		bnode *pnode = que.front();
		que.pop();
		if(*first == 0) {
			pnode->left = NULL;
		}
		else {
			pnode->left = make_bnode(*first);
		}
		que.push(pnode->left);
		++first;

		if(first == last) {
			break;
		}

		if(*first == 0) {
			pnode->right = NULL;
		}
		else {
			pnode->right = make_bnode(*first);
		}
		que.push(pnode->right);
		++first;
	}
}

template < typename T >
void btree<T>::destroy_btree(bnode *pnode)
{
	if(pnode != NULL) {
		destroy_btree(pnode->left);
		destroy_btree(pnode->right);
		destroy_bnode(pnode);
	}
}

template < typename T >
btree<T>::~btree()
{
	destroy_btree(root);
}

template < typename T >
void btree<T>::traverse_bnode(bnode *pnode, Function func)
{
	if(pnode != NULL) {
		traverse_bnode(pnode->left, func);
		func(pnode->data);
		traverse_bnode(pnode->right, func);
	}
}

template < typename T >
void btree<T>::traverse(Function func)
{
	traverse_bnode(root, func);
}

#endif