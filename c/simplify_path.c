// Given an absolute path for a file (Unix-style), simplify it.

// For example,
// path = "/home/", => "/home"
// path = "/a/./b/../../c/", => "/c"
// click to show corner cases.

// Corner Cases:
// Did you consider the case where path = "/../"?
// In this case, you should return "/".
// Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
// In this case, you should ignore redundant slashes and return "/home/foo".

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElementType char*
#define MAX 2

struct StackRecord
{
	int Size;
	int Capacity;
	ElementType* Next;
};

typedef struct StackRecord* Stack;

Stack Initialize(int Capacity)
{
	Stack S;

	S = malloc(sizeof(struct StackRecord));
	S -> Size = 0;
	S -> Capacity = Capacity;
	S -> Next = malloc(sizeof(ElementType) * Capacity);

	return S;
}

int IsEmpty(Stack S)
{
	return S -> Size == 0;
}

int IsFull(Stack S)
{
	return S -> Size == S -> Capacity;
}

void Push(Stack S, ElementType Value)
{
	if (IsFull(S))
	{
		S -> Next = realloc(S -> Next, sizeof(ElementType) * S -> Capacity * 2);
		S -> Capacity *= 2;
	}

	S -> Next[S -> Size++] = Value;
}

ElementType Pop(Stack S)
{
	if (IsEmpty(S))
	{
		fprintf(stderr, "Empty Stack\n");
		exit(1);
	}

	return S -> Next[-- S -> Size];
}

void Destroy(Stack S)
{
	free(S -> Next);
	free(S);
}

struct PathRecord
{
	int Size;
	int Capacity;
	char* Buffer;
};

typedef struct PathRecord* Path;

Path InitPathRecord(int Capacity)
{
	Path P;

	P = malloc(sizeof(struct PathRecord));
	P -> Size = 0;
	P -> Capacity = 2;
	P -> Buffer = malloc(sizeof(char*) * Capacity);
	memset(P -> Buffer, 0, P -> Capacity);
	return P;
}

void AddDirToPath(Path P, char* Dir)
{
	int DirLen;

	DirLen = strlen(Dir);
	// The extra chars, one for '/', one for '\0'
	if (DirLen + P -> Size + 1 > P -> Capacity)
	{
		P -> Buffer = realloc(P -> Buffer, sizeof(char*) * P -> Capacity * 2);
		P -> Capacity *= 2;
	}

	strcat(P -> Buffer + P -> Size, Dir);
	P -> Buffer[P -> Size + DirLen + 1] = '\0';
	P -> Size += DirLen;
}

char* JoinStackToPath(Stack S)
{
	Path P;
	char* Dir;

	P = InitPathRecord(MAX);

	while (!IsEmpty(S))
	{
		AddDirToPath(P, "/");
		Dir = Pop(S);
		AddDirToPath(P, Dir);
	}

	if (P -> Size == 0)
		AddDirToPath(P, "/");
	
	return P -> Buffer;
}

void Reverse(char** Buffer, int Len)
{
	int i, j;
	char* Tmp;

	i = 0;
	j = Len - 1;

	while (i < j)
	{
		Tmp = Buffer[i];
		Buffer[i] = Buffer[j];
		Buffer[j] = Tmp;
		++i, --j;
	}
}

char* simplifyPath(char* path) {
	char* Ptr, *SimplifiedPath;
	Stack S;

	S = Initialize(MAX);
	while ((Ptr = strtok(path, "/")) != NULL)
	{
		if (strcmp(Ptr, "..") == 0)
		{
			if (!IsEmpty(S))
			{
				Pop(S);
			}
		}
		else if (strcmp(Ptr, ".") == 0)
		{
		}
		else
		{
			Push(S, Ptr);
		}

		path = NULL;
	}

	Reverse(S -> Next, S -> Size);
	SimplifiedPath = JoinStackToPath(S);
	return SimplifiedPath;
}

int main(int argc, char const *argv[])
{
	char *SimplifiedPath;
	// char path[] = "/home/./b/../../c/";
	// SimplifiedPath = simplifyPath(path);
	// printf("%s\n", SimplifiedPath);

	// char path2[] = "/../";
	// SimplifiedPath = simplifyPath(path2);
	// printf("%s\n", SimplifiedPath);

	// char path3[] = "/home//foo/";
	// SimplifiedPath = simplifyPath(path3);
	// printf("%s\n", SimplifiedPath);

	char path4[] = "/ZUEKUr/////mQgCnRJfQNIZg/.///./YpBxTyhpmtYyJfeiQWxb/../DLsEfOyEcdqu/../KBBImXbXDEclofboL/tUwMwZzcvkFfizDilg///.///gM/cBmkdtUVdAQ/gCgcGeobJBMCDGIXw/sMXnmxXrzBpkmssuPKT/atCyXalaSgmDFpvahvQW///SrctZaeLTddJKXlPHFNq/.././////./../yRNwSo/JEUmkcvANwvsrw/FhSrydvzDBCrtLTaZ/XrXtPuxAMuXFrbKuOh/./.././../FUEiMcTe/////../srNGnzVZxWOUpe/././YNtjpYYLQWoaBlJIEWM/..///./..///klHbRNEJLWvSaz/////GzNkpNWWPlLzkWrbGf/../zgZHxxnK/Ha///RUJfZEo/w/wSPgfJcSCZnKlU/../WacBhJNVvbJEARNLTN/../D/HYsTPrFyLEFX/YlPvoXcHUP/../VCeexmaHTqdbY///////././////iHWYv/////ZhMwruOuSAwsd/../../Gkr/VICeU/trbQemaHKwYpQ///ZJoPXJfbIeMQoQw/../yZRXdPdVOTgIHBW/..///uvzdgjWtD/../////JTbuiwNrWCyEERc///aWoePM///////lhPTKameBojoskHf/.///./../GNmRJROCxIhHkl/wWiRZiqA/QMjifqukwQ/UIKpIhcRmPlM/.///VhVxNrzgj/./../cdNIgbBP/CkGu/lqjZJHdyfbpVdQsygw/gTkQkHSqfHNFOQ/.././JhugsGGBRd/EJwkObqLYxQ/LSWEObQHwFWztAB/./CuyLucgUfNkE/////////vdu/fwdgPpD////";
	SimplifiedPath = simplifyPath(path4);
	printf("%s\n", SimplifiedPath);
	// char* pathes[] = { "home", "deploy", "cap", "cms", "current", "app" };
	// char* pathes[] = { "h", "b" };
	// int Len;
	// Path P;

	// Len = sizeof(pathes) / sizeof(pathes[0]);
	// P = InitPathRecord(MAX);
	// int i;

	// for (i = 0; i < Len; ++i)
	// {
	// 	AddDirToPath(P, pathes[i]);
	// }

	// printf("%s\n", P -> Buffer);

	return 0;
}