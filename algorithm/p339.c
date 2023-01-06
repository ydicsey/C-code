#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

typedef struct
{
    int32_t x;
    int32_t y;
}point;

// n * m
int32_t m, n;

// queue c implementation
typedef struct
{
    int32_t front, rear, size;
    int32_t capacity;
    point *array;
}Queue;

Queue* creatQueue(int32_t capacity)
{
    Queue* q = (Queue*)malloc(capacity * sizeof(Queue));
    q->capacity = capacity;
    q->front = 0;
    q->size = 0;
    q->rear = capacity - 1;
    q->array = (point*)malloc(q->capacity * sizeof(point));

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

void enqueue(Queue* queue, int32_t x, int32_t y)
{
    point p;
    p.x = x;
    p.y = y;
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = p;
    queue->size = queue->size + 1;
    // printf("(%d, %d) enqueued to queue\n", p.x, p.y);
}

point dequeue(Queue* queue)
{
    point item;
    item.x = -1;
    item.y = -1;
    if (isEmpty(queue))
        return item;
    item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

/*
leva[i][j] -> the earliest time for leva to arrive at(i,j)
*/
// Leva spread -> 多源BFS

void show2Dstring(const int32_t** a, int32_t n, int32_t m)
{
    int32_t i, j;
    printf("\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
}

// check with binary search like p293
/*
int left = 0, right = m*n
while(left < right)
{
    int mid = right - (right - left) / 2
    if(check(grid, leva, mid))
    {
        left = mid;
    }
    else
    {
        right = mid - 1
    }

    if(check(grid, leva, left))
    {
        return left
    }
    return -1
}
*/

bool checkOK(point start, point end, int32_t** grid, int32_t** leva, int32_t time)
{
    // printf("\ntime: %d, ", time);
    // printf("end(%d, %d)\n", end.x, end.y);
    int32_t i, j, k;
    int32_t **visited = calloc(n*m, sizeof(int32_t));
    for(i = 0; i < n; i++)
    {
        visited[i] = malloc(m * sizeof(int32_t));
    }

    Queue* q = creatQueue(m*n);
    enqueue(q, start.x, start.y);
    visited[start.x][start.y] = 1;

    while(!isEmpty(q))
    {
        int32_t CNT = q->size;
        // printf("\n1: %d\n", CNT_leva);
        while(CNT--)
        {
            point tmp = dequeue(q);
            // printf("(%d, %d)\n", tmp.x, tmp.y);
            // up
            if((tmp.x - 1) >= 0)
            {
                if(!(grid[tmp.x - 1][tmp.y] == 'O' || visited[tmp.x - 1][tmp.y] || leva[tmp.x - 1][tmp.y] <= time))
                {
                    // printf(" up ");
                    visited[tmp.x -1][tmp.y] = 1;
                    if((tmp.x-1) != end.x || tmp.y != end.y)
                    {
                        enqueue(q, tmp.x-1, tmp.y);
                    }
                    if((tmp.x - 1) == end.x && tmp.y == end.y)
                    {
                        return true;
                    }
                }
            }
            // down
            if((tmp.x + 1) < n)
            {
                if(!(grid[tmp.x + 1][tmp.y] == 'O' || visited[tmp.x + 1][tmp.y] || leva[tmp.x + 1][tmp.y] <= time))
                {
                    // printf(" down ");
                    visited[tmp.x + 1][tmp.y] = 1;
                    if((tmp.x + 1) != end.x || tmp.y != end.y)
                    {
                        enqueue(q, tmp.x+1, tmp.y);
                    }
                    if((tmp.x + 1) == end.x && tmp.y == end.y)
                    {
                        return true;
                    }
                }
            }
            // left
            if((tmp.y - 1) >= 0)
            {
                if(!(grid[tmp.x][tmp.y - 1] == 'O' || visited[tmp.x][tmp.y - 1] || leva[tmp.x][tmp.y - 1] <= time))
                {
                    // printf(" left ");
                    visited[tmp.x][tmp.y - 1] = 1;
                    if(tmp.x != end.x || (tmp.y - 1) != end.y)
                    {
                        enqueue(q, tmp.x, tmp.y-1);
                    }
                    if(tmp.x == end.x && (tmp.y - 1) == end.y)
                    {
                        return true;
                    }
                }
            }
            // right
            if((tmp.y + 1) < m)
            {
                if(!(grid[tmp.x][tmp.y + 1] == 'O' || visited[tmp.x][tmp.y + 1] || leva[tmp.x][tmp.y + 1] <= time))
                {
                    // printf(" right ");
                    visited[tmp.x][tmp.y + 1] = 1;
                    if(tmp.x != end.x || (tmp.y + 1) != end.y)
                    {
                        enqueue(q, tmp.x, tmp.y+1);
                    }
                    if(tmp.x == end.x && (tmp.y + 1) == end.y)
                    {
                        return true;
                    }
                }
            }
        }
    }
    // show2Dstring(visited, n, m);
    return false;
}


int main()
{
    int32_t i, j, levastep = 0;
    point start, end;

    scanf("%d %d", &n, &m);
    // creat queue
    Queue *q = creatQueue(m*n);

    // grid -> input
    int32_t **grid = calloc(m * n, sizeof(int32_t));
    // leva[i][j] -> the earliest time for leva to arrive at(i,j)
    int32_t **leva = calloc(m * n, sizeof(int32_t));

    for(i = 0; i < n; i++)
    {
        grid[i] = malloc(m * sizeof(int32_t));
        leva[i] = malloc(m * sizeof(int32_t));
        for(j = 0; j < m; j++)
        {
            scanf("\n%c", &grid[i][j]);
            // initial leva
            leva[i][j] = INT_MAX;
            if(grid[i][j] == 'L')
            {
                // push into queue
                enqueue(q, i, j);
                // grid[i][j] = 0; -> input grid position
                leva[i][j] = levastep;
            }
            else if(grid[i][j] == 'B')
            {
                start.x = i;
                start.y = j;
            }
            else if(grid[i][j] == 'D')
            {
                end.x = i;
                end.y = j;
            }
        }
    }
    // show2Dstring(grid, n, m);

    // BFS on leva[i][j]
    while(!isEmpty(q))
    {
        
        int32_t CNT_leva = q->size;
        // printf("\n1: %d\n", CNT_leva);
        while(CNT_leva--)
        {
            point tmp = dequeue(q);
            // printf("(%d, %d)\n", tmp.x, tmp.y);
            // up
            if((tmp.x - 1) >= 0)
            {
                if(!(grid[tmp.x -1][tmp.y] == 'D' || grid[tmp.x -1][tmp.y] == 'B' || grid[tmp.x -1][tmp.y] == 'O' || leva[tmp.x - 1][tmp.y] != INT_MAX))
                {
                    // printf(" up ");
                    leva[tmp.x -1][tmp.y] = levastep + 1;
                    if(tmp.x-1 != n - 1 || tmp.y != m - 1)
                    {
                        enqueue(q, tmp.x-1, tmp.y);
                    }
                }
            }
            // down
            if((tmp.x + 1) < n)
            {
                if(!(grid[tmp.x + 1][tmp.y] == 'D' || grid[tmp.x + 1][tmp.y] == 'B' || grid[tmp.x + 1][tmp.y] == 'O' || leva[tmp.x + 1][tmp.y] != INT_MAX))
                {
                    // printf(" down ");
                    leva[tmp.x + 1][tmp.y] = levastep + 1;
                    if(tmp.x+1 != n - 1 || tmp.y != m - 1)
                    {
                        enqueue(q, tmp.x+1, tmp.y);
                    }
                }
            }
            // left
            if((tmp.y - 1) >= 0)
            {
                if(!(grid[tmp.x][tmp.y - 1] == 'D' || grid[tmp.x][tmp.y - 1] == 'B' || grid[tmp.x][tmp.y - 1] == 'O' || leva[tmp.x][tmp.y - 1] != INT_MAX))
                {
                    // printf(" left ");
                    leva[tmp.x][tmp.y - 1] = levastep + 1;
                    if(tmp.x != n - 1 || tmp.y-1 != m - 1)
                    {
                        enqueue(q, tmp.x, tmp.y-1);
                    }
                }
            }
            // right
            if((tmp.y + 1) < m)
            {
                if(!(grid[tmp.x][tmp.y + 1] == 'D' || grid[tmp.x][tmp.y + 1] == 'B' || grid[tmp.x][tmp.y + 1] == 'O' || leva[tmp.x][tmp.y + 1] != INT_MAX))
                {
                    // printf(" right ");
                    leva[tmp.x][tmp.y + 1] = levastep + 1;
                    if(tmp.x != n - 1 || tmp.y+1 != m - 1)
                    {
                        enqueue(q, tmp.x, tmp.y+1);
                    }
                }
            }
        }
        levastep++;
    }
    // printf("\nleva:");
    // show2Dstring(leva, n, m);
    // leva BFS finished


    
    int32_t left = 0, right = n*m;
    while(left < right)
    {
        int32_t mid = right - (right-left)/2;
        if(checkOK(start, end, grid, leva, mid))
        {
            left = mid;
        }
        else
        {
            right = mid - 1;
        }
    }
    if(checkOK(start, end, grid, leva, left) && left)
    {
        printf("%d", left);
        return 0;
    }
    else 
    {
        printf("-1");
        return 0;
    }
}