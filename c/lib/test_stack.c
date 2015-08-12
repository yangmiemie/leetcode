#include <stdio.h>

#include "test_stack.h"

#define Stack struct StackRecord*
#define MAX 2

extern Stack Initialize(int);
extern int Push(Stack, int);
extern int Pop(Stack);
extern void Destroy(Stack);
extern int IsEmpty(Stack);

int TestStack()
{
 Stack S;
 int i;

 S = Initialize(MAX);
 for (i = 0; i < 100; ++i)
   Push(S, i);

 while (!IsEmpty(S))
   printf("%d ", Pop(S));

 printf("\n");

 Destroy(S);
}

#undef Stack