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

struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;

struct TreeNode* invertTree(struct TreeNode* root) {
    if (root == NULL)
    	return NULL;

    Tree T;

    T = root -> right;
    root -> right = root -> left;
    root -> left = T;

    invertTree(root -> left);
    invertTree(root -> right);

    return root;
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
  int Len, i;
  // int Array[] = {1, 2};
  int Array[] = {8, 7, 4, 10, 9, 12};;

  T = NULL;
  Len = sizeof(Array) / sizeof(Array[0]);
  // Len = 0;
  for (i = 0; i < Len; ++i)
    T = Insert(Array[i], T);
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

	T = CreateTree();

	PreOrderTraverse(T);
  printf("\n");

  InOrderTraverse(T);
  printf("\n");

  PostOrderTraverse(T);
  printf("\n");

  T = invertTree(T);

  PreOrderTraverse(T);
  printf("\n");

  InOrderTraverse(T);
  printf("\n");

  PostOrderTraverse(T);
  printf("\n");

	return 0;
}