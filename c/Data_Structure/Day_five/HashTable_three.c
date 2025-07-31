//
// Created by 17246 on 2025/7/31.
//

#include <stdlib.h>
#include <stdio.h>

#define SIZE 9


typedef struct ListNode
{
    int key;
    struct ListNode* next;
}* LNode;

typedef struct HashTable
{
    LNode table;
}* HashTable;

void initHashTable(HashTable hashTable)
{
    hashTable->table = malloc(sizeof(struct ListNode) * SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        hashTable->table[i].key = -1;
        hashTable->table[i].next = NULL;
    }
}


int hash(int key)
{
    return key % SIZE;
}

LNode createNode(int key)
{
    LNode node = malloc(sizeof(struct ListNode));
    node->key = key;
    node->next = NULL;
    return node;
}

void insert(HashTable hashTable, int key)
{
    int hashCode = hash(key);
    LNode head = hashTable->table + hashCode;
    while (head->next != NULL)
    {
        head = head->next;
    }
    head->next = createNode(key);
}

_Bool search(HashTable hashTable, int key)
{
    int hashCode = hash(key);
    LNode head = hashTable->table + hashCode;
    while (head->next && head->key != key)
    {
        head = head->next;
    }
    return head->key == key;
}


int main()
{
    struct HashTable table;
    initHashTable(&table);
    insert(&table, 10);
    insert(&table, 7);
    insert(&table, 13);
    insert(&table, 10);
    insert(&table, 29);
    insert(&table, 16);

    printf("%d ", search(&table, 10));
    printf("%d ", search(&table, 17));
    printf("%d", search(&table, 16));
}
