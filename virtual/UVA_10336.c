#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

typedef struct
{
    int x;
    int y;
}point;

// queue c implementation
typedef struct
{
    int front, rear, size;
    int capacity;
    point *array;
}Queue;

Queue* creatQueue(int capacity)
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

void enqueue(Queue* queue, int x, int y)
{
    point p;
    p.x = x;
    p.y = y;
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
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
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
void bfs(char** grid, int x, int y, int **visited, int row, int col, int *cnt)
{
    Queue* q = creatQueue(row * col);
    enqueue(q, x, y);

    while(!isEmpty(q))
    {
        int CNT = q->size;
        while(CNT--)
        {
            point tmp = dequeue(q);
            for(int i = 0; i < 4; i++)
            {
                int new_x = tmp.x + dx[i];
                int new_y = tmp.y + dy[i];
                if(new_x < 0 || new_x >= row || new_y < 0 || new_y >= col || grid[new_x][new_y] != grid[x][y] || visited[new_x][new_y])
                {
                    continue;
                }
                // cnt[grid[x][y] - 'a'] ++;
                visited[new_x][new_y] = 1;
                enqueue(q, new_x, new_y);
            }
        }
    }
}

int cmp(const void *a, const void *b)
{
    point* A = (point*)a;
    point* B = (point*)b;
    if(A->y == B->y)
    {
        return (A->x - B->x);
    }
    return (B->y - A->y);
}

int main()
{
    int cnt;
    int i, j, k;
    scanf("%d", &cnt);
    for(k = 0; k < cnt; k++)
    {
        int row, col;

        scanf("%d %d", &row, &col);
        char** grid = (char**)calloc(row * col, sizeof(char*));
        int** visited = (int**)calloc(row * col, sizeof(int*));
        int *alpha_cnt = (int*)malloc(26 * sizeof(int));
        
        int alpha_idx = 0;

        for(i = 0; i < row; i++)
        {
            grid[i] = (char*)malloc(col * sizeof(char));
            visited[i] = (int*)malloc(col * sizeof(int));
            for(j = 0; j < col; j++)
            {
                scanf("\n%c", &grid[i][j]);
                visited[i][j] = 0;
            }
        }

        for(i = 0; i < row; i++)
        {
            for(j = 0; j < col; j++)
            {
                if(visited[i][j] == 0)
                {
                    visited[i][j] = 1;
                    if(alpha_cnt[grid[i][j] - 'a'] == 0)
                    {
                        alpha_idx++;
                    }
                    alpha_cnt[grid[i][j] - 'a']++;

                    bfs(grid, i, j, visited, row, col, alpha_cnt);
                }
            }
        }

        // print alpha_cnt array
        point *alpha_list = (point*)malloc(alpha_idx * sizeof(point));
        j = 0;
        for(i = 0; i < 26; i++)
        {
            // printf("%d ", alpha_cnt[i]);
            if(alpha_cnt[i])
            {
                alpha_list[j].x = i;
                alpha_list[j++].y = alpha_cnt[i];
            }
        }
        printf("World #%d\n", k+1);

        // sort alpha_list
        qsort(alpha_list, alpha_idx, sizeof(point), cmp);
        // printf("%d\n", alpha_idx);
        for(i = 0; i < alpha_idx; i++)
        {
            printf("%c: %d\n", alpha_list[i].x + 'a', alpha_list[i].y);
        }
    }
}