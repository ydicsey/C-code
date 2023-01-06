#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
const long INF = __LONG_MAX__/2-100;
#define MAX 100005

using namespace std;

struct node{
    int vertex;
    long dist;
};

vector<node> graph[MAX];

//first=weight; second=destination/node
typedef pair<long, int> DP;

long dijkstra(int src, int vertex, int N)
{
    int i; 
    long alt;
    priority_queue<DP, vector<DP>, greater<DP>> Q;

    // unsigned long long int dist[N];
    // fill(dist, dist+N, INF);
    vector<long> dist(N, INF);
    dist[src] = 0;

    Q.push(DP(0, src));

    while( !Q.empty())
    {
        // extract min
        DP smallest = Q.top();
        Q.pop();

        // if(smallest.second == vertex)
        // {
        //     return dist[vertex];
        // }
        if(dist[smallest.second] < smallest.first)
        {
            continue;
        }

        for(i = 0; i < graph[smallest.second].size(); i++)
        {
            node tmp = graph[smallest.second][i];
            alt = (long)(dist[smallest.second] + tmp.dist);
            if(dist[tmp.vertex] > alt && dist[smallest.second] < INF)
            {
                dist[tmp.vertex] = (long)alt;
                // if(tmp.vertex == vertex)
                // {
                //     return dist[vertex];
                // }
                Q.push(DP(dist[tmp.vertex], tmp.vertex));
            }
        }
    }
    return dist[vertex];
}


int main()
{
    long i, w;
    int N, M;
    int home, stop1, stop2, customer;
    int u, v;

    cin >> N >> M;
    cin >> home >> stop1 >> stop2 >> customer;

    for(i = 0; i < M; i++)
    {
        cin >> u >> v >> w;
        graph[u-1].push_back((node){v-1, w});
        graph[v-1].push_back((node){u-1, w});
    }

    i = (long)0;
    i += (long)dijkstra(home-1, stop1-1, N);
    i += (long)dijkstra(stop1-1, stop2-1, N);
    i += (long)dijkstra(stop2-1, customer-1, N);
    i += (long)dijkstra(customer-1, home-1, N);

    // i *= 100000000000000000;
    cout << i << endl;
    // cout << __LONG_MAX__ <<endl;
}