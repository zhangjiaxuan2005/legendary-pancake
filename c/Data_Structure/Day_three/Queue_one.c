//
// Created by 17246 on 2025/7/17.
//

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef struct SqQueue
{
    int Data[MAXSIZE];
    int front, rear;
    int size;
}SqQueue;

void initQueue(SqQueue* queue)
{
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
}

int pushQueue(SqQueue* queue, int e)
{
    if (queue->size == MAXSIZE) return 0;
    queue->Data[queue->rear] = e;
    queue->rear = (queue->rear + 1) % MAXSIZE;
    queue->size++;
    return 1;
}

int popQueue(SqQueue* queue,int *e)
{
    if (queue->size == 0) return 0;
    *e = queue->Data[queue->front];
    queue->front = (queue->front + 1) % MAXSIZE;
    queue->size--;
    return 1;
}

void printQueue(SqQueue* queue)
{
    for (int i=0;i<queue->size;i++)
    {
        printf("%d ", queue->Data[(queue->front + i) % MAXSIZE]);
    }
    printf("\n");
}

int main()
{
    SqQueue queue;
    initQueue(&queue);
    for (int i=0;i<10;i++)
    {
        pushQueue(&queue,i);
    }
    printQueue(&queue);
    int e;
    popQueue(&queue,&e);
    printf("%d\n",e);
    return 0;
}

