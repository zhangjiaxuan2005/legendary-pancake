//
// Created by 17246 on 2025/7/20.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
}* TNode;





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
}