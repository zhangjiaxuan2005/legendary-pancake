//
// Created by 17246 on 2025/7/20.
//
#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
} TreeNode;


typedef struct StackNode
{
    TreeNode* data;
    struct StackNode* next;
} StackNode;


void initStack(StackNode** top)
{
    *top = NULL;
}

int isStackEmpty(StackNode* top)
{
    return top == NULL;
}

TreeNode* createNode(int data)
{
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void push(StackNode** top, TreeNode* node)
{
    StackNode* newNode = malloc(sizeof(StackNode));
    if (newNode == NULL)
    {
        return;
    }
    newNode->data = node;
    newNode->next = *top;
    *top = newNode;
}

TreeNode* pop(StackNode** top)
{
    if (isStackEmpty(*top))
    {
        return NULL;
    }
    StackNode* temp = *top;
    TreeNode* node = temp->data;
    *top = temp->next;
    free(temp);
    return node;
}


void dfs(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    StackNode* stack;
    initStack(&stack);
    TreeNode* current = root;

    while (current != NULL || !isStackEmpty(stack))
    {
        while (current != NULL)
        {
            printf("%c ", current->data);
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        current = current->right;
    }
    printf("\n");
}


int main()
{
    // 创建树节点
    TreeNode* a = createNode('A');
    TreeNode* b = createNode('B');
    TreeNode* c = createNode('C');
    TreeNode* d = createNode('D');
    TreeNode* e = createNode('E');
    TreeNode* f = createNode('F');

    // 构建树结构
    c->data = 'C';
    d->data = 'D';
    e->data = 'E';
    f->data = 'F';
    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    c->right = f;
    c->left = NULL;
    d->left = d->right = NULL;
    e->left = e->right = NULL;
    f->left = f->right = NULL;
    dfs(a);
}
