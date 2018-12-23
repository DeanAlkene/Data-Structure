#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e5+7;
int n, m;
bool vis[MAXN];
int subtree[MAXN];
struct edgeNode
{
    int idx;
    int weight;
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

void clear(int n)
{
    for(int i = 1; i <= n; ++i)
    {
        edgeNode *tmp, *cur;
        if(verList[i].head != NULL)
        {
            tmp = verList[i].head;
            cur = tmp->next;
            while(cur)
            {
                tmp = cur->next;
                delete cur;
                cur = tmp;
            }
            verList[i].head = NULL;
        }
    }
}

int DFS(int x)
{
    if(vis[x]) return 0;
    vis[x] = true;
    edgeNode *tmp;
    for(tmp = verList[x].head; tmp != NULL; tmp = tmp->next)
    {
        if(!vis[tmp->idx])
            subtree[x] += DFS(tmp->idx);
    }
    return ++subtree[x];
}

bool check(int k)
{
    memset(vis, 0, sizeof(vis));
    memset(subtree, 0, sizeof(subtree));
    subtree[1] = DFS(1);
    if(n % k == 0)
    {
        int cnt = 0;
        for(int i = 1; i <= n; ++i)
        {
            if(subtree[i] % k == 0)
                cnt++;
        }
        if(cnt == (n / k))
            return true;
        else
            return false;
    }
    else
        return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t, k, u, v;
    cin >> t;
    for(int i = 0; i < t; ++i)
    {
        cin >> n >> k;
        for(int j = 0; j < n-1; ++j)
        {
            cin >> u >> v;
            addEdge(u, v);
            addEdge(v, u);
        }
        if(check(k))
            cout << "YES" << '\n';
        else
            cout << "NO" << '\n';
        clear(n);
    }
    
    cout << flush;
    return 0;
}