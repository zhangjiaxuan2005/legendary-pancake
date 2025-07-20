//
// Created by 17246 on 2025/7/18.
//


#include <stdio.h>
#include <stdlib.h>

typedef struct Queue
{
    int* array;
    int capacity;
    int front, rear;
}* ArrayQueue;

_Bool initQueue(ArrayQueue queue)
{
    queue->array = malloc(sizeof(int) * 10);
    if (queue->array == NULL) return 0;
    queue->capacity = 10;
    queue->front = queue->rear = 0;
    return 1;
}

_Bool offerQueue(ArrayQueue queue, int value)
{
    int pos = (queue->rear + 1) % queue->capacity;
    if (pos == queue->front)
    {
        return 0;
    }
    queue->rear = pos;
    queue->array[queue->rear] = value;
    return 1;
}


_Bool isEmpty(ArrayQueue queue)
{
    return queue->front == queue->rear;
}

int pullQueue(ArrayQueue queue)
{
    queue->front = (queue->front + 1) % queue->capacity;
    return queue->array[queue->front];
}

void printQueue(ArrayQueue queue)
{
    int pos = queue->front;
    do
    {
        pos=(pos+1)%queue->capacity;
        printf("%d ",queue->array[pos]);
    }
    while(pos!=queue->rear);
    printf("\n");
}

int main()
{
    struct Queue queue;
    initQueue(&queue);
    for (int i = 0; i < 10; i++)
    {
        offerQueue(&queue, i);
    }
    printQueue(&queue);
    while (!isEmpty(&queue))
    {
        printf("%d ", pullQueue(&queue));
    }
}
