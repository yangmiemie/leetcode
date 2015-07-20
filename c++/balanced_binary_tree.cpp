/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include <iostream>
using std::cout;
using std::endl;

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

typedef struct TreeNode* Tree;

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        int height;
        return isTreeBalanced(root, height);
    }
private:
		bool isTreeBalanced(TreeNode* root, int& height)
		{
			bool leftBalanced, rightBalanced, rootBalanced;
			int leftHeight, rightHeight;

			if (root == NULL)
			{
				height = 0;
				return true;
			}

			if (root -> left == NULL && root -> right == NULL)
			{
				height = 1;
				return true;
			}

			leftBalanced = isTreeBalanced(root -> left, leftHeight);
			rightBalanced = isTreeBalanced(root -> right, rightHeight);
			rootBalanced = abs(leftHeight - rightHeight) > 1 ? false : true;

			height = max(leftHeight, rightHeight) + 1;

			return leftBalanced && rightBalanced && rootBalanced;
		}

		int max(int a, int b)
		{
			return a > b ? a : b;
		}

		int abs(int a)
		{
			if (a < 0)
				return a * -1;

			return a;
		}
};

Tree Insert(int value, Tree T)
{
	if (T == NULL)
		return new TreeNode(value);

	if (T -> val > value)
		T -> left = Insert(value, T -> left);
	else if (T -> val < value)
		T -> right = Insert(value, T -> right);

	return T;
}

void PostOrderTraverse(Tree T)
{
	if (T == NULL)
		return;

	PostOrderTraverse(T -> left);
	PostOrderTraverse(T -> right);
	cout << T -> val << " ";
}


void InOrderTraverse(Tree T)
{
	if (T == NULL)
		return;

	InOrderTraverse(T -> left);
	cout << T -> val << " ";
	InOrderTraverse(T -> right);
}

void PreOrderTraverse(Tree T)
{
	if (T == NULL)
		return;

	cout << T -> val << " ";
	PreOrderTraverse(T -> left);
	PreOrderTraverse(T -> right);
}

int main(int argc, char const *argv[])
{
	int array[] = {7, 3, 8};
	Tree T;
	int i, Len, balanced;
	Solution s;

	Len = sizeof(array) / sizeof(array[0]);
	T = NULL;
	for (i = 0; i < Len; ++i)
		T = Insert(array[i], T);

	PreOrderTraverse(T);
	cout << endl;

	InOrderTraverse(T);
	cout << endl;

	PostOrderTraverse(T);
	cout << endl;

	balanced = s.isBalanced(T);
	cout << balanced << endl;
	return 0;
}