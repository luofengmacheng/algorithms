## 二叉树的非递归遍历

树的节点定义：

``` C++
struct tree_node {
	int val;
	tree_node *left, *right;
	tree_node(int x = 0) : val(x), left(NULL), right(NULL) { }
};
```

### 1 二叉树的前序遍历(递归)

``` C++
void preorder_recur(tree_node *root)
{
	if(root != NULL) {
		cout << root->val << endl;
		preorder_recur(root->left);
		preorder_recur(root->right);
	}
}
```

### 2 二叉树的前序遍历(非递归)

``` C++
void preorder_nonrecur(tree_node *root)
{
	if(root == NULL) {
		return;
	}

	stack<tree_node *> sta;

	tree_node *pnode = root;
	while(pnode != NULL || !sta.empty()) {

		while(pnode) {
			cout << pnode->val << endl;
			sta.push(pnode);
			pnode = pnode->left;
		}

		tree_node *qnode = sta.top();
		pnode = qnode->right;
		sta.pop();
	}
}
```

### 3 二叉树的中序遍历(递归)

``` C++
void inorder_recur(tree_node *root)
{
	if(root != NULL) {
		inorder_recur(root->left);
		cout << root->val << endl;
		inorder_recur(root->right);
	}
}
```

### 4 二叉树的中序遍历(非递归)

``` C++
void inorder_nonrecur(tree_node *root)
{
	if(root == NULL) {
		return;
	}

	stack<tree_node *> sta;

	tree_node *pnode = root;
	while(pnode != NULL || !sta.empty()) {

		while(pnode) {
			sta.push(pnode);
			pnode = pnode->left;
		}

		tree_node *qnode = sta.top();
		cout << qnode->val << endl;
		pnode = qnode->right;
		sta.pop();
	}
}
```

### 5 二叉树的后序遍历(递归)

``` C++
void postorder_recur(tree_node *root)
{
	if(root != NULL) {
		postorder_recur(root->left);
		postorder_recur(root->right);
		cout << root->val << endl;
	}
}
```

### 6 二叉树的后序遍历(非递归)

``` C++
void postorder_nonrecur(tree_node *root)
{
	if(root == NULL) {
		return;
	}

	vector<pair<tree_node *, bool> > sta;

	tree_node *pnode = root;
	while(pnode != NULL || !sta.empty()) {

		while(pnode) {
			sta.push_back(make_pair(pnode, true));
			pnode = pnode->left;
		}

		while(!sta.empty() && (sta.back().second == false)) {
			pair<tree_node *, bool> eliment = sta.back();
			cout << eliment.first->val << endl;
			sta.pop_back();
		}

		if(!sta.empty()) {
			sta.back().second = false;
			pnode = sta.back().first->right;
		}
	}
}
```

### 7 链表和树的测试方法

这里以二叉树为例，链表类似。

在编写有关二叉树的代码时，为了测试代码是否运行正常，我们需要创建一个二叉树，但是，二叉树的创建操作略显麻烦，而且还要写几个关于创建和销毁的函数，这里介绍一种创建二叉树的简单方法。


假如要创建下面这样的二叉树：

    0
   / \
  1   2
 / \   \
3   4   5

先写一个修改二叉树节点的左右指针和值的函数:

``` C++
// tree为二叉树的数组指针，root表示当前根节点的索引
// left为当前根节点的左子树的索引，right为当前根节点的右子树的索引
// 如果left为0，表示左子树为空，如果right为0，表示右子树为空
// val为根节点的数据域的值
void link(tree_node *tree, int root, int left, int right, int val)
{
	tree[root].val = val;

	if(left == 0) {
		tree[root].left = NULL;
	}
	else {
		tree[root].left = &tree[left];
	}

	if(right == 0) {
		tree[root].right = NULL;
	}
	else {
		tree[root].right = &tree[right];
	}
}
```

那么，就可以以如下方式创建上面二叉树：

``` C++
tree_node tree[5];
link(tree, 0, 1, 2, 0);
link(tree, 1, 3, 4, 1);
link(tree, 2, 0, 5, 2);
link(tree, 3, 0, 0, 3);
link(tree, 4, 0, 0, 4);
link(tree, 5, 0, 0, 5);
```

然后，就可以对上面的二叉树调用遍历函数：

``` C++
postorder_recur(&tree[0]);
```
