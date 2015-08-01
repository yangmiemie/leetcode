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

#include "lib/tree.h"

typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;

#define ElementType Position
#define SIZE 2

struct StackRecord
{
  int Size;
  int Capacity;
  ElementType* Next;
};

typedef struct StackRecord* Stack;
#define SIZE 2

Stack Initialize()
{
  Stack S;

  S = malloc(sizeof(struct StackRecord));
  S -> Size = 0;
  S -> Capacity = SIZE;
  S -> Next = malloc(sizeof(ElementType) * S -> Capacity);

  return S;
}

int IsEmpty(Stack S)
{
  return S -> Size == 0;
}

int IsFull(Stack S)
{
  return S -> Capacity == S -> Size;
}

ElementType Pop(Stack S)
{
  if (IsEmpty(S))
  {
    fprintf(stderr, "Empty Stack\n");
    exit(1);
  }

  return S -> Next[--S -> Size];
}

void Push(Stack S, ElementType X)
{
  if (IsFull(S))
  {
    S -> Next = realloc(S -> Next, sizeof(ElementType) * S -> Capacity * 2);
    S -> Capacity *= 2;
  }

  S -> Next[S -> Size++] = X;
}

void Destroy(Stack S)
{
  free(S -> Next);
  free(S);
}

int GetPathToNode(Stack S, Tree Root, Position Node)
{
	if (Root == NULL)
		return 0;

	int LeftFound, RightFound;

	Push(S, Root);
	if (Node == Root)
		return 1;

	LeftFound = GetPathToNode(S, Root -> left, Node);
	if (LeftFound == 0)
		RightFound = GetPathToNode(S, Root -> right, Node);

	if (LeftFound || RightFound)
		return 1;

	Pop(S);
	return 0;
}

Position GetMaxCommonNode(Stack S1, Stack S2)
{
	int i;

	i = 0;
	while (!IsEmpty(S1) && !IsEmpty(S2))
	{
		if (S1 -> Next[i] == S2 -> Next[i])
			++i;
		else
			break;
	}

	return S1 -> Next[i -1];
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
	if (root == NULL || p == NULL || q == NULL)
		return NULL;

	Stack S1, S2;
	Position P;
	S1 = Initialize();
	S2 = Initialize();

	if (!GetPathToNode(S1, root, p) || !GetPathToNode(S2, root, q))
		return NULL;

	P = GetMaxCommonNode(S1, S2);
	Destroy(S1);
	Destroy(S2);

	return P;
}

int main(int argc, char const *argv[])
{
  Tree T;
  Position P, P1, P2;
  T = CreateTree();

  PreOrderTraverse(T);
  printf("\n");

  InOrderTraverse(T);
  printf("\n");

  PostOrderTraverse(T);
  printf("\n");

  P1 = Find(T, 12);
  P2 = Find(T, 9);
 
  P = lowestCommonAncestor(T, P2, P1);
  printf("Position = %d\n", P -> val);
	return 0;
}