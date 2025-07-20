//
// Created by 17246 on 2025/7/17.
//
#include <stdio.h>
#define MAXSIZE 100

typedef struct SqStack
{
    int data[MAXSIZE];
    int top;
} SqStack;

void initStack(SqStack* stack)
{
    stack->top = -1;
}

int pop(SqStack* stack, int* e)
{
    if (stack->top == -1)
    {
        return 0;
    }
    *e = stack->data[stack->top];
    stack->top--;
    return 1;
}

int push(SqStack* stack, int e)
{
    if (stack->top == MAXSIZE - 1)
    {
        return 0;
    }
    stack->top++;
    stack->data[stack->top] = e;
    return 1;
}

void print(SqStack* stack)
{
    for (int i = 0; i <= stack->top; i++)
    {
        printf("%d ", stack->data[i]);
    }
}

int main()
{
    SqStack S;
    initStack(&S);
    for (int i = 0; i < 10; i++)
    {
        push(&S, i);
    }
    print(&S);
}
