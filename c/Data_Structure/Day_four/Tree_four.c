//
// Created by 17246 on 2025/7/31.
//


#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
}* TNode;

TNode createTree(int data)
{
    TNode node = malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

TNode insert(TNode root, int data)
{
    if (root)
    {
        if (data < root->data)
        {
            root->left = insert(root->left, data);
        }
        else if (data > root->data)
        {
            root->right = insert(root->right, data);
        }
    }
    else
    {
        root = createTree(data);
    }
    return root;
}

void inOrder(TNode root)
{
    if (root)
    {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

TNode find(TNode root, int target)
{
    while (root)
    {
        if (root->data > target)
        {
            root = root->left;
        }
        else if (root->data < target)
        {
            root = root->right;
        }
        else
        {
            return root;
        }
    }
    return NULL;
}

TNode findMax(TNode root)
{
    while (root->right)
    {
        root = root->right;
    }
    return root;
}

TNode delete(TNode root, int target)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->data > target)
    {
        root->left = delete(root->left, target);
    }
    else if (root->data < target)
    {
        root->right = delete(root->right, target);
    }
    else
    {
        if (root->left && root->right)
        {
            TNode max = findMax(root->left);
            root->data = max->data;
            root->left = delete(root->left, max->data);
        }else
        {
            TNode temp = root;
            if (root->left)
            {
                root = root->left;
            }
            else
            {
                root = root->right;
            }
            free(temp);
        }
    }
    return root;
}

int main()
{
    TNode root = createTree(10);
    insert(root, 5);
    insert(root, 15);
    insert(root, 3);
    insert(root, 7);
    insert(root, 12);
    insert(root, 18);
    inOrder(root);
    printf("\n");
    printf("%p\n", find(root, 12));
    printf("%p", find(root, 11));
    free(root);
    return 0;
}

