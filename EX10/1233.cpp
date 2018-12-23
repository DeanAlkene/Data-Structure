#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 107;
int n, m, start, num;
bool vis[MAXN];
struct edgeNode
{
    int idx;
    edgeNode *next;
    edgeNode(int i, edgeNode *n): idx(i), next(n) {}
};

struct verNode
{
    int idx;
    edgeNode *head;
    verNode(int i = 0, edgeNode *h = NULL): idx(i), head(h) {}
};
verNode verList[MAXN];

void addEdge(int u, int v)
{
    verList[u].head = new edgeNode(v, verList[u].head);
}

void DFS(int s, int len, int &nodes, int &ans)
{
    edgeNode *tmp = verList[s].head;
    vis[s] = true;
    ++nodes;
    if(nodes == len+1)
    {
        vis[s] = false;
        --nodes;
        ++ans;
        return;
    }
    while(tmp != NULL)
    {
        if(!vis[tmp->idx])
            DFS(tmp->idx, len, nodes, ans);
        tmp = tmp->next;
    }
    vis[s] = false;
    --nodes;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int u, v;
    cin >> n >> m >> start >> num;
    for(int i = 1; i <= n; ++i)
    {
        verList[i].idx = i;
    }
    for(int i = 0; i < m; ++i)
    {
        cin >> u >> v;
        addEdge(u, v);
    }

    memset(vis, 0, sizeof(vis));
    int ans = 0, nodes = 0;
    DFS(start, num, nodes, ans);
    cout << ans << '\n';
    cout << flush;
    return 0;
}