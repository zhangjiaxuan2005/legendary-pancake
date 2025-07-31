//
// Created by 17246 on 2025/7/31.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
    int height;
}* TNode;

TNode createTree(int data)
{
    TNode node = malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int getHeight(TNode root)
{
    if (root == NULL)return 0;

    return root->height;
}

TNode leftRotation(TNode root)
{
    TNode temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
    return temp;
}

TNode rightRotation(TNode root)
{
    TNode temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
    return temp;
}


TNode leftRightRotation(TNode root)
{
    root->left = leftRotation(root->left);
    return rightRotation(root);
}

TNode rightLeftRotation(TNode root)
{
    root->right = rightRotation(root->right);
    return leftRotation(root);
}

TNode insert(TNode root, int data)
{
    if (root == NULL)
    {
        root = createTree(data);
    }
    else if (root->data > data)
    {
        root->left = insert(root->left, data);
        if (getHeight(root->left) - getHeight(root->right) > 1)
        {
            if (root->left->data > data)
            {
                root = rightRotation(root);
            }
            else
            {
                root = leftRightRotation(root);
            }
        }
    }
    else if (root->data < data)
    {
        root->right = insert(root->right, data);
        if (getHeight(root->left) - getHeight(root->right) < -1)
        {
            if (root->right->data < data)
            {
                root = leftRotation(root);
            }
            else
            {
                root = rightLeftRotation(root);
            }
        }
    }
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    return root;
}


int main()
{
    TNode root = NULL;
    while (1)
    {
        int data;
        scanf("%d", &data);
        root = insert(root, data);
        printf("");
    }
}
