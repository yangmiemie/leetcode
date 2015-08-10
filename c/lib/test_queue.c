#include <stdio.h>

#include "test_queue.h"

#define Queue struct StackRecord*

extern Queue Initialize();
extern int Enqueue(Queue, int);
extern int Dequeue(Queue);
extern void Destroy(Queue);

int TestQueue()
{
 Queue Q;
 int i;

 Q = Initialize();
 for (i = 0; i < 100; ++i)
   Enqueue(Q, i);

 while (!IsEmpty(Q))
   printf("%d ", Dequeue(Q));

 printf("\n");

 Destroy(Q);
}

#undef Queue