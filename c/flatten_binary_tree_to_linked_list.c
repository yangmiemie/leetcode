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

struct TreeNode
{
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;

#define ElementType Position
#define SIZE 2

struct QueueRecord
{
	int Capacity;
	int Rear;
	int Front;
	ElementType* Next;
};

typedef struct QueueRecord* Queue;

Queue Initialize()
{
	Queue Q;

	Q = malloc(sizeof(struct QueueRecord));
	Q -> Capacity = SIZE;
	Q -> Rear = Q -> Front = 0;
	Q -> Next = malloc(sizeof(ElementType) * SIZE);

	return Q;
}

int Succ(Queue Q, int Index)
{
	if (++Index >= Q -> Capacity)
		return Index % Q -> Capacity;

	return Index;
}

int IsEmpty(Queue Q)
{
	return Q -> Rear == Q -> Front;
}

int IsFull(Queue Q)
{
	return Succ(Q, Q -> Rear) == Q -> Front;
}

ElementType Dequeue(Queue Q)
{
	if (IsEmpty(Q))
	{
		fprintf(stderr, "Empty Queue\n");
		exit(1);
	}

	return Q -> Next[Q -> Front++];
}

Queue Rearrange(Queue Q)
{
	ElementType* Buffer;
	int i;

	Buffer = malloc(sizeof(ElementType) * Q -> Capacity * 2);
	i = 0;

	while (!IsEmpty(Q))
		Buffer[i++] = Dequeue(Q);

	Q -> Capacity *= 2;
	Q -> Front = 0;
	Q -> Rear = i;
	free(Q -> Next);
	Q -> Next = Buffer;

	return Q;
}

void Enqueue(Queue Q, ElementType X)
{
	if (IsFull(Q))
	{
		Q = Rearrange(Q);
	}

	Q -> Next[Q -> Rear++] = X;
}

void Destroy(Queue Q)
{
	free(Q -> Next);
	free(Q);
}

void PreorderTraversal(Tree T, Queue Q)
{
	if (T == NULL)
		return;

	Enqueue(Q, T);
	PreorderTraversal(T -> left, Q);
	PreorderTraversal(T -> right, Q);
}

void flatten(struct TreeNode* root) {
  if (root == NULL)
  	return;

  Queue Q;

  Q = Initialize();
  PreorderTraversal(root, Q);

  root = Dequeue(Q);

  while (!IsEmpty(Q))
  {
  	root -> right = Dequeue(Q);
  	root -> left = NULL;
  	root = root -> right;
  }

  Destroy(Q);
}

// void TestQueue()
// {
// 	int i;
// 	Queue Q;

// 	Q = Initialize();
// 	for (i = 0; i < 100; ++i)
// 		Enqueue(Q, i);

// 	while (!IsEmpty(Q))
// 		printf("%d ", Dequeue(Q));
// 	printf("\n");
// }



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
  // int Array[] = {8, 7, 4, 10, 9, 12};;

  // T = NewNode(1);
  // T -> left = NewNode(2);
  // T = NULL;
  // Len = sizeof(Array) / sizeof(Array[0]);
  // Len = 100;
  // for (i = 0; i < Len; ++i)
  // //   T = Insert(Array[i], T);
  //   T = Insert(rand() % 1024, T);

  return T;
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

  struct TreeNode node1, node2;
  node1.val = 1;
  node1.left = node1.right = NULL;

  node2.val = 2;
  node2.left = node2.right = NULL;
  node1.left = &node2;

  flatten(&node1);

  T = &node1;
  while (T)
  {
  	printf("%d ", T -> val);
  	T = T -> right;
  }	

  printf("\n");
  return 0;
}