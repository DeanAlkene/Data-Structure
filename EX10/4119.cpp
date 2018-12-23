#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 20007;
const int INF = 1e9;
int n, a, b, c;
int A[MAXN], B[MAXN], C[MAXN], q[10*MAXN];
bool vis[MAXN];
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

void BFS(int s, int *a)
{
    memset(vis, 0, sizeof(vis));
    int head = 0, tail = 0;
    edgeNode* tmp;
    q[tail++] = s;
    a[s] = 0;
    while(head != tail)
    {
        int e = q[head++];
        for(tmp = verList[e].head; tmp != NULL; tmp = tmp->next)
        {
            if(a[tmp->idx] > a[e] + tmp->weight)
            {
                a[tmp->idx] = a[e] + tmp->weight;
                if(!vis[tmp->idx])
                {
                    q[tail++] = tmp->idx;
                    vis[tmp->idx] = true;
                }

            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int u, v, w;
    cin >> n >> a >> b >> c;
    for(int i = 1; i <= n; ++i)
    {
        verList[i].idx = i;
    }
    for(int i = 0; i < n-1; ++i)
    {
        cin >> u >> v >> w;
        addEdge(u, v ,w);
        addEdge(v, u, w);
    }
    for(int i = 1; i <= n; ++i)
        A[i] = B[i] = C[i] = INF;
    BFS(a, A);
    BFS(b, B);
    BFS(c, C);
    int ans = INF, pos;

    for(int i = 1; i<= n; ++i)
    {
        if(ans > A[i] + B[i] + C[i])
        {
            pos = i;
            ans = A[i] + B[i] + C[i];
        }
    }
    cout << pos << '\n';
    cout << ans << '\n';
    cout << flush;
    return 0;
}