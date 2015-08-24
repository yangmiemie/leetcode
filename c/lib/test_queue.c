#include <stdio.h>

#include "test_queue.h"

#define Queue struct QueueRecord*

extern Queue Initialize(int);
extern int Enqueue(Queue, int);
extern int Dequeue(Queue);
extern void Destroy(Queue);

int TestQueue()
{
 Queue Q;
 int i;

 Q = Initialize(4);
 for (i = 0; i < 100; ++i)
   Enqueue(Q, i);

 while (!IsEmpty(Q))
   printf("%d ", Dequeue(Q));

 printf("\n");

 Destroy(Q);
}

#undef Queue