//
// Created by 17246 on 2025/7/17.
//

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack_ListNode
{
    int data;
    struct stack_ListNode* next;
} SLNode;

typedef struct Link_Stack
{
    SLNode* top;
} LinkStack;

void initLinkStack(LinkStack* stack)
{
    stack->top = NULL;
}

void push(LinkStack* stack, int e)
{
    SLNode* node = malloc(sizeof(SLNode));
    node->data = e;
    node->next = stack->top;
    stack->top = node;
}

int pop(LinkStack* stack, int* e)
{
    if (stack->top == NULL)
    {
        return 0;
    }
    SLNode *temp=stack->top;
    *e=temp->data;
    stack->top=temp->next;
    free(temp);
    return 1;
}

void printLinkStack(LinkStack* stack)
{
    SLNode* node = stack->top;
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main()
{
    LinkStack S;
    initLinkStack(&S);
    for (int i = 0; i < 10; i++)
    {
        push(&S, i);
    }
    printLinkStack(&S);
}

