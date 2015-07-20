/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 19

typedef struct ListNode* Position;
typedef struct HashTbl* HashTable;

struct ListNode
{
	int Key;
	int Value;
	Position Next;
};

struct HashTbl
{
	int TableSize;
	Position *TheList;
};

HashTable Initialize()
{
	HashTable T;
	int i;

	T = malloc(sizeof(struct HashTbl));
	T -> TableSize = SIZE;
	T -> TheList = malloc(SIZE * sizeof(struct ListNode));

	for (i = 0; i < T -> TableSize; ++i)
		T -> TheList[i] = NULL;

	return T;
}

int Hash(int Key,HashTable H)
{
	if (Key < 0)
		Key *= -1;

	return Key % (H -> TableSize);
}

Position Find(int Key, HashTable H)
{
	Position List;
	List = H -> TheList[Hash(Key, H)];

	while (List)
	{
		if (List -> Key == Key)
			return List;

		List = List -> Next;
	}

	return NULL;
}

void Insert(int Key, int Value, HashTable H)
{
	Position P, List, Node;
	int hash;

	P = Find(Key, H);

	if (P != NULL)
		return;

	hash = Hash(Key, H);
	List = H -> TheList[hash];
	Node = malloc(sizeof(struct ListNode));
	Node -> Key = Key;
	Node -> Value = Value;
	Node -> Next = NULL;

	if (List == NULL)
	{
		H -> TheList[hash] = Node;
		return;
	}	

	Node -> Next = List -> Next;
	List -> Next = Node;

	return;
}

void freeHashTbl(HashTable H)
{
	int i;
	Position P1, P2;

	for (i = 0; i < H -> TableSize; ++i)
	{
		P1 = H -> TheList[i];

		while (P1)
		{
			P2 = P1 -> Next;
			free(P1);
			P1 = P2;
		}
	}
}

int* twoSum(int* nums, int numsSize, int target) {
    int i;
    int *Result;
    HashTable H;
    Position P;

    H = Initialize();
    for (i = 0; i < numsSize; ++i)
    {
    	P = Find(target - nums[i], H);

    	if (P != NULL)
    	{
    		Result = malloc(sizeof(int) * 2);
    		Result[0] = P -> Value + 1;
    		Result[1] = i + 1;

    		freeHashTbl(H);
    		return Result;
    	}

    	Insert(nums[i], i, H);
    }

    freeHashTbl(H);
    return NULL;
}

// int* twoSum(int* nums, int numsSize, int target) {
// 	int i, j;
// 	int* Result;

// 	for (i = 0; i < numsSize; ++i)
// 		for (j = i; j < numsSize; ++j)
// 		{
// 			if (nums[i] + nums[j] == target)
// 			{
// 				Result = malloc(sizeof(int) * 2);
// 				Result[0] = i + 1;
// 				Result[1] = j + 1;
// 				return Result;
// 			}
// 		}


// 	return NULL;
// }

int main(int argc, char const *argv[])
{
	int array[] = {1, 14, 13, 2, 3, 4, 5, 7, 8};
	int a1[] = {2, 7, 11, 15};
	int a2[] = {2, 3, 11, 15, 7};
	int a3[] = {2, 3, 11, 15};
	int a4[] = {-3, 4, 3, 90};
	int a5[] = {591,955,829,805,312,83,764,841,12,744,104,773,627,306,731,539,349,811,662,341,465,300,491,423,569,405,508,802,500,747,689,506,129,325,918,606,918,370,623,905,321,670,879,607,140,543,997,530,356,446,444,184,787,199,614,685,778,929,819,612,737,344,471,645,726};
	int *Result;
	HashTable H;
	int i, Len;
	Position P;

	H = Initialize();
	Len = sizeof(array) / sizeof(array[0]);
	for (i = 0; i < Len - 2; ++i)
		Insert(array[i], array[i] * 3, H);

	for (i = 0; i < Len -2; ++i)
	{
		P = Find(array[i], H);
		assert(P -> Value == array[i] * 3);
	}

	for (; i < Len; ++i)
	{
		P = Find(array[i], H);
		assert(P == NULL);		
	}

	Result = twoSum(a1, sizeof(a1) / sizeof(a1[0]), 9);
	assert(Result[0] == 1);
	assert(Result[1] == 2);

	Result = twoSum(a2, sizeof(a2) / sizeof(a2[0]), 9);
	assert(Result[0] == 1);
	assert(Result[1] == 5);

	Result = twoSum(a3, sizeof(a3) / sizeof(a3[0]), 9);
	assert(Result == NULL);

	Result = twoSum(a4, sizeof(a4) / sizeof(a4[0]), 0);
	assert(Result[0] == 1);
	assert(Result[1] == 3);

	Result = twoSum(a5, sizeof(a5) / sizeof(a5[0]), 789);
	printf("%d %d\n", Result[0], Result[1]);
	printf("%d %d", a5[Result[0] - 1], a5[Result[1] - 1]);
	printf("\n");
	return 0;
}