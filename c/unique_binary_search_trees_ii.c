// Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

// For example,
// Given n = 3, your program should return all 5 unique BST's shown below.

//    1         3     3      2      1
//     \       /     /      / \      \
//      3     2     1      1   3      2
//     /     /       \                 \
//    2     1         2                 3


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

typedef struct TreeNode* Tree;

Tree NewNode(int value)
{
  Tree T;
  struct TreeNode node;
  T = (Tree)malloc(sizeof(struct TreeNode));
  T -> val = value;
  T -> left = T -> right = NULL;
  return T;
}

Tree CreateTree(int first, int end)
{
	int i;
	Tree T;

	if (first == end)
	{
		return NewNode(first);
	}

	if (first > end)
	{
		return NULL;
	}

	for (i = first; i <= end; ++i)
	{
		T = NewNode(first);
		T -> left = CreateTree(i, first - 1);
		T -> right = CreateTree(first + 1, end);
	}	

	
}

struct TreeNode** generateTrees(int n, int* returnSize) {
    
}