#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>
#define MAX 1005
int32_t parent[MAX], rank[MAX];
int32_t CNT = 0;
// https://github.com/abhichand26/kruskal-mst/blob/master/Kruskal_MST.c

// 生成最大生成樹返回最後一個被kruskal找到的邊的weighted
// 將途中小於此weight的邊都去掉
// 再跑一次正常的MST

typedef struct Edge
{
    int32_t u;
    int32_t v;
    int32_t w;
}edgeSet;

// Union Find Kruskal's Algorithm
int32_t find(int32_t u)
{
    int32_t i = 0, tmp[MAX];
    while(u != parent[u])
    {
        tmp[i] = u;
        u = parent[u];
        i++;
    }
    i--;
    while(i >= 0)
    {
        parent[tmp[i]] = u;
        i--;
    }
    return u;
}

void unionMST(int32_t u, int32_t v)
{
    int32_t x, y;
    x = find(u);
    y = find(v);
    if(rank[x] < rank[y])
    {
        parent[x] = y;
    }
    else if(rank[x] > rank[y])
    {
        parent[y] = x;
    }
    else
    {
        parent[x] = y;
        rank[y]++;
    }
}

// fun to sort in descending order
int decmp(const void * a, const void * b)
{
    edgeSet *A = (edgeSet*)a;
    edgeSet *B = (edgeSet*)b;
    return (B->w - A->w);
}
// fun to sort in increasing order
int incmp(const void * a, const void * b)
{
    edgeSet *A = (edgeSet*)a;
    edgeSet *B = (edgeSet*)b;
    return (A->w - B->w);
}

// funs to return min in max spinning tree
int32_t bottleneckKruskal(edgeSet *E, int32_t N, int32_t M)
{
    int32_t i, j = 0, x, y, u, v;
    int32_t bottleneck = 0;
    // sort edge by descending order
    qsort(E, M, sizeof(edgeSet), decmp);
    // edgeSet *MST = (edgeSet*)malloc((N-1)*sizeof(edgeSet));

    for(i = 0; i < M; i++)
    {
        if(j == (N-1))
        {
            break;
        }
        u = E[i].u;
        v = E[i].v;
        x = find(u);
        y = find(v);
        CNT++;
        if(x != y)
        {
            // MST[j] = E[i];
            bottleneck = E[i].w;
            unionMST(x, y);
            j++;
        }
    }

    // printMST(MST,N-1);
    return bottleneck;
}

int32_t Kruskal(edgeSet *E, int32_t N, int32_t M)
{
    int32_t i, j = 0, x, y, u, v;
    int32_t cost = 0;
    // sort edge by increasing order
    // qsort(E, M, sizeof(edgeSet), incmp);
    // for(i = 0; i < M; i++)
    // {
    //     printf("E: %d %d %d\n", E[i].u, E[i].v, E[i].w);
    // }

    // edgeSet *MST = (edgeSet*)malloc((N-1)*sizeof(edgeSet));

    for(i = M-1; i >= 0; i--)
    {
        
        if(j == (N-1))
        {
            break;
        }
        u = E[i].u;
        v = E[i].v;
        x = find(u);
        y = find(v);
        // printf("2E: %d %d %d %d %d\n", E[i].u, E[i].v, E[i].w, x, y);
        if(x != y)
        {
            cost += E[i].w;
            unionMST(x, y);
            j++;
        }
    }
    return cost;
}

int main()
{
    int32_t N, M;
    int32_t i, j, k;
    scanf("%d %d", &N, &M);

    edgeSet *set = (edgeSet*)malloc(M * sizeof(edgeSet));

    for(i = 0; i < M; i++)
    {
        scanf("%d %d %d",&set[i].u, &set[i].v, &set[i].w);
    }
    for(i = 1; i < N+1; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    int32_t bottleneck = bottleneckKruskal(set, N, M);
    // printf("\n\n%d\n", bottleneck);

    // int32_t left = 0, right = M, mid;
    // while(left < right)
    // {
    //     mid = right - (right - left)/2;
    //     if(set[mid].w < bottleneck)
    //     {
    //         right = mid-1;
    //     }
    //     else 
    //     {
    //         left = mid;
    //     }
    // }

    // printf("\nleft:%d %d %d\n", left, right, mid);
    for(i = 1; i < N+1; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
    printf("%d\n", Kruskal(set, N, CNT)); 
}