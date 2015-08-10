// Evaluate the value of an arithmetic expression in Reverse Polish Notation.

// Valid operators are +, -, *, /. Each operand may be an integer or another expression.

// Some examples:
//   ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
//   ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElementType int
#define MAX 2

struct StackRecord 
{
	int Size;
	int Capacity;
	ElementType *Next;
};

typedef struct StackRecord* Stack;

Stack Initialize()
{
	Stack S;

	S = malloc(sizeof(struct StackRecord));
	S -> Size = 0;
	S -> Capacity = MAX;
	S -> Next = malloc(sizeof(ElementType) * S -> Capacity);

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

	return S -> Next[--S -> Size];
}

void Destroy(Stack S)
{
	free(S -> Next);
	free(S);
}

//   ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
//   ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

#define ISOP(X) (((X) == '+') || ((X) == '-') || ((X) == '*') || ((X) == '/'))

int Operate(int Op1, int Op2, char Operator)
{
	switch (Operator)
	{
		case '+':
			return Op1 + Op2;
		case '-':
			return Op1 - Op2;
		case '*':
			return Op1 * Op2;
		case '/':
			return Op1 / Op2;
	}
}

int evalRPN(char** tokens, int tokensSize) {
	int i;
	int Op1, Op2, Result;
	Stack S;

	S = Initialize();

	for (i = 0; i < tokensSize; ++i)
	{
		if ((strlen(tokens[i]) == 1 )&& ISOP(tokens[i][0]))
		{
			Op2 = Pop(S);
			Op1 = Pop(S);
			Push(S, Operate(Op1, Op2, tokens[i][0]));
		}
		else
		{
			Push(S, atoi(tokens[i]));
		}
	}

	Result = Pop(S);
	Destroy(S);
	return Result;
}

int main(int argc, char const *argv[])
{
	char* tokens[] = {"4", "-3", "+"};
	int Len;

	Len = sizeof(tokens) / sizeof(tokens[0]);
	printf("%d\n", evalRPN(tokens, Len));
	return 0;
}