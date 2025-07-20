//
// Created by 17246 on 2025/7/17.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Queue_ListNode
{
    int data;
    struct Queue_ListNode *next;
}QLNode;

typedef struct
{
    QLNode *front, *rear;
}LinkQueue;

void initQueue(LinkQueue *q)
{
    q->front = q->rear = (QLNode *)malloc(sizeof(QLNode));
    q->front->next = NULL;
}

void push(LinkQueue *queue, int value)
{
    QLNode *node = malloc(sizeof(QLNode));
    node->data = value;
    node->next = NULL;
    queue->rear->next = node;
    queue->rear = node;
}

void pop(LinkQueue *queue,int *value)
{
    if (queue->front == queue->rear)
    {
        return;
    }
    QLNode *temp=queue->front->next;
    *value=temp->data;
    queue->front->next=temp->next;
    if (queue->rear == temp)
    {
        queue->rear = queue->front;
    }
    free(temp);
}

void printQueue(LinkQueue *queue)
{
    QLNode *temp = queue->front->next;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    LinkQueue queue;
    initQueue(&queue);
    for (int i = 0; i < 10; i++)
    {
        push(&queue, i);
    }
    printQueue(&queue);
    int value;
    pop(&queue, &value);
    printf("%d\n", value);
    return 0;
}

