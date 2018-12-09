#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e5 + 7;
int s[MAXN];
inline int max(int a, int b) { return a > b ? a : b; }
struct Node
{
    int index;
    Node *next;
    Node(int idx = 0, Node *n = NULL) : index(idx), next(n) {}
};
Node nodeList[MAXN];
void add(int u, int v)
{
    Node *cur, *tmp;
    if (nodeList[u].next == NULL)
    {
        nodeList[u].next = new Node(v, NULL);
    }
    else
    {
        cur = nodeList[u].next;
        while (cur->next)
            cur = cur->next;
        tmp = new Node(v, NULL);
        cur->next = tmp;
    }
    if (nodeList[v].next == NULL)
    {
        nodeList[v].next = new Node(u, NULL);
    }
    else
    {
        cur = nodeList[u].next;
        while (cur->next)
            cur = cur->next;
        tmp = new Node(v, NULL);
        cur->next = tmp;
    }
    nodeList[u].index++;
    nodeList[v].index++;
}

int find(int u, int v)
{
    Node *cur = nodeList[u].next;
    for (int i = 0; i < v && cur->next; ++i)
        cur = cur->next;
    return cur->index;
}

int DFS(int root, int parent, int n)
{
    int k, ans, son = 0, sum = 1, len = nodeList[root].index;
    s[root] = 0;
    for (int i = 0; i < len; ++i)
    {
        k = find(root, i);
        if (k == parent)
            continue;
        ans = DFS(k, root, n);
        son = max(son, ans);
        sum += ans;
    }
    s[root] = max(n - sum, son);
    return sum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(s, 0, sizeof(s));
    int n, u, v;
    cin >> n;
    for (int i = 0; i < n - 1; ++i)
    {
        cin >> u >> v;
        add(u, v);
    }
    DFS(1, 0, n);
    for (int i = 1; i <= n; ++i)
    {
        if (2 * s[i] <= n)
        {
            cout << i << ' ';
        }
    }
    cout << '\n';
    cout << flush;
    return 0;
}