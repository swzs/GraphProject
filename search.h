
#include <stdio.h>

typedef struct list
{
    int des;
    struct list *next;
}List;

void DFS(int x, int y, int di, List *now, int times);
void BFS(int x, int y);
void Dijkstra(int x, int y);
int* shortestPath(int u, int v, char algorithm[], char name[]);

