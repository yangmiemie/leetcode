// Reverse a linked list from position m to n. Do it in-place and in one-pass.

// For example:
// Given 1->2->3->4->5->NULL, m = 2 and n = 4,

// return 1->4->3->2->5->NULL.

// Note:
// Given m, n satisfy the following condition:
// 1 ≤ m ≤ n ≤ length of list.

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

struct ListNode* reverseBetween(struct ListNode* head, int m, int n) {
  if (head == NULL || head -> next == NULL)
    return head;

  if (m == n)
    return head;

  int i;
  Position PtrPre, PtrCur, PtrNext;
  Position PtrBegin, PtrEnd;
  Position PtrSubBegin, PtrSubEnd;

  i = 1;
  PtrPre = head;

  while (i < m)
  {
    PtrBegin = PtrPre;
    PtrPre = PtrPre -> next;
    ++i;
  }

  PtrSubBegin = PtrPre;
  PtrCur = PtrPre -> next;
  while (i < n)
  {
    PtrNext = PtrCur -> next;
    PtrCur -> next = PtrPre;
    PtrPre = PtrCur;
    PtrCur = PtrNext;
    ++i;
  }

  PtrSubEnd = PtrPre;
  PtrEnd = PtrCur;

  if (m != 1)
    PtrBegin -> next = PtrSubEnd;
  else
    head = PtrSubEnd;
  
  PtrSubBegin -> next = PtrEnd;

  return head;
}

int main(int argc, char const *argv[])
{
  List L1, L2, L;

  L1 = CreateEvenList(1);
  L2 = CreateOddList(10);
  PrintList(L1);
  PrintList(L2);

  L1 = reverseBetween(L1, 1, 2);
  // L = mergeTwoLists(L1, L2);
  PrintList(L1);
  return 0;
}