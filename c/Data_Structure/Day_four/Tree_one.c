//
// Created by 17246 on 2025/7/18.
//

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct TreeNode
{
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TNode;

typedef struct SqQueue
{
    TNode* Data[MAXSIZE];
    int front, rear;
    int size;
} SqQueue;


TNode* newTreeNode(int value)
{
    TNode* node = (TNode*)malloc(sizeof(TNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TNode* insert(TNode* head, TNode* tail, int value)
{
    TNode* newNode = newTreeNode(value);
    head->left = newNode;
    newNode->left = tail;
    return newNode;
}

TNode* delete(TNode* node)
{
    TNode* temp = node;
    node->left = node->right;
    free(temp);
    return node;
}

void initQueue(SqQueue* queue)
{
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
}

int push(SqQueue* queue, TNode* e)
{
    if (queue->size == MAXSIZE) return 0;
    queue->Data[queue->rear] = e;
    queue->rear = (queue->rear + 1) % MAXSIZE;
    queue->size++;
    return 1;
}

int pop(SqQueue* queue, TNode** e)
{
    if (queue->size == 0)return 0;
    *e = queue->Data[queue->front];
    queue->front = (queue->front + 1) % MAXSIZE;
    queue->size--;
    return 1;
}

int *bfs(TNode* root, int* returnSize)
{
    if (!root)
    {
        *returnSize = 0;
        return NULL;
    }
    int* ret = (int*)malloc(MAXSIZE * sizeof(int));
    int index = 0;
    SqQueue queue;
    initQueue(&queue);
    push(&queue, root);
    while (queue.size != 0)
    {
        TNode* temp;
        pop(&queue, &temp);
        ret[index++] = temp->value;
        if (temp->left)push(&queue, temp->left);
        if (temp->right)push(&queue, temp->right);
    }
    *returnSize = index;
    return ret;
}

void dfs(TNode* root)
{
    if (!root) return;
    printf("%d ", root->value);
    dfs(root->left);
    dfs(root->right);
}

int main()
{
    TNode* root = newTreeNode(10);
    TNode* n1 = newTreeNode(9);
    TNode* n2 = newTreeNode(8);
    TNode* n3 = newTreeNode(7);
    TNode* n4 = newTreeNode(6);
    TNode* n5 = newTreeNode(5);

    root->left = n1;
    root->right = n2;
    n1->left = n3;
    n1->right = n4;
    n2->left = n5;

    int returnSize;
    int* data = bfs(root, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    dfs(root);
    free(root);
    free(data);
    return 0;
}
