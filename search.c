//这部分代码来源于上一届学长，因我们能力有限，请教上一届学长得到了这份代码的初始版本，然后由于时间和能力的缘故，我们对代码进行了一些修改优化之后便进行了试用，如果
//这个算抄袭，和沈伟（2019302180068）无关，由我（2019302180072）承担，请老师酌情判断。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "search.h"
#include "stats.h"
#define ERROR 0
#define OK 1

int error = 1;
int first[450000];
int vis [450000];
int parent[450000];
char done[450000];
int next[4000000], u[4000000], v[4000000], d[4000000];
int min = 21473640;
List *head;
List *answer;
int *ans;
int member = 0;
int n;   //vertices
int num; //edges
int complete = 0;


void DFS(int x, int y, int di, List *now, int times)
{
    if (di >= min || di >= 1005 || times >= 23)
    {
        return;
    }

    List *newone = (List *)malloc(sizeof(List));
    newone -> des = x;
    newone -> next = NULL;
    now -> next = newone;

    if (x == y)
    {
        error = 0;
        if (di < min)
        {
            min = di;

            List *temp = answer -> next;
            while (temp)
            {
                List *t = temp -> next;
                free(temp);
                temp = t;
            }

            int mem = 0;
            List * dec = answer;
            temp = head -> next;
            while (temp)
            {
                List *t = (List *)malloc(sizeof(List));
                t -> des = temp -> des;
                temp = temp -> next;
                dec -> next = t;
                dec = dec -> next;
                mem++;
            }
            dec -> next = NULL;
            member = mem;
        }

        now -> next = NULL;
        free(newone);    
        return; 
    }

    int l = first[x];
    while (l >= 0)
    {
        if (vis[v[l]] == 0)
        {
            vis[v[l]] = 1;
            DFS(v[l], y, di + d[l], newone, times + 1);
            vis[v[l]] = 0;
        }
        l = next[l]; 
    }
    now -> next = NULL;
    free(newone);   
}



typedef struct s
{
    int father;
    int num;
    int d;
}S;

typedef struct Queue 
{
    S *data;
    int head, tail, length;
}Queue;

void init(Queue *q, int length) 
{
    q -> data = (S *)malloc(sizeof(S) * length);
    q -> length = length;
    q -> head = 0;
    q -> tail = -1;
}

int push(Queue *q, S element) 
{
    if(q -> tail + 1 >= q -> length) 
    {
        return ERROR;
    }
    q -> tail++;
    q -> data[q -> tail] = element;
    return OK;
}

S front(Queue *q)
{
    return q -> data[q -> head];
}

void pop(Queue *q)
{
    q -> head++;
}

int empty(Queue *q)
{
    return q -> head > q -> tail;
}

void clear(Queue *q) 
{
    free(q -> data);
    free(q);
}

void BFS(int x, int y)
{
    error = 1;
    complete = 1;
    S start;
    start.num = x;
    start.d = 0;
    start.father = -1;
    vis[x] = 1;
    Queue *queue1 = (Queue *)malloc(sizeof(Queue));
    init(queue1, 450000);
    push(queue1, start);

    while (!empty(queue1))
    {
        S cur1 = front(queue1);
        if (cur1.num == y)
        {
            int di = cur1.d;
            ans = (int *)malloc(sizeof(int) * (di + 1));

            ans[di] = cur1.num;
            for (int i = di - 1; i >= 0; i--)
            {
                ans[i] = queue1 -> data[cur1.father].num;
                cur1 = queue1-> data[cur1.father];                
            }      
            error = 0;     
            break;
        }

        int l = first[cur1.num];
        while (l >= 0)
        {
            if (vis[v[l]] == 0)
            {
                vis[v[l]] = 1;
                S tmp;
                tmp.num = v[l];
                tmp.father = queue1 -> head;
                tmp.d = cur1.d + 1;
                push(queue1, tmp);
            }
            l = next[l]; 
        }
        pop(queue1);               
    }
    clear(queue1);

    if (error)
    {
        printf("No Answer.\n");
        exit(0);
    }
      
}

typedef struct PriorityQueue 
{  
    S data[450000];
    int size;
}PQ;


void H_AdjustDown(PQ *H, int k)
{
    while (k * 2 <= H -> size)
    {
        int j = k * 2;
        if (j + 1 <= H -> size && H -> data[j].d > H -> data[j + 1].d)
        {
            j = j + 1;
        }
        if (H -> data[k].d <= H -> data[j].d)
        {
            break;
        }

        S tmp = H -> data[k];
        H -> data[k] = H -> data[j];
        H -> data[j] = tmp;
 
        k = j;
    }
}

void H_init(PQ *H)
{ 
    for (int i = H -> size / 2; i > 0; i--)
    { 
        H_AdjustDown(H, i);
    }
}

void H_AdjustUp(PQ *H, int k)
{
    while (1 < k && H -> data[k / 2].d > H -> data[k].d)
    {
        S tmp = H -> data[k / 2];
        H -> data[k / 2] = H -> data[k];
        H -> data[k] = tmp;
        k /= 2;
    }
}


void PQinit(PQ* q)
{
    assert(q);
    q -> size = 0;
}
 
void PQpush(PQ* q, S x)
{
    assert(q);
    assert(q -> size <= 450000);

    q -> data[q -> size + 1] = x;
    q -> size++;
 
    H_AdjustUp(q, q -> size);
    
}
 
S PQpop(PQ* q)
{
    assert(q);
    assert(q -> size > 0);

    S res = q -> data[1];
    q -> data[1] = q -> data[q -> size];
    q -> data[(q -> size)--] = (S){0, 0, 500000}; 
    H_AdjustDown(q, 1);
 
    return res;
}
 
S PQfront(PQ* q)
{
    assert(q);
    assert(q -> size > 0);

    return q -> data[1];
}
 
int PQsize(PQ* q)
{
    return q -> size;
}
 
int PQempty(PQ* q)
{
    return q -> size == 0;
}

void Dijkstra(int x, int y)
{
    if (y > n)
    {
        printf("No Answer.\n");
        exit(0);       
    }

    memset(done, 0, sizeof(done));
    complete = 1;
    for (int i = 0; i < n; i++)
    {
        vis[i] = 500000;
    }
    vis[x] = 0;

    PQ *q = (PQ *)malloc(sizeof(PQ));
    PQinit(q);
    S start;
    start.d = 0;
    start.num = x;
    parent[x] = -1;
    PQpush(q, start);

    while(!PQempty(q))
    {
        S tmp = PQfront(q);
        PQpop(q);
      
        if (done[tmp.num] == '1')
        {
            continue;
        }
        done[tmp.num] = '1';

        int l = first[tmp.num];
        while (l >= 0)
        {
            if (vis[v[l]] > vis[u[l]] + d[l])
            {
                vis[v[l]] = vis[u[l]] + d[l];

                S newone;
                newone.num = v[l];
                newone.d = vis[v[l]];          
                PQpush(q, newone);

                parent[v[l]] = l;
            }    
      
            l = next[l]; 
        }
    }

    ans = (int *)malloc(sizeof(int) * (vis[y] + 1)); 
    int mid = parent[y];
    int count = 0;
    while (mid >= 0)
    {
        mid = parent[u[mid]];
        count++;   
    }
    ans[count] = y;
    mid = parent[y];
    for (int i = count - 1; i >= 0; i--)
    {
        ans[i] = u[mid];
        mid = parent[u[mid]];                   
    }  

}



int* shortestPath(int u0, int v0, char algorithm[], char name[])
{
    FILE *fp;
    fp = fopen(name, "r"); 
    if (!fp)
    {
        printf("Wrong File!\n");
        exit(1);
    }

    memset(first, -1, sizeof(first));
    memset(vis, 0, sizeof(vis));

    n = 0;
    num = 0;
    while (fscanf(fp, "%d %d %d", &u[num], &v[num], &d[num]) != EOF)
    {
        next[num] = first[u[num]];
        first[u[num]] = num;
        
    
        if (n < u[num])
        {
            n = u[num];
            
        } 
        num++;
    }
    n++;
 
    head = (List *)malloc(sizeof(List));
    head -> next = NULL;
    answer = (List *)malloc(sizeof(List));
    answer -> next = NULL;

    
    if (strcmp(algorithm, "DFS") == 0)
    {
        DFS(u0, v0, 0, head, 0);
        if (error)
        {
            printf("No Answer.\n");
            exit(0);
        }
        
    }
    else if (strcmp(algorithm, "BFS") == 0)
    {
        BFS(u0, v0);    
    }
    else if (strcmp(algorithm, "Dijkstra") == 0)
    {
        Dijkstra(u0, v0);
    }
    else
    {
        printf("输入错误");
        exit(0);
    }
    
    if( complete == 0)
    {
        int mark = 0;
        ans = (int *)malloc(sizeof(int) * member);
        List *tmp = answer -> next;
        while (tmp)
        {
            ans[mark++] = tmp -> des;
            tmp = tmp -> next;
        }
    }

    return ans;
}

