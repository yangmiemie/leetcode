// Implement a trie with insert, search, and startsWith methods.
// Note:
// You may assume that all inputs are consist of lowercase letters a-z.

// Your Trie object will be instantiated and called as such:
// struct TrieNode* node = trieCreate();
// insert(node, "somestring");
// search(node, "key");
// trieFree(node);

#include <stdio.h>
#include <stdlib.h>

#define ElementType char

typedef struct TrieNode* TNode;

struct TrieNode {
	ElementType Value;
	TNode Left, Right, Middle;
	int Tag;
};

TNode NewNode(ElementType Value)
{
	TNode Node;

	Node = malloc(sizeof(struct TrieNode));
	Node -> Left = Node -> Right = Node -> Middle = NULL;
	Node -> Value = Value;
	Node -> Tag = 0;
	return Node;
}

/** Initialize your data structure here. */
struct TrieNode* trieCreate() {
	return NewNode('a');
}

TNode TrieInsert(TNode root, char* word, int k)
{
	if (root == NULL && word[k] != '\0')
		root = NewNode(word[k]);
	// if (word[k] == '\0')
	// 	return;

	if (root -> Value > word[k])
		root -> Left = TrieInsert(root -> Left, word, k);
	else if (root -> Value < word[k])
		root -> Right = TrieInsert(root -> Right, word, k);
	else
	{
		if (word[k + 1] == '\0')
			root -> Tag = 1;
		else
			root -> Middle = TrieInsert(root -> Middle, word, k + 1);			
	}

	return root;
}
/** Inserts a word into the trie. */
void insert(struct TrieNode* root, char* word) {
	root -> Middle = TrieInsert(root -> Middle, word, 0);
}

int TrieSearch(TNode root, char* word, int k)
{
	if (root == NULL)
		return 0;

	if (root -> Value > word[k])
		return TrieSearch(root -> Left, word, k);
	else if (root -> Value < word[k])
		return TrieSearch(root -> Right, word, k);
	else
	{
		if (word[k + 1] == '\0')
		{
			if (root -> Tag == 1)
				return 1;
			else
				return 0;
		}
		else
			return TrieSearch(root -> Middle, word, k + 1);			
	}
}

/** Returns if the word is in the trie. */
int search(struct TrieNode* root, char* word) {
	return TrieSearch(root -> Middle, word, 0);
}

int TrieStartWith(struct TrieNode* root, char* prefix, int k) {
	if (prefix[k] == '\0')
		return 1;
	if (root == NULL)
		return 0;

	if (root -> Value > prefix[k])
		return TrieStartWith(root -> Left, prefix, k);
	else if (root -> Value < prefix[k])
		return TrieStartWith(root -> Right, prefix, k);
	else
		return TrieStartWith(root -> Middle, prefix, k + 1);
}
/** Returns if there is any word in the trie 
    that starts with the given prefix. */
int startsWith(struct TrieNode* root, char* prefix) {
  return TrieStartWith(root -> Middle, prefix, 0);
}

void FreeTrieTree(TNode root)
{
	if (root == NULL)
		return;

	if (root -> Left)
		FreeTrieTree(root -> Left);
	if (root -> Middle)
		FreeTrieTree(root -> Middle);
	if (root -> Right)
		FreeTrieTree(root -> Right);

	free(root);
}

/** Deallocates memory previously allocated for the TrieNode. */
void trieFree(struct TrieNode* root) {
	FreeTrieTree(root -> Middle);
	free(root);
}

int main(int argc, char const *argv[])
{
	struct TrieNode* node = trieCreate();
	// insert(node, "somestring");
	insert(node, "aaaa");
	insert(node, "aaab");
	insert(node, "aaac");
	insert(node, "aaad");
	insert(node, "aaae");
	insert(node, "aaaf"),
	insert(node, "aaag"),
	insert(node, "aaah"),
	insert(node, "aaai"),
	insert(node, "aaaj"),
	insert(node, "aaak"),
	insert(node, "aaal"),
	insert(node, "aaam"),
	insert(node, "aaan"),
	insert(node, "aaao"),
	insert(node, "aaap"),
	insert(node, "aaaq"),
	insert(node, "aaar"),
	insert(node, "aaas"),
	insert(node, "aaat"),
	insert(node, "aaau"),
	insert(node, "aaav"),
	insert(node, "aaaw"),
	insert(node, "aaax"),
	insert(node, "aaay"),
	insert(node, "aaaz"),
	insert(node, "aaa");
	insert(node, "aab");
	insert(node, "aac");
	insert(node, "aad"),
	insert(node, "aae"),
	insert(node, "aaf"),
	insert(node, "aag"),
	insert(node, "aah"),
	insert(node, "aai"),
	insert(node, "aaj"),
	insert(node, "aak"),
	insert(node, "aal"),
	insert(node, "aam"),
	insert(node, "aan"),
	insert(node, "aao"),
	insert(node, "aap"),
	insert(node, "aaq"),
	insert(node, "aar"),
	insert(node, "aas"),
	insert(node, "aat");
	insert(node, "aau");
	insert(node, "aav");
	insert(node, "aaw");
	insert(node, "aax");
	insert(node, "aay");
	insert(node, "aaz");
	int i1 = search(node, "aaaa"),
	i2 = search(node, "aaaaa"),
	i3 = search(node, "aaa"),
	i4 = search(node, "a"),
	i5 = startsWith(node, "aaaa"),
	i6 = startsWith(node, "aaaaa"),
	i7 = startsWith(node, "aaa"),
	i8 = startsWith(node, "a");
	printf("%d %d %d %d %d %d %d %d\n", i1, i2, i3, i4, i5, i6, i7, i8);
	trieFree(node);

	struct TrieNode* T = trieCreate();
	T = trieCreate();
	insert(T, "ab");
	printf("%d\n", search(T, "ab"));
	printf("%d\n", startsWith(T, "ad"));
	trieFree(T);
	return 0;
}