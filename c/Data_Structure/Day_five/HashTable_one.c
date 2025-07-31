//
// Created by 17246 on 2025/7/31.
//

#include <stdlib.h>
#include <stdio.h>

#define SIZE 9


typedef struct Data
{
    int key;
}* Data;

typedef struct HashTable
{
    Data* table;
}* HashTable;

void initHashTable(HashTable hashTable)
{
    hashTable->table = malloc(sizeof(Data) * SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        hashTable->table[i] = NULL;
    }
}

int hash(int key)
{
    return key % SIZE;
}

void insert(HashTable hashTable, Data data)
{
    int hashCode = hash(data->key);
    hashTable->table[hashCode] = data;
}

_Bool search(HashTable hashTable, int key)
{
    int hashCode = hash(key);
    if (hashTable->table[hashCode] == NULL)
    {
        return 0;
    }
    return hashTable->table[hashCode]->key == key;
}

Data create(int key)
{
    Data data = malloc(sizeof(struct Data));
    data->key = key;
    return data;
}

int main()
{
    struct HashTable table;
    initHashTable(&table);
    insert(&table, create(10));
    insert(&table, create(7));
    insert(&table, create(13));
    insert(&table, create(10));
    insert(&table, create(29));
    for (int i = 0; i < SIZE; i++)
    {
        if (table.table[i])
        {
            printf("%d ", table.table[i]->key);
        }
        else
        {
            printf("NULL ");
        }
    }
    printf("\n");
    printf("%d ", search(&table, 10));
    printf("%d", search(&table, 1));
}
