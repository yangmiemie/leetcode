// Design a data structure that supports the following two operations:

// void addWord(word)
// bool search(word)
// search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

// For example:

// addWord("bad")
// addWord("dad")
// addWord("mad")
// search("pad") -> false
// search("bad") -> true
// search(".ad") -> true
// search("b..") -> true

// Your WordDictionary object will be instantiated and called as such:
// struct WordDictionary* wordDictionary = wordDictionaryCreate();
// addWord(wordDictionary, "word");
// search(wordDictionary, "pattern");
// wordDictionaryFree(wordDictionary);

#include <stdio.h>
#include <stdlib.h>

#define ElementType char
typedef struct TrieNode* TrieTree;

struct TrieNode
{
	ElementType Value;
	int Tag;
	TrieTree Left, Right, Middle;
};

struct WordDictionary {
	TrieTree DicTree;
};


typedef struct WordDictionary* WDict;
/** Initialize your data structure here. */
struct WordDictionary* wordDictionaryCreate() {
	WDict WD;

	WD = malloc(sizeof(struct WordDictionary));
	WD -> DicTree = NULL;

	return WD;
}

TrieTree NewTrieNode(ElementType Value)
{
	TrieTree Tree;

	Tree = malloc(sizeof(struct TrieNode));
	Tree -> Value = Value;
	Tree -> Left = Tree -> Right = Tree -> Middle = NULL;
	Tree -> Tag = 0;

	return Tree;
}

TrieTree AddTrieTree(TrieTree Tree, char* Word, int k)
{
	if (Tree == NULL)
		Tree = NewTrieNode(Word[k]);

	if (Tree -> Value < Word[k])
		Tree -> Right = AddTrieTree(Tree -> Right, Word, k);
	else if (Tree -> Value > Word[k])
		Tree -> Left = AddTrieTree(Tree -> Left, Word, k);
	else
	{
		if (Word[k + 1] == '\0')
			Tree -> Tag = 1;
		else
			Tree -> Middle = AddTrieTree(Tree -> Middle, Word, k + 1);
	}

	return Tree;
}

/** Inserts a word into the data structure. */
void addWord(struct WordDictionary* wordDictionary, char* word) {
	wordDictionary -> DicTree = AddTrieTree(wordDictionary -> DicTree, word, 0);
}

int SearchTrieTree(TrieTree Tree, char* Word, int k)
{
	int Result = 0;
	if (Tree == NULL)
		return 0;

	if (Word[k] == '.' || Tree -> Value > Word[k])
		Result = SearchTrieTree(Tree -> Left, Word, k);

	if ((!Result) && (Word[k] == '.' || Tree -> Value < Word[k]))
		Result = SearchTrieTree(Tree -> Right, Word, k);
	
	if ((!Result) && (Word[k] == '.' || Tree -> Value == Word[k]))
	{
		if (Word[k + 1] == '\0' && Tree -> Tag == 1)
			Result = 1;
		else
			Result = SearchTrieTree(Tree -> Middle, Word, k + 1);
	}

	return Result;
}
/** Returns if the word is in the data structure. A word could
    contain the dot character '.' to represent any one letter. */
int search(struct WordDictionary* wordDictionary, char* word) {
	return SearchTrieTree(wordDictionary -> DicTree, word, 0);
}

void FreeTrieTree(TrieTree Tree)
{
	if (Tree != NULL)
	{
		if (Tree -> Left != NULL)
			FreeTrieTree(Tree -> Left);
		if (Tree -> Right != NULL)
			FreeTrieTree(Tree -> Right);
		if (Tree -> Middle != NULL)
			FreeTrieTree(Tree -> Middle);

		free(Tree);
	}
}

/** Deallocates memory previously allocated for the data structure. */
void wordDictionaryFree(struct WordDictionary* wordDictionary) {
	FreeTrieTree(wordDictionary -> DicTree);
	free(wordDictionary);
}

// addWord("bad")
// addWord("dad")
// addWord("mad")
// search("pad") -> false
// search("bad") -> true
// search(".ad") -> true
// search("b..") -> true

// Your WordDictionary object will be instantiated and called as such:
// struct WordDictionary* wordDictionary = wordDictionaryCreate();
// addWord(wordDictionary, "word");
// search(wordDictionary, "pattern");
// wordDictionaryFree(wordDictionary);

int main(int argc, char const *argv[])
{
	struct WordDictionary* wd = wordDictionaryCreate();
	// addWord(wd, "word");
	// printf("%d\n", search(wd, "pattern")); 
	// wordDictionaryFree(wd);

	addWord(wd, "a");
	// addWord(wd, "dad");
	// addWord(wd, "mad");

	printf("%d\n", search(wd, ".")); 
	// printf("%d\n", search(wd, "z*d")); 
	// printf("%d\n", search(wd, "a")); 

	wordDictionaryFree(wd);
	// 	search("pad") 
	// search("bad") 
	// search(".ad") 
	// search("b..")
	return 0;
}