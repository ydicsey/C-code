/*
 * @lc app=leetcode.cn id=130 lang=c
 *
 * [130] 被围绕的区域
 */

// @lc code=start

// BFS in c
int m;
int n;

void show(char ** board)
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

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
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
void bfs(char **board, int x, int y)
{
    Queue* q = creatQueue(m*n);
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
                if(new_x < 0 || new_x >= m || new_y < 0 || new_y >= n || board[new_x][new_y] != 'O')
                {
                    continue;
                }
                board[new_x][new_y] = 'V';
                enqueue(q, new_x, new_y);
            }
        }
    }
}

void solve(char** board, int boardSize, int* boardColSize){
    m = boardSize;
    n = boardColSize[0];

    // 從邊界開始BFS
    for(int i = 0; i < n; i++)
    {
        // printf("%c, %c\n", board[i][0], board[i][n-1]);
        if( board[0][i] == 'O')
        {
            // 遇到O開始BFS
            // 把所有連接邊界的O改成V:visited
            board[0][i] = 'V';
            bfs(board, 0, i);
        }
        if( board[m-1][i] == 'O')
        {
            board[m-1][i] = 'V';
            bfs(board, m-1, i);
        }
    }
    for(int i = 1; i < m-1; i++)
    {
        // printf("%c, %c\n", board[0][i], board[m-1][i]);
        if( board[i][0] == 'O')
        {
            board[i][0] = 'V';
            bfs(board, i, 0);
        }
        if( board[i][n-1] == 'O')
        {
            board[i][n-1] = 'V';
            bfs(board, i, n-1);
        }
    }
    // show(board);

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if('V' == board[i][j])
            {
                board[i][j] = 'O';
            }
            else if('O' == board[i][j])
            {
                board[i][j] = 'X';
            }
        }
    }
}
// @lc code=end

