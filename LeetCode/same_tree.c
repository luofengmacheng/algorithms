/*
 * author:	luo feng
 * date:	2013/10/18
 * source:	LeetCode OJ
 * title:	Same Tree
 * remark:	由于本题采用递归比较简单，因此，就不给出程序的整体代码了
 */

bool isSameTree(TreeNode *p, TreeNode *q) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
    if(p == NULL && q == NULL )
        return true;
    else if(p == NULL && q != NULL)
        return false;
    else if(p != NULL && q == NULL)
        return false;
        
    if(p->val == q->val &&
       isSameTree(p->left, q->left) && 
       isSameTree(p->right, q->right))
        return true;
    else
        return false;
}
