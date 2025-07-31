#include <stdio.h>
#include <stdlib.h>
//
// Created by 17246 on 2025/7/31.
//
typedef struct MaxHeap
{
    int* arr;
    int size;
    int capacity;
}* Heap;

_Bool initHeap(Heap heap)
{
    heap->size = 0;
    heap->capacity = 10;
    heap->arr = malloc(sizeof(int) * heap->capacity);
    return heap->arr != NULL;
}

_Bool insert(Heap heap, int data)
{
    if (heap->size == heap->capacity)
    {
        int newCapacity = heap->capacity + (heap->capacity >> 1);
        int* newArray = realloc(heap->arr, newCapacity * sizeof(int));
        if (newArray == NULL) return 0;
        heap->arr = newArray;
        heap->capacity = newCapacity;
    }
    int index = ++heap->size;
    while (index > 1 && data > heap->arr[index / 2])
    {
        heap->arr[index] = heap->arr[index / 2];
        index /= 2;
    }
    heap->arr[index] = data;
    return 1;
}

int delete(Heap heap)
{
    int data = heap->arr[1], temp = heap->arr[heap->size--];
    int index = 1;
    while (index * 2 <= heap->size)
    {
        int child = index * 2;
        if (child < heap->size && heap->arr[child + 1] > heap->arr[child])
        {
            child++;
        }
        if (temp > heap->arr[child]) break;
        heap->arr[index] = heap->arr[child];
        index = child;
    }
    heap->arr[index] = temp;
    return data;
}

void printHeap(Heap heap)
{
    for (int i = 1; i <= heap->size; i++)
    {
        printf("%d ", heap->arr[i]);
    }
}


int main()
{
    struct MaxHeap heap;
    initHeap(&heap);
    insert(&heap, 1);
    insert(&heap, 4);
    insert(&heap, 3);
    insert(&heap, 9);
    insert(&heap, 2);
    insert(&heap, 5);
    insert(&heap, 7);
    printHeap(&heap);
    printf("\n");
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", delete(&heap));
    }
}
