//
// Created by 17246 on 2025/7/17.
//
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int data;
    struct ListNode* next;
}* LNode;


void initList(LNode node)
{
    node->next = NULL;
}

_Bool insertList(LNode node, int data, int index)
{
    if (index < 1) return 0;
    while (--index)
    {
        node = node->next;
        if (node == NULL) return 0;
    }
    LNode newNode = malloc(sizeof(struct ListNode));
    if (newNode == NULL) return 0;
    newNode->data = data;
    newNode->next = node->next;
    node->next = newNode;
    return 1;
}

_Bool deleteList(LNode node, int index)
{
    if (index < 1) return 0;
    while (--index)
    {
        node = node->next;
        if (node == NULL) return 0;
    }
    if (node->next == NULL) return 0;
    LNode temp = node->next;
    node->next = temp->next;
    free(temp);
    return 1;
}

int getList(LNode node, int index)
{
    if (index<1) return 0;
    do
    {
        node=node->next;
        if (node==NULL) return 0;
    }while (--index);
    return node->data;
}

int findList(LNode node, int data)
{
    int index=-1;
    while (node)
    {
        if (node->data==data) return index;
        node=node->next;
        index++;
    }
    return -1;
}


void printList(LNode node)
{
    while (node->next)
    {
        node = node->next;
        printf("%d\n", node->data);
    }
}

int main()
{
    struct ListNode Head;
    initList(&Head);
    for (int i = 1; i <= 3; i++)
    {
        insertList(&Head, i * 100, i);
    }
    printList(&Head);
    // deleteList(&Head, 2);
    printf("%d\n",getList(&Head,2));
    printf("%d\n",findList(&Head,100));
    return 0;
}
