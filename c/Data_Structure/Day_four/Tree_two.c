//
// Created by 17246 on 2025/7/18.
//


#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
}* TNode;

void preOrder(TNode root)
{
    if (root == NULL)return;
    printf("%c", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(TNode root)
{
    if (root == NULL)return;
    inOrder(root->left);
    printf("%c", root->data);
    inOrder(root->right);
}

void postOrder(TNode root)
{
    if (root == NULL)return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%c",root->data);
}



int main()
{
    TNode a = malloc(sizeof(struct TreeNode));
    TNode b = malloc(sizeof(struct TreeNode));
    TNode c = malloc(sizeof(struct TreeNode));
    TNode d = malloc(sizeof(struct TreeNode));
    TNode e = malloc(sizeof(struct TreeNode));
    TNode f = malloc(sizeof(struct TreeNode));
    a->data = 'A';
    b->data = 'B';
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
    preOrder(a);
    printf("\n");
    inOrder(a);
    printf("\n");
    postOrder(a);
}

