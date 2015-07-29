/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct TreeNode
{
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;

int Max(int a, int b)
{
	return a > b ? a : b;
}

int Max3(int a, int b, int c)
{
	int x;
	x = a > b ? a : b;
	x = x > c ? x : c;
	return x;
}

int maxTreePathSum(struct TreeNode* root, int* MaxPathSum)
{
  if (root == NULL)
  	return 0;

  if (root -> left == NULL && root -> right == NULL)
  {
	  if (root -> val > *MaxPathSum)
	  	*MaxPathSum = root -> val;

  	return root -> val;  	
  }

  int LeftMaxPathSum, RightMaxPathSum, Tmp;

  LeftMaxPathSum = maxTreePathSum(root -> left, MaxPathSum);
  RightMaxPathSum = maxTreePathSum(root -> right, MaxPathSum);

  if (LeftMaxPathSum > 0 && (LeftMaxPathSum + root -> val > *MaxPathSum))
  	*MaxPathSum = LeftMaxPathSum + root -> val;

  if (RightMaxPathSum > 0 && (RightMaxPathSum + root -> val) > *MaxPathSum)
  	*MaxPathSum = RightMaxPathSum + root -> val;

  if (root -> val > *MaxPathSum)
  	*MaxPathSum = root -> val;

  if (LeftMaxPathSum > 0 && RightMaxPathSum > 0 && (RightMaxPathSum + LeftMaxPathSum + root -> val) > *MaxPathSum)
  	*MaxPathSum = RightMaxPathSum + LeftMaxPathSum + root -> val;

  return Max3(LeftMaxPathSum + root -> val, RightMaxPathSum + root -> val, root -> val);
}

int maxPathSum(struct TreeNode* root) {
	int MaxPathSum = INT_MIN;
	maxTreePathSum(root, &MaxPathSum);
	return MaxPathSum;
}

Tree NewNode(int value)
{
  Tree T;
  T = malloc(sizeof(struct TreeNode));
  T -> val = value;
  T -> left = T -> right = NULL;
  return T;
}

Tree Insert(int value, Tree T)
{
  if (T == NULL)
    return NewNode(value);

  // T -> left = Insert(value, T -> left);
  if (T -> val > value)
    T -> left = Insert(value, T -> left);
  else if (T -> val < value)
    T -> right = Insert(value, T -> right);

  return T;
}

void PreOrderTraverse(Tree T)
{
  if (T == NULL)
    return;

  printf("%d ", T -> val);
  PreOrderTraverse(T -> left);
  PreOrderTraverse(T -> right);
}

void InOrderTraverse(Tree T)
{
  if (T == NULL)
    return;

  InOrderTraverse(T -> left);
  printf("%d ", T -> val);
  InOrderTraverse(T -> right);
}

void PostOrderTraverse(Tree T)
{
  if (T == NULL)
    return;

  PostOrderTraverse(T -> left);
  PostOrderTraverse(T -> right);
  printf("%d ", T -> val);
}

Tree CreateTree()
{
  Tree T;

  T = NewNode(9);
  T -> left = NewNode(6);
  T -> right = NewNode(-3);
  T -> right -> left = NewNode(-6);
  T -> right -> right = NewNode(2);
  T -> right -> right -> left = NewNode(2);
  T -> right -> right -> left -> left = NewNode(-6);
  T -> right -> right -> left -> right = NewNode(-6);
  T -> right -> right -> left -> left -> left = NewNode(-6);

  // int Len, i;
  // int Array[] = {2, -1};
  // int Array[] = {8, 7, 4, 10, 9, 12};;

  // T = NULL;
  // Len = sizeof(Array) / sizeof(Array[0]);
  // Len = 0;
  // for (i = 0; i < Len; ++i)
  //   T = Insert(Array[i], T);
    // T = Insert(rand() % 1024, T);

  return T;
}

void MakeEmpty(Tree T)
{
  if (T)
  {
    MakeEmpty(T -> left);
    MakeEmpty(T -> right);
    free(T);
  }

  return;
}

int main(int argc, char const *argv[])
{
	Tree T;
	int MaxPathSum;

	T = CreateTree();

	PreOrderTraverse(T);
	printf("\n");

	InOrderTraverse(T);
	printf("\n");

	PostOrderTraverse(T);
	printf("\n");

	MaxPathSum = maxPathSum(T);
	printf("%d\n", MaxPathSum);

	return 0;
}