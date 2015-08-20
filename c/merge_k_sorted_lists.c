// Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdio.h>
#include <stdlib.h>

#include "lib/list.h"

typedef struct ListNode* Position;
typedef struct ListNode* List;

List MergeSortedList(List L1, List L2)
{
  if (L1 == NULL)
    return L2;

  if (L2 == NULL)
    return L1;

  List NewList;
  Position P;

  if (L1 -> val > L2 -> val)
  {
    NewList = L2;
    L2 = L2 -> next;
  }
  else
  {
    NewList = L1;
    L1 = L1 -> next;
  }

  P = NewList;

  while (L1 != NULL && L2 != NULL)
  {
    if (L1 -> val > L2 -> val)
    {
      P -> next = L2;
      L2 = L2 -> next;
    }
    else
    {
      P -> next = L1;
      L1 = L1 -> next;
    }

    P = P -> next;
  }

  if (L1 != NULL)
    P -> next = L1;

  if (L2 != NULL)
    P -> next = L2;

  return NewList;
}

List MergeSortLists(List* L, int Size)
{
  if (Size == 0)
    return NULL;

  if (Size == 1)
    return *L;

  List L1, L2;
  L1 = MergeSortLists(L, Size / 2);
  L2 = MergeSortLists(L + Size / 2, Size - Size / 2);

  return MergeSortedList(L1, L2);
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
  if (lists == NULL || listsSize == 0)
    return NULL;

  return MergeSortLists(lists, listsSize);
}

int main(int argc, char const *argv[])
{
  List L1, L2, L3, L4, L;
  List* Lists;
  int Size;

  L1 = CreateEvenList(10);
  L2 = CreateOddList(10);
  L3 = CreateOddList(5);
  L4 = CreateEvenList(5);
  PrintList(L1);
  PrintList(L2);
  PrintList(L3);
  PrintList(L4);

  // L = MergeSortedList(L1, L2);
  // PrintList(L);

  Size = 4;
  Lists = malloc(sizeof(List) * Size);
  Lists[0] = L1;
  Lists[1] = L2;
  Lists[2] = L3;
  Lists[3] = L4;
  L = mergeKLists(Lists, Size);
  PrintList(L);
  return 0;
}