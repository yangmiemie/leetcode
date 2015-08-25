// Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the difference between i and j is at most k.

#include <stdio.h>
#include <stdlib.h>

#define Prime 17

typedef struct IndexListNode* Position;
typedef struct IndexListNode* List;
typedef struct HashTbl* HashTable;

struct IndexListNode
{
	int Index;
	int Value;
	Position Next;
};

struct HashTbl
{
	int TableSize;
	List* TheList;
};

Position NewNode(int Value, int Index)
{
	Position P;

	P = malloc(sizeof(struct IndexListNode));
	P -> Value = Value;
	P -> Index = Index;
	P -> Next = NULL;

	return P;
}

HashTable Initialze(int Capacity)
{
	HashTable HT;
	int i;

	HT = malloc(sizeof(struct HashTbl));
	HT -> TableSize = Capacity;
	HT -> TheList = malloc(sizeof(Position) * Capacity);

	for (i = 0; i < Capacity; ++i)
	{
		HT -> TheList[i] = NewNode(-1, -1);
	}

	return HT;
}

int Hash(int Value)
{
	while (Value < 0)
		Value += Prime;

	return Value % Prime;
}

int FindAndInsert(HashTable HT, int Value, int Index, int k)
{
	List L;
	Position P;

	L = HT -> TheList[Hash(Value)];
	P = L -> Next;

	for (; P != NULL; P = P -> Next)
	{
		if (P -> Value == Value)
		{
			if (Index - P -> Index <= k)
				return 1;
			else
				break;
		}
	}

	P = NewNode(Value, Index);
	P -> Next = L -> Next;
	L -> Next = P;
	return 0;
}

void DestroyList(List L)
{
	if (L == NULL)
		return;

	Position P1, P2;

	P1 = L;
	while (P1 != NULL)
	{
		P2 = P1 -> Next;
		free(P1);
		P1 = P2;
	}
}

void Destroy(HashTable HT)
{
	int i;

	for (i = 0; i < HT -> TableSize; ++i)
	{
		DestroyList(HT -> TheList[i]);
	}

	free(HT);
}

int containsNearbyDuplicate(int* nums, int numsSize, int k) {
	HashTable HT;
	Position P;
	int i, j, Value;

	if (nums == NULL || numsSize <= 1)
		return 0;
	
	HT = Initialze(Prime);
	Value = 0;
	for (i = 0; i < numsSize; ++i)
	{
		if (FindAndInsert(HT, nums[i], i, k) == 1)
		{
			Value = 1;
			break;
		}
	}

	Destroy(HT);
	return Value;
}

int main(int argc, char const *argv[])
{
	int Numbers[] = {1, 2, 3, 11, 4, 12, 13, 2, 1};
	int Len, i;

	Len = sizeof(Numbers) / sizeof(Numbers[0]);

	printf("%d\n", containsNearbyDuplicate(Numbers, Len, 5));
	return 0;
}