//
// Created by 17246 on 2025/7/17.
//


#include <stdio.h>
#include <stdlib.h>

typedef struct Stack
{
    int* array;
    int capacity;
    int top;
}* ArrayStack;

_Bool initStack(ArrayStack stack)
{
    stack->array = malloc(sizeof(int) * 10);
    if (stack->array == NULL) return 0;
    stack->capacity = 10;
    stack->top = -1;
    return 1;
}

_Bool isEmpty(ArrayStack stack)
{
    return stack->top == -1;
}

_Bool pushStack(ArrayStack stack, int e)
{
    if (stack->top+1==stack->capacity)
    {
        int newCapacity=stack->capacity+(stack->capacity>>1);
        int *newArray=realloc(stack->array,newCapacity*sizeof(int));
        if (newArray==NULL) return 0;
        stack->array=newArray;
        stack->capacity=newCapacity;
    }
    stack->array[++stack->top] = e;
    return 1;
}

int popStack(ArrayStack stack)
{
    return stack->array[stack->top--];
}

void printStack(ArrayStack stack)
{
    for (int i=0;i<=stack->top;i++)
    {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

int main()
{
    struct Stack stack;
    initStack(&stack);
    for (int i = 0; i < 10; i++)
    {
        pushStack(&stack, i);
    }
    printStack(&stack);
    while (!isEmpty(&stack))
    {
        printf("%d ", popStack(&stack));
    }
    return 0;
}

