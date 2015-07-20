/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x): val(x), next(NULL) {}
};

class Solution {
	public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head, **list, *node, *l;
        int sum, value, carry, val1, val2;

        if (l1 == NULL)
        	return l2;

        if (l2 == NULL)
        	return l1;

        head = NULL;
        list = &head;
        while (l1 != NULL || l2 != NULL)
        {
        	val1 = getValueAndMoveNext(l1);
        	val2 = getValueAndMoveNext(l2);

        	sum = val1 + val2 + carry;
        	value = sum >= 10 ? sum - 10 : sum;
        	carry = sum >= 10 ? 1 : 0;

        	node = new ListNode(value);
        	*list = node;
        	list = &(node -> next);
         }

        if (carry > 0)
        {
        	node = new ListNode(carry);
        	*list = node;
        }

        return head;
    }

    ListNode* initList(int* array, int size)
		{
			if (size <= 0)
				return NULL;

			ListNode* head, *list, *node;
			head = new ListNode(array[0]);
			list = head;

			for (int i = 1; i < size; ++i)
			{
				node = new ListNode(array[i]);
				list -> next = node;
				list = list -> next;
			}

			return head;
		}

		void printList(ListNode* list)
		{
			while (list != NULL)
			{
				cout << list -> val << " ";	
				list = list -> next;
			}
			cout << endl;
		}

		void freeList(ListNode *list)
		{
			ListNode* node;

			while (list != NULL)
			{
				node = list;
				delete(node);
				list = list -> next;
			}
		}

  private:
  	int getValueAndMoveNext(ListNode* &list)
  	{
  		int value = 0;

  		if (list)
  		{
  			value = list -> val;
  			list = list -> next;
  		}

  		return value;
  	}
};


void testListArray(ListNode* list, int* array, int size)
{
	for (int i = 0; i < size; ++i)
	{
		assert(list -> val == array[i]);
		list = list -> next;
	}

	assert(list == NULL);
}

void testCase(int* a1, int len1, int* a2, int len2, int* res, int resLen)
{
	Solution s;
	ListNode *l1, *l2, *list;

	l1 = s.initList(a1, len1);
	l2 = s.initList(a2, len2);

	list = s.addTwoNumbers(l1, l2);
	testListArray(list, res, resLen);

	s.freeList(l1);
	s.freeList(l2);
	s.freeList(list);
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