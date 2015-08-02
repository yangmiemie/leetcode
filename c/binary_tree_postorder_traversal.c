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

#include <stdlib.h>
#include <stdio.h>

#include "lib/tree.h"

#define SIZE 8

typedef struct Stack* Stack;
typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;
typedef struct PostOrderNode* PNode;

#define ElementType PNode

struct PostOrderNode {
	int isFirst;
	Position P;
};

struct Stack {
	ElementType* next;
	int size;
	int capacity;
};


Stack initialize()
{
	Stack S;

	S = malloc(sizeof(struct Stack));
	S -> next = malloc(SIZE * sizeof(ElementType));
	S -> size = 0;
	S -> capacity = SIZE;
	return S;
}

ElementType pop(Stack S)
{
	return S -> next[--S -> size];
}

int isEmpty(Stack S)
{
	return S -> size == 0;
}

void push(Stack S, ElementType value)
{
	if (S -> size == S -> capacity)
	{
		S -> next = realloc(S -> next, S -> capacity * 2 * sizeof(ElementType));
		S -> capacity *= 2;
	}

	S -> next[S -> size++] = value;
}

void destory(Stack S)
{
	free(S -> next);
	free(S);
}

void pushBuffer(int** buffer, int value, int *i, int *capacity)
{
	if (*i == *capacity)
	{
		*buffer = realloc(*buffer, *capacity * 2 * sizeof(int));
		*capacity = *capacity * 2;
	}

	(*buffer)[(*i)++] = value;
}

PNode NewPNode(Position P)
{
	PNode node;

	node = malloc(sizeof(struct PostOrderNode));
	node -> isFirst = 1;
	node -> P = P;

	return node;
}

int* postorderTraversal(struct TreeNode* root, int* returnSize) {
		if (root == NULL)
		{
			returnSize = 0;
			return NULL;
		}

    Stack S;
    Tree T;
    int* buffer;
    int i, capacity;
		PNode node;
    
    buffer = malloc(sizeof(int) * SIZE);
    capacity = SIZE;
    i = 0;

    S = initialize();
    push(S, NewPNode(root));
    while(!isEmpty(S))
    {
    	node = pop(S);

    	if (node -> isFirst)
    	{
    		node -> isFirst = 0;
    		push(S, node);

    		if (node -> P -> right)
	    		push(S, NewPNode(node -> P -> right));
	    	if (node -> P -> left)
	    		push(S, NewPNode(node -> P -> left));
    	}
    	else
    	{
    		// printf("%d ", node -> P -> val);
    		pushBuffer(&buffer, node -> P -> val, &i, &capacity);
    		free(node);
    	}
    }

    *returnSize = i;
    return buffer;
}

int main(int argc, char const *argv[])
{
	Tree T;
	int Len, i, returnSize;
	int* array;

	T = NULL;
	Len = 0;
	for (i = 0; i < Len; ++i)
		T = Insert(rand() % 1024, T);

	PreOrderTraverse(T);
	printf("\n");

	PostOrderTraverse(T);
	printf("\n");

	array = postorderTraversal(T, &returnSize);
	printf("%d\n", returnSize);

	for (i = 0; i < returnSize; ++i)
		printf("%d ", array[i]);
	printf("\n");
	return 0;
}