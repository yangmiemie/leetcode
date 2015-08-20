// Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

// If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

// You may not alter the values in the nodes, only nodes itself may be changed.

// Only constant memory is allowed.

// For example,
// Given this linked list: 1->2->3->4->5

// For k = 2, you should return: 2->1->4->3->5

// For k = 3, you should return: 3->2->1->4->5

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

int GetLengthOfList(List L)
{
  int i;

  i = 0;
  while (L != NULL)
  {
    L = L -> next;
    ++i;
  }

  return i;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
  if (k <= 1 || head == NULL || head -> next == NULL)
    return head;

  int RoundOfReverse, Len;
  int i, j;
  List NewList;
  Position PtrBeforeEnd, PtrSubBegin, PtrPre, PtrCur, PtrNext;

  Len = GetLengthOfList(head);

  if (Len < k)
    return head;

  RoundOfReverse = Len / k;
  PtrPre = head;
  PtrCur = head -> next;

  for (i = 0; i < RoundOfReverse; ++i)
  {
    PtrSubBegin = PtrPre;
    for (j = 1; j < k; ++j)
    {
      PtrNext = PtrCur -> next;
      PtrCur -> next = PtrPre;
      PtrPre = PtrCur;
      PtrCur = PtrNext;
    }

    if (i == 0)
      NewList = PtrPre;
    else
    {
      PtrBeforeEnd -> next = PtrPre;
    }

    PtrSubBegin -> next = PtrCur;
    PtrBeforeEnd = PtrSubBegin;

    PtrPre = PtrCur;
    if (PtrCur != NULL)
      PtrCur = PtrCur -> next;
  }

  return NewList;
}

int main(int argc, char const *argv[])
{
  List L1;

  L1 = CreateEvenList(3);
  PrintList(L1);

  L1 = reverseKGroup(L1, 2);
  PrintList(L1);
  return 0;
}