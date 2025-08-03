//
// Created by 17246 on 2025/8/1.
//

#include <stdio.h>
#include <stdlib.h>

#define MaxVertex 5

typedef struct MatrixGraph
{
    int matrix[MaxVertex][MaxVertex];
    int vertexCount, edgeCount;
    char data[MaxVertex];
}* Graph;

Graph create()
{
    Graph graph = malloc(sizeof(struct MatrixGraph));
    graph->edgeCount = graph->vertexCount = 0;
    for (int i = 0; i < MaxVertex; i++)
    {
        for (int j = 0; j < MaxVertex; j++)
        {
            graph->matrix[i][j] = 0;
        }
    }
    return graph;
}

void addVertex(Graph graph, char data)
{
    if (graph->vertexCount >= MaxVertex)return;
    graph->data[graph->vertexCount++] = data;
}

void addEdge(Graph graph, int a, int b)
{
    if (graph->matrix[a][b] == 0)
    {
        graph->matrix[a][b] = 1;
        graph->edgeCount++;
    }
}

void printGraph(Graph graph)
{
    for (int i = -1; i < graph->vertexCount; i++)
    {
        for (int j = -1; j < graph->vertexCount; j++)
        {
            if (j == -1)
            {
                printf("%c", 'A' + i);
            }
            else if (i == -1)
            {
                printf("%c", 'A' + j);
            }
            else
            {
                printf("%d", graph->matrix[i][j]);
            }
        }
        printf("\n");
    }
}

int main()
{
    Graph graph = create();
    addVertex(graph, 'A');
    addVertex(graph, 'B');
    addVertex(graph, 'C');
    addVertex(graph, 'D');
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 0);
    addEdge(graph, 2, 0);
    printGraph(graph);
    free(graph);
}



