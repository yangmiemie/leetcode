// Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

// get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
// set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

#include <stdio.h>
#include <stdlib.h>

#define SIZE 2
typedef struct LruItem* LruNode;
typedef struct LruRecord* LruList;

#define ElementType LruNode
typedef struct HashListNode* HashPosition;

struct HashListNode
{
	ElementType Element;
	HashPosition Next;
};

struct HashTbl
{
	int Capacity;
	HashPosition* HashList;
};

typedef struct HashTbl* HashTable;

struct LruItem 
{
	int Key;
	int Value;
	LruNode Next;
	LruNode Prev;
};

struct LruRecord
{
	LruNode Head;
	LruNode Last;
	int Size;
	int Capacity;
	HashTable HT;
};

HashTable InitHashTable(int Capacity)
{
	HashTable HT;
	int i;

	HT = malloc(sizeof(struct HashTbl));
	HT -> Capacity = Capacity;
	HT -> HashList = malloc(sizeof(HashPosition) * Capacity);

	for (i = 0; i < Capacity; ++i)
	{
		HT -> HashList[i] = malloc(sizeof(struct HashListNode));
		HT -> HashList[i] -> Next = NULL;
	}
		
	return HT;
}

int Hash(int Key, int HashTableSize)
{
	return Key % HashTableSize;
}

HashPosition Find(HashTable HT, int Key)
{
	HashPosition HP, Node;

	HP = HT -> HashList[Hash(Key, HT -> Capacity)];
	Node = HP -> Next;

	while (Node != NULL && Node -> Element -> Key != Key)
		Node = Node -> Next;

	return Node;
}

void Insert(HashTable HT, ElementType Node)
{
	HashPosition P, NewCell;

	P = Find(HT, Node -> Key);
	if (P == NULL)
	{
		NewCell = malloc(sizeof(struct HashListNode));
		NewCell -> Element = Node;
		NewCell -> Next = HT -> HashList[Hash(Node -> Key, HT -> Capacity)] -> Next;
		HT -> HashList[Hash(Node -> Key, HT -> Capacity)] -> Next = NewCell;
	}
}

void Delete(HashTable HT, int Key)
{
	HashPosition HP, Node, PreNode;

	HP = HT -> HashList[Hash(Key, HT -> Capacity)];
	Node = HP -> Next;

	while (Node != NULL && Node -> Element -> Key != Key)
	{
		if (Node -> Element -> Key == Key)
		{
			PreNode -> Next = Node -> Next;
			free(Node);
			return;
		}

		PreNode = Node;
		Node = Node -> Next;
	}
}

void Destroy(HashTable HT)
{
	int i;
	HashPosition HP, Node, PreNode;

	for (i = 0; i < HT -> Capacity; ++i)
	{
		HP = HT -> HashList[i];
		Node = HP -> Next;
		while (Node != NULL)
		{
			PreNode = Node;
			Node = Node -> Next;
			free(PreNode);		
		}
	}

	free(HT -> HashList);
	free(HT);
}

void PrintHT(HashTable HT)
{
	int i;
	HashPosition HP, Node;

	for (i = 0; i < HT -> Capacity; ++i)
	{
		HP = HT -> HashList[i];
		Node = HP -> Next;
		printf("%d: ", i);
		while (Node != NULL)
		{
			printf("(%d, %d) ", Node -> Element -> Key, Node -> Element -> Value);
			Node = Node -> Next;			
		}
		printf("\n");
	}
	printf("\n");
}

LruNode GetNodeOfKey(LruList List, int Key)
{
	LruNode Node;
	HashPosition HP;
	// for (Node = List -> Head -> Next; Node != NULL; Node = Node -> Next)
	// 	if (Node -> Key == Key)
	// 		return Node;

	HP = Find(List -> HT, Key);
	if (HP == NULL)
		return NULL;

	return HP -> Element;
}

LruNode NewLruNode(int Key, int Value)
{
	LruNode Node;

	Node = malloc(sizeof(struct LruItem));
	Node -> Key = Key;
	Node -> Value = Value;
	Node -> Next = Node -> Prev = NULL;

	return Node;	
}

void RemoveToFirst(LruList List, LruNode NewNode)
{
	if (List -> Last == NewNode)
		List -> Last = NewNode -> Prev;

	if (NewNode -> Prev != NULL)
		NewNode -> Prev -> Next = NewNode -> Next;

	if (NewNode -> Next != NULL)
		NewNode -> Next -> Prev = NewNode -> Prev;
	
	NewNode -> Next = List -> Head -> Next;
	NewNode -> Prev = List -> Head;

	if (List -> Head -> Next != NULL)
		List -> Head -> Next -> Prev = NewNode;
	
	List -> Head -> Next = NewNode;

	if (List -> Size == 1)
		List -> Last = NewNode;
}

void AddNodeToList(LruList List, int Key, int Value)
{
	LruNode Node, NewNode;

	if (List -> Size == List -> Capacity)
	{
		Node = List -> Last;
		List -> Last = List -> Last -> Prev;
		List -> Last -> Next = NULL;
		--List -> Size;
		Delete(List -> HT, Node -> Key);
		free(Node);
	}	

	++List -> Size;
	NewNode = NewLruNode(Key, Value);
	Insert(List -> HT, NewNode);
	RemoveToFirst(List, NewNode);
}

void DestroyList(LruList List)
{
	LruNode Node, TmpNode;

	for (Node = List -> Head -> Next; Node != NULL; )
	{
		TmpNode = Node;		
		Node = Node -> Next;
		free(TmpNode);
	}

	free(List -> Head);
	// free(List);
}

void PrintList(LruList List)
{
	LruNode Node;

	for (Node = List -> Head -> Next; Node != NULL; Node = Node -> Next)
		printf("(%d,%d) ", Node -> Key, Node -> Value);

	for (Node = List -> Last; Node != List -> Head; Node = Node -> Prev)
		printf("(%d,%d) ", Node -> Key, Node -> Value);

	printf(", First is (%d,%d), Last is (%d,%d)\n", List -> Head -> Next -> Key, List -> Head -> Next -> Value, List -> Last -> Key, List -> Last -> Value);
}

static LruList TheList;

void lruCacheInit(int capacity) {
	TheList = malloc(sizeof(struct LruRecord));

	TheList -> Size = 0;
	TheList -> Capacity = capacity;
	TheList -> Head = NewLruNode(-1, -1);
	TheList -> Last = NULL;
	TheList -> HT = InitHashTable(SIZE);
}

void lruCacheFree() {
	Destroy(TheList -> HT);
	DestroyList(TheList);
}

int lruCacheGet(int key) {
	LruNode Node;

	Node = GetNodeOfKey(TheList, key);
	if (Node == NULL)
		return -1;

	RemoveToFirst(TheList, Node);
	return Node -> Value;
}
    
void lruCacheSet(int key, int value) {
	LruNode Node, TmpNode;

	Node = GetNodeOfKey(TheList, key);
	if (Node == NULL)
		AddNodeToList(TheList, key, value);
	else
	{
		TmpNode = Node -> Prev;
		Node -> Prev -> Next = Node -> Next;
		if (Node -> Next != NULL)
			Node -> Next -> Prev = TmpNode;
		Node -> Value = value;

		RemoveToFirst(TheList, Node);
	}
}

int main(int argc, char const *argv[])
{
	int Size = 3;
	int Value;

// 2,[set(2,1),set(1,1),get(2),set(4,1),get(1),get(2)]
// 3,[set(1,1),set(2,2),set(3,3),set(4,4),get(4),get(3),get(2),get(1),set(5,5),get(1),get(2),get(3),get(4),get(5)]

	lruCacheInit(Size);
	lruCacheSet(1, 1);
	lruCacheSet(2, 2);
	lruCacheSet(3, 3);
	lruCacheSet(4, 4);

	PrintList(TheList);
	Value = lruCacheGet(4);
	printf("%d\n", Value);
	PrintList(TheList);

	Value = lruCacheGet(3);
	printf("%d\n", Value);
	PrintList(TheList);

	Value = lruCacheGet(2);
	printf("%d\n", Value);
	PrintList(TheList);

	Value = lruCacheGet(1);
	printf("%d\n", Value);
	PrintList(TheList);

	lruCacheSet(5, 5);
	PrintList(TheList);

	Value = lruCacheGet(1);
	PrintList(TheList);
	printf("%d\n", Value);
	Value = lruCacheGet(2);
	PrintList(TheList);
	printf("%d\n", Value);
	PrintList(TheList);
	Value = lruCacheGet(3);
	PrintList(TheList);
	printf("%d\n", Value);
	Value = lruCacheGet(4);
	PrintList(TheList);
	printf("%d\n", Value);
	Value = lruCacheGet(5);
	PrintList(TheList);
	printf("%d\n", Value);

	// lruCacheSet(4, 1);
	// Value = lruCacheGet(1);
	// printf("%d\n", Value);

	// Value = lruCacheGet(2);
	// printf("%d\n", Value);

	// lruCacheSet(4, 16);
	// lruCacheSet(5, 25);
	// lruCacheSet(2, 8);
	// lruCacheSet(1, 11);

	// lruCacheInit(Size);
	// lruCacheSet(1, 1);
	// PrintHT(TheList -> HT);
	// lruCacheSet(2, 4);
	// PrintHT(TheList -> HT);
	// lruCacheSet(3, 9);
	// PrintHT(TheList -> HT);
	// lruCacheSet(4, 16);
	// PrintHT(TheList -> HT);
	// lruCacheSet(5, 25);
	// PrintHT(TheList -> HT);
	// lruCacheSet(2, 8);
	// PrintHT(TheList -> HT);
	// lruCacheSet(1, 11);
	// PrintHT(TheList -> HT);

	// Value = lruCacheGet(1);
	// printf("%d\n", Value);
	lruCacheFree();

	return 0;
}