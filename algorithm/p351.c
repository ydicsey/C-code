#include<stdio.h>
#include<string.h>
#include<stdint.h>
#define MAX 103
#define INF 100000000
#define Min(x, y) ((x)>(y)?(y):(x))

int32_t distance[MAX][MAX];
int32_t adjacency[MAX][MAX];

int main()
{
    int32_t numofStations, numofLines, i ,j ,k;
    for(i = 0; i < MAX; i++)
    {
        for(j = 0; j < MAX; j++)
        {
            adjacency[i][j] = INF;
        }
    }
    scanf("%d %d", &numofStations, &numofLines);
    for(i = 0; i < numofLines; i++)
    {
        int32_t x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        adjacency[x][y] = Min(adjacency[x][y], adjacency[y][x]);
        adjacency[x][y] = Min(adjacency[x][y], w);
        adjacency[y][x] = Min(adjacency[x][y], adjacency[y][x]);
    }

    memcpy(distance, adjacency, sizeof(adjacency));
    for(i = 1; i <= numofStations; i++)
    {
        distance[i][i] = INF;
    }

    int32_t ans = INF;

    for(int k = 1; k <= numofStations; k++)
    {
		for(int i = 1; i <= k; i++)
        {
			for(int j = 1; j <= k; j++)
            {
                if(i != j)
                {
                    if (adjacency[k][i] + distance[i][j] + adjacency[j][k] < ans)
                    {
                        ans = adjacency[k][i] + distance[i][j] + adjacency[j][k];
                    }
                }
			}
		}
        for(i = 1; i <= numofStations; i++)
        {
            for(j = 1; j <= numofStations; j++)
            {
                if (distance[i][k] + distance[k][j] < distance[i][j])
                {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
	}
    if(ans == INF)
    {
        printf("-1");
        return 0;
    }
    printf("%d", ans);
    return 0;
}