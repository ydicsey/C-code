#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#define MAX 103
#define min(x, y) ((x)>(y)?(y):(x))

// queue c implementation
typedef struct
{
    int32_t front, rear, size;
    int32_t capacity;
    int32_t *array;
}Queue;

Queue* creatQueue(int32_t capacity)
{
    Queue* q = (Queue*)malloc(capacity * sizeof(Queue));
    q->capacity = capacity;
    q->front = 0;
    q->size = 0;
    q->rear = capacity - 1;
    q->array = (int32_t*)malloc(q->capacity * sizeof(int32_t));

    return q;
}

int isFull(Queue* queue)
{
    return (queue->size == queue->capacity);
}

int isEmpty(Queue* queue)
{
    return (queue->size == 0);
}

void enqueue(Queue* queue, int32_t node2in)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = node2in;
    queue->size = queue->size + 1;
    // printf("(%d, %d) enqueued to queue\n", p.x, p.y);
}

int32_t dequeue(Queue* queue)
{
    int32_t node2out;
    if (isEmpty(queue))
        return -1;
    node2out = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return node2out;
}
// queue c implementation end
// V -> Number of vertices in graph
bool bfs(int32_t** graph, int32_t s, int32_t t, int32_t* parent, int32_t V)
{
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    Queue *Q = creatQueue(MAX);
    enqueue(Q, s);

    visited[s] = true;
    parent[s] = -1;

    int32_t u, i;

    while(!isEmpty(Q))
    {
        u = dequeue(Q);
        for(i = 0; i < V; i++)
        {
            if(!visited[i] && graph[u][i] > 0)
            {
                if(i == t)
                {
                    parent[i] = u;
                    return true;
                }
                enqueue(Q, i);
                parent[i] = u;
                visited[i] = true;
            }
        }
    }
    // cannot reach T in BFS starting from S
    return false;
}

int32_t fordFulkerson(int32_t **graph, int32_t s, int32_t t, int32_t V)
{

    int32_t i, j, maxFlow = 0;

    int32_t** residualG = calloc(V*V, sizeof(int32_t));

    for(i = 0; i < V; i++)
    {
        residualG[i] = malloc(V * sizeof(int32_t));
        for(j = 0; j < V; j++)
        {
            residualG[i][j] = graph[i][j];
        }
    }

    int *parent = malloc(V * sizeof(int32_t));

    while(bfs(residualG, s, t, parent, V))
    {
        int32_t pathFlow = INT_MAX;
        for(i = t; i != s; i = parent[i])
        {
            j = parent[i];
            pathFlow = min(pathFlow, residualG[j][i]);
        }

        for(i = t; i != s; i = parent[i])
        {
            j = parent[i];
            residualG[j][i] -= pathFlow;
            residualG[i][j] += pathFlow;
        }

        maxFlow += pathFlow;
    }
    return maxFlow;
}

int main()
{
    int32_t i, j;
    int32_t N, M;
    int32_t u, v, w;
    scanf("%d %d", &N, &M);

    int32_t** graph = calloc((N+2)*(N+2), sizeof(int32_t));
    for(i = 0; i < N+2; i++)
    {
        graph[i] = malloc((N+2) * sizeof(int32_t));
    }

    for(i = 0; i < N; i++)
    {
        scanf("%d", &graph[i+1][N+1]);
    }
    for(i = 0; i < N; i++)
    {
        scanf("%d", &graph[0][i+1]);
    }
    for(i = 0; i < M; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }

    // for(i = 0; i < N+2; i++)
    // {
    //     for(j = 0; j < N+2; j++)
    //     {
    //         printf(" %d ", graph[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("%d", fordFulkerson(graph, 0, N+1, N+2));
}