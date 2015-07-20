/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
// typedef struct ListNode* ListNode;
typedef struct ListNode* Position;

struct ListNode {
	int val;
	struct ListNode* next;
};

Position NewNode(int value)
{
	Position P;

	P = malloc(sizeof(struct ListNode));
	P -> val = value;
	P -> next = NULL;
	return P;
}

struct ListNode* initList(int* array, int size)
{
	if (size <= 0)
		return NULL;

	Position head, list, node;
	head = NewNode(array[0]);
	list = head;
	int i;

	for (i = 1; i < size; ++i)
	{
		node = NewNode(array[i]);
		list -> next = node;
		list = list -> next;
	}

	return head;
}

void printList(struct ListNode* list)
{
	while (list != NULL)
	{
		printf("%d ", list -> val);
		list = list -> next;
	}
	printf("\n");;
}

void freeList(struct ListNode *list)
{
	Position node;

	while (list != NULL)
	{
		node = list;
		free(node);
		list = list -> next;
	}
}

int getValueAndMoveNext(struct ListNode** l1)
{
	int value;

	value = 0;
	if (*l1)
	{
		value = (*l1) -> val;
		*l1 = (*l1) -> next;
	}

	return value;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
  struct ListNode *head, **list;
  int value, carry, sum, val1, val2;

  if (l1 == NULL)
  	return l2;

  if (l2 == NULL)
  	return l1;

  carry = 0;
  head = NULL;
  list = &head;
  while (l1 != NULL || l2 != NULL)
  {
  	val1 = getValueAndMoveNext(&l1);
  	val2 = getValueAndMoveNext(&l2);
  	sum = carry + val1 + val2;
  	carry = sum >= 10 ? 1 : 0;
  	value = sum >= 10 ? sum - 10 : sum;
  	*list = NewNode(value);
  	list = &((*list) -> next);
  }

  if (carry > 0)
  {
  	*list = NewNode(carry);
  }

  return head;  
}



void testListArray(struct ListNode* list, int* array, int size)
{
	int i;

	for (i = 0; i < size; ++i)
	{
		assert(list -> val == array[i]);
		list = list -> next;
	}

	assert(list == NULL);
}

void testCase(int* a1, int len1, int* a2, int len2, int* res, int resLen)
{
	struct ListNode *l1, *l2, *list;

	l1 = initList(a1, len1);
	l2 = initList(a2, len2);

	list = addTwoNumbers(l1, l2);
	testListArray(list, res, resLen);

	freeList(l1);
	freeList(l2);
	freeList(list);
}

void testWithSameLength()
{
	int a1[] = {2, 4, 3};
	int a2[] = {5, 6, 4};
	int res[] = {7, 0, 8};

	testCase(a1, sizeof(a1) / sizeof(a1[0]), a2, sizeof(a2) / sizeof(a2[0]), res, sizeof(res) / sizeof(res[0]));
}

void testWithDifferentLength()
{
	int a1[] = {2, 4, 3};
	int a2[] = {5, 6, 9, 8};
	int res[] = {7, 0, 3, 9};

	testCase(a1, sizeof(a1) / sizeof(a1[0]), a2, sizeof(a2) / sizeof(a2[0]), res, sizeof(res) / sizeof(res[0]));
}

void testWithEmptyArray()
{
	int a1[] = {2, 4, 3};
	int a2[] = {};
	int res[] = {2, 4, 3};

	testCase(a1, sizeof(a1) / sizeof(a1[0]), a2, sizeof(a2) / sizeof(a2[0]), res, sizeof(res) / sizeof(res[0]));
}

int main(int argc, char const *argv[])
{
	// (2 -> 4 -> 3) + (5 -> 6 -> 4)
	testWithDifferentLength();
	testWithSameLength();
	testWithEmptyArray();
	return 0;
}