#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>
#define MAX 3005
int32_t top = 0;

// Anti-Sea-Bear Circle

/*
圖表用adjacency list
先利用BFS知道各點與起始點的距離是否 <=D，起始點由大到小嘗試。
*/

int cmp (const void * a, const void * b)
{
   return (*(int32_t*)a - *(int32_t*)b);
}

typedef struct
{
    int32_t cnt;
    int32_t *list;
}adjacency_list;

adjacency_list** creatAList(int32_t n)
{
    adjacency_list **a = (adjacency_list**)malloc(MAX * sizeof(adjacency_list*));
    for(int32_t i = 0; i < n; i++)
    {
        a[i] = (adjacency_list*)malloc(sizeof(adjacency_list));
        a[i]->list = (int32_t*)malloc(n * sizeof(int32_t));
        a[i]->cnt = 0;
    }
    return a;
}

void add2list(adjacency_list **a, int32_t i, int32_t j)
{
    a[i]->list[ a[i]->cnt++] = j;
}

void showADlist(adjacency_list** a, int32_t n)
{
    int32_t i, j;
    for(i = 0; i < n; i++)
    {
        printf("(%d): ", i);
        for(j = 0; j < a[i]->cnt; j++)
        {
            printf(" %d", a[i]->list[j]);
        }
        printf("\n");
    }
}

bool dfs(adjacency_list **graph ,int32_t node2DFS, int32_t depth, int32_t size, int32_t *ans, int32_t *visited)
{
    int32_t i;

    ans[top++] = node2DFS;
    if(size < depth)
    {
        return false;
    }
    visited[node2DFS] = 1;
    for(i = 0; i < graph[node2DFS]->cnt; i++)
    {
        if(!visited[graph[node2DFS]->list[i]])
        {
            if(!dfs(graph, graph[node2DFS]->list[i],depth+1, size, ans, visited))
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    int32_t i, j, k;
    int32_t num, size;
    scanf("%d %d", &num, &size);
    adjacency_list **graph = creatAList(num);

    // 圖表用adjacencylist
    for(i = 1; i < num; i++)
    {
        int32_t start, end;
        scanf("%d %d", &start, &end);

        add2list(graph, start-1, end-1);
        add2list(graph, end-1, start-1);
    }
    // showADlist(graph, num);

    if(num == 1)
	{
		if(size == 0)
		{
			printf("1\n");
			return 0;		
		}
	}
	else
	{
		if(size == 0)
		{
			printf("-1\n");
			return 0;
		}
	}

    for(i = 0; i < num; i++)
    {
        qsort(graph[i]->list, graph[i]->cnt, sizeof(int32_t), cmp);
    }

    showADlist(graph, num);

    for(i = 0; i < num; i++)
    {
        int32_t *ans = (int32_t*)malloc(num*sizeof(int32_t));
        int32_t *visited = (int32_t*)malloc(num*sizeof(int32_t));
        top = 0;
        if(dfs(graph, i, 0, size, ans, visited))
        {
            for(j = 0; j < top - 1; j++)
            {
                printf("%d ", ans[j] + 1);
            }
            printf("%d", ans[top-1] + 1);
            return 0;
        }
    }
    printf("-1");
}

// bool DFSonNode(adjacency_list **graph, int32_t size, int32_t node2DFS, int32_t *ans, int32_t *visited, int32_t depth)
// {
//     int32_t i, j, k;
//     ans[top++] = node2DFS;
//     if(depth > size)
//     {
//         return false;
//     }
//     for(i = 0; i < graph[node2DFS]->cnt; i++)
//     {
//         if(visited[graph[node2DFS]->list[i]] == 1)
//         {
//             continue;
//         }
//         if(! DFSonNode(grapg, size, graph[node2DFS]->list[i], int32_t *ans, int32_t *visited, int32_t depth + 1))
//         {
//             return false;
//         }
//     }
//     return true;
// }

// for(j = i; CNT_visited < (num - 2); j = j+1, j%=num)
// {
//     visited[i] = 1;
//     for(k = 0; k < graph[j]->cnt; k++)
//     {
//         if(visited[graph[j]->list[k]] == 0 && depth[j] < size)
//         {
//             visited[graph[j]->list[k]] = 1;
//             depth[graph[j]->list[k]] = depth[j] + 1;
//             maxD = depth[graph[j]->list[k]];
//             CNT_visited ++;
//             printf("%d (%d, %d)vis: %d, dep: %d, CNT: %d\n", i, j, graph[j]->list[k], visited[graph[j]->list[k]], depth[graph[j]->list[k]], CNT_visited);
//             if(CNT_visited == (num-1) && maxD <= size)
//             {
//                 printf("%d\n", i);
//                 return 0;
//             }
//         }
//     }
// }