// Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

// The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.

#include <stdio.h>
#include <stdlib.h>

#define ElementType char
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

ElementType Top(Stack S)
{
	if (IsEmpty(S))
	{
		fprintf(stderr, "Empty Stack\n");
		exit(1);
	}

	return S -> Next[S -> Size - 1];
}

void Destroy(Stack S)
{
	free(S -> Next);
	free(S);
}

int IsPair(char c1, char c2)
{
	if ((c1 == '{' && c2 == '}') || (c1 == '(' && c2 == ')') || (c1 == '[' && c2 == ']'))
		return 1;
	
	return 0;
}

int IsLeftPart(char c)
{
	if ((c == '(') || (c == '{') || (c == '['))
		return 1;

	return 0;
}

int isValid(char* s) {
	char* Ptr;
	Stack S;

	S = Initialize(MAX);
	Ptr = s;
	while (*Ptr != '\0')
	{
		if (IsEmpty(S))
		{
			Push(S, *Ptr);			
		}
		else
		{
			if (IsLeftPart(*Ptr))
			{
					Push(S, *Ptr);
			}
			else
			{
				if (IsPair(Top(S), *Ptr))
					Pop(S);
				else
					return 0;
			}
		}

		++Ptr;
	}

	if (IsEmpty(S))
		return 1;
	else
		return 0;
}

int main(int argc, char const *argv[])
{
	printf("%d\n", isValid("()"));
	printf("%d\n", isValid("()[]{}"));
	printf("%d\n", isValid("([)]"));
	printf("%d\n", isValid("(]"));
	return 0;
}