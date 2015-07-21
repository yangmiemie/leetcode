// Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

// Calling next() will return the next smallest number in the BST.

// Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.


/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#include <stdlib.h>
#include <stdio.h>

#define SIZE 8

struct TreeNode {
	int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

typedef struct TreeNode* Tree;

struct BSTIterator {
   int* next;
   int size;
   int capacity;
   int front;
};


void Push(int value, struct BSTIterator* i)
{
	if (i -> size >= i -> capacity)
	{
		i -> next = realloc(i -> next, i -> capacity * 2 * sizeof(int));
		i -> capacity = i -> capacity * 2;
	}	

	i -> next[i -> size++] = value;
	return;
}

int Pop(struct BSTIterator* i)
{
	if (i -> size == i -> front)
		return;

	return i -> next[i -> front++];
}

int isEmpty(struct BSTIterator* i)
{
	return i -> size == i -> front;
}

void InOrderTraverse(struct TreeNode *root, struct BSTIterator* i)
{
	if (root == NULL)
		return;

	InOrderTraverse(root -> left, i);
	Push(root -> val, i);
	InOrderTraverse(root -> right, i);
}

struct BSTIterator *bstIteratorCreate(struct TreeNode *root) {
	struct BSTIterator* i = malloc(sizeof(struct BSTIterator));
	i -> next = malloc(SIZE * sizeof(int));
	i -> size = 0;
	i -> capacity = SIZE;
	i -> front = 0;

	InOrderTraverse(root, i);
	return i;
}

/** @return whether we have a next smallest number */
int bstIteratorHasNext(struct BSTIterator *iter) {
	return !isEmpty(iter);
}

/** @return the next smallest number */
int bstIteratorNext(struct BSTIterator *iter) {
  return Pop(iter);
}

/** Deallocates memory previously allocated for the iterator */
void bstIteratorFree(struct BSTIterator *iter) {
   free(iter -> next);
   free(iter);
}

/**
 * Your BSTIterator will be called like this:
 * struct BSTIterator *i = bstIteratorCreate(root);
 * while (bstIteratorHasNext(i)) printf("%d\n", bstIteratorNext(i));
 * bstIteratorFree(i);
 */
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

int main(int argc, char const *argv[])
{
	int array[50] = {};
	Tree T;
	int i, Len, balanced;
	Len = 50;

	for (i = 0; i < Len; ++i)
		array[i] = rand() % 100;

	T = NULL;
	for (i = 0; i < Len; ++i)
		T = Insert(array[i], T);

	PreOrderTraverse(T);
	printf("\n");

  struct BSTIterator *iter = bstIteratorCreate(T);
	while (bstIteratorHasNext(iter)) 
		printf("%d\n", bstIteratorNext(iter));
	bstIteratorFree(iter);
	return 0;
}

// struct BSTIterator *i = bstIteratorCreate(root);
// while (bstIteratorHasNext(i)) 
// 	printf("%d\n", bstIteratorNext(i));
// bstIteratorFree(i);