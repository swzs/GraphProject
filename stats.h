#include <stdio.h>
#define MAXV 1000000
typedef char VertexType,VexType;
typedef int EdgeType,InfoType;



/*typedef struct ANode
{   int adjvet;
    struct ANode *nextarc;
	int weight;
} ArcNode;
typedef struct Vnode
{   InfoType info;
    ArcNode *firstarc;
}VNode;

typedef struct
{   VNode adjlist[MAXV];
    int n, e;
}AdjGraph;*/






int numberOfEdges(char name[]);

int numberOfVertices(char name[]);

float freemanNetworkCentrality(char name[]);
