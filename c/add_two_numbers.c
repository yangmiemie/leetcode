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

void addTwoNode(struct ListNode *l1, struct ListNode* l2, int carry, int* resCarry, int*resVal)
{
	int val2, sum;

	val2 = l2 == NULL ? 0 : l2 -> val;
	sum = carry + l1 -> val + val2;
	*resCarry = sum >= 10 ? 1 : 0;
	*resVal = *resCarry > 0 ? sum - 10 : sum;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
  struct ListNode *head, *list, *node, *l;
  int value, carry;

  if (l1 == NULL)
  	return l2;

  if (l2 == NULL)
  	return l1;

  addTwoNode(l1, l2, 0, &carry, &value);
  head = NewNode(value);
  list = head;
  l1 = l1 -> next;
  l2 = l2 -> next;

  while (l1 != NULL && l2 != NULL)
  {
  	addTwoNode(l1, l2, carry, &carry, &value);
  	node = NewNode(value);
  	list -> next = node;
  	list = list -> next;
  	l1 = l1 -> next;
  	l2 = l2 -> next;
  }

  l = l1 == NULL ? l2 : l1;
  while(l != NULL)
  {
  	addTwoNode(l, NULL, carry, &carry, &value);
  	node = NewNode(value);
  	list -> next = node;
  	list = list -> next;
  	l = l -> next;
  }

  if (carry > 0)
  {
  	node = NewNode(carry);
  	list -> next = node;
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