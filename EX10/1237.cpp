#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e5+7;
int n, m;
int inDegree[MAXN], q1[2 * MAXN], q2[2 * MAXN];
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

int topSort()
{
    int head1, tail1, head2, tail2, cur, semester = 1;
    edgeNode *tmp;
    memset(inDegree, 0, sizeof(inDegree));
    head1 = tail1 = head2 = tail2 = 0;
    for(int i = 1; i <= n; ++i)
    {
        for(tmp = verList[i].head; tmp != NULL; tmp = tmp->next)
            ++inDegree[tmp->idx];
    }
    for(int i = 1; i <= n; ++i)
    {
        if(inDegree[i] == 0)
            q1[tail1++] = i;
    }
    while(true)
    {
        while(head1 != tail1)
        {
            cur = q1[head1++];
            for(tmp = verList[cur].head; tmp != NULL; tmp = tmp->next)
            {
                if(--inDegree[tmp->idx] == 0)
                {
                    q2[tail2++] = tmp->idx;
                }
            }
        }
        if(head2 == tail2)
            break;
        ++semester;
        while(head2 != tail2)
        {
            cur = q2[head2++];
            for(tmp = verList[cur].head; tmp != NULL; tmp = tmp->next)
            {
                if(--inDegree[tmp->idx] == 0)
                {
                    q1[tail1++] = tmp->idx;
                }
            }
        }
        if(head1 == tail1)
            break;
        ++semester;
    }
    
    return semester;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int u, v;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
    {
        verList[i].idx = i;
    }
    for(int i = 0; i < m; ++i)
    {
        cin >> u >> v;
        addEdge(u, v);
    }
    int ans = topSort();
    cout << ans << '\n';
    cout << flush;
    return 0;
}