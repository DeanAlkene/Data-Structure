#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 100;
const int INF = 1e9;
int n, m, start, finish;
int q[100 * MAXN], distant[MAXN];

struct edgeNode
{
    int idx;
    int weight;
    edgeNode *next;
    edgeNode(int i, int w, edgeNode *n): idx(i), weight(w), next(n) {}
};

struct verNode
{
    int idx;
    edgeNode *head;
    verNode(int i = 0, edgeNode *h = NULL): idx(i), head(h) {}
};
verNode verList[MAXN];

void addEdge(int u, int v, int w)
{
    verList[u].head = new edgeNode(v, w, verList[u].head);
}

int BFS(int s, int f)
{
    int head = 0, tail = 0;
    edgeNode* tmp;
    q[tail++] = s;
    distant[s] = 0;
    while(head != tail)
    {
        int e = q[head++];
        for(tmp = verList[e].head; tmp != NULL; tmp = tmp->next)
        {
            if(distant[tmp->idx] > distant[e] + tmp->weight)
            {
                distant[tmp->idx] = distant[e] + tmp->weight;
                q[tail++] = tmp->idx;
            }
        }
    }
    return distant[f];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int u, v, w;
    cin >> n >> m >> start >> finish;
    for(int i = 0; i < m; ++i)
    {
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }
    for(int i = 0; i < MAXN; ++i)
        distant[i] = INF;
    int ans = BFS(start, finish);
    cout << ans << '\n';
    cout << flush;
    return 0;
}