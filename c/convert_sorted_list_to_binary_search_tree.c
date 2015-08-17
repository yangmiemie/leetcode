// Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
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

#include "lib/list.h"
#include "lib/tree.h"

// struct TreeNode {
//  int val;
//   struct TreeNode *left;
//   struct TreeNode *right;
// };

#define ElementType int
#define SIZE 4

typedef struct ListNode* Position;
typedef struct ListNode* List;
typedef struct TreeNode* Tree;

ElementType* ConvertListToArray(List Head, int* PtrSize)
{
  int i, Capacity;
  List P;
  ElementType* Array;

  Array = malloc(sizeof(ElementType) * Capacity);
  i = 0;
  Capacity = SIZE;
  for (P = Head; P != NULL; P = P -> next)
  {
    if (i >= Capacity)
    {
      Array = realloc(Array, Capacity * 2 * sizeof(ElementType));
      Capacity *= 2;
    }

    Array[i++] = P -> val;
  }
  
  *PtrSize = i;
  return Array;
}

Tree NewTreeNode(int Value)
{
  Tree T;

  T = malloc(sizeof(struct TreeNode));
  T -> left = T -> right = NULL;
  T -> val = Value;

  return T;
}

Tree SortedArrayToBST(ElementType* Array, int Left, int Right)
{
  if (Left > Right)
    return NULL;

  if (Left == Right)
    return NewTreeNode(Array[Left]);

  Tree T;
  int Mid;
  Mid = (Left + Right) / 2;
  T = NewTreeNode(Array[Mid]);
  T -> left = SortedArrayToBST(Array, Left, Mid - 1);
  T -> right = SortedArrayToBST(Array, Mid + 1, Right);

  return T;
}

struct TreeNode* sortedListToBST(struct ListNode* head) {
  int Size;
  ElementType* Array;
  Tree T;

  if (head == NULL)
    return NULL;

  Array = ConvertListToArray(head, &Size);
  T = SortedArrayToBST(Array, 0, Size - 1);
  free(Array);

  return T;
}

int main(int argc, char const *argv[])
{
  List L;
  Tree T;

  L = CreateList(15);
  PrintList(L);

  T = sortedListToBST(L);
  PreOrderTraverse(T);
  printf("\n");
  InOrderTraverse(T);
  printf("\n");
  PostOrderTraverse(T);
  printf("\n");
  return 0;
}