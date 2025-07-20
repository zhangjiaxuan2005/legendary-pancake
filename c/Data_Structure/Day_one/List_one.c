//
// Created by 17246 on 2025/7/17.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct List_Node
{
    int data;
    struct List_Node* next;
} LNode;

LNode *initList()
{
    LNode *L=(LNode *)malloc(sizeof(LNode));
    L->next=NULL;
    return L;
}


LNode *createList(int data)
{
    LNode *node=(LNode *)malloc(sizeof(LNode));
    node->data=data;
    node->next=NULL;
    return node;
}

LNode *HeadInsert(LNode *L)
{
    int data;
    LNode *node;
    printf("请输入数据，输入0结束");
    scanf("%d",&data);
    while (data!=0)
    {
        node=createList(data);
        node->next=L->next;
        L->next=node;
        scanf("%d",&data);

    }
    return L;
}

LNode *TailInsert(LNode *L)
{
    int data;
    LNode *node;
    printf("请输入数据，输入0结束");
    scanf("%d",&data);
    while (data!=0)
    {
        node=createList(data);
        L->next=node;
        L=node;
        scanf("%d",&data);

    }
    return L;
}

LNode *traversal(LNode *l)
{
    LNode *p=l->next;
    while (p!=NULL)
    {
        printf("%d\n",p->data);
        p=p->next;
    }
    return l;
}

LNode *search(LNode *L,int data)
{
    LNode *p=L->next;
    while (p!=NULL)
    {
        if (p->data==data)
        {
            return p;
        }
        p=p->next;
    }
    return NULL;
}

void insertNode(LNode *s, LNode *p)
{
    p->next = s->next;
    s->next = p;
}

void deleteNode(LNode *s)
{
    s->next = s->next->next;
}

int main(int argc, char* argv[])
{
    LNode *L=initList();
    if (L==NULL)
    {
        printf("init error");
        return 0;
    }
    LNode *L1=HeadInsert(L);
    // LNode *L2=TailInsert(L);
    insertNode(L1,createList(100));
    traversal(L);
    free(L);
    return 0;
}
