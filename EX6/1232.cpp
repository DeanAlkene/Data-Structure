#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
const int MAXN = 1e5 + 7;
int tree[MAXN][4];
int foot[MAXN][4];
int path[MAXN];
int walk[MAXN];
bool visited[MAXN];
int q[MAXN];
class DisjointSet
{
    private:
        int size;
        int *parent;
    public:
        DisjointSet(int n);
        ~DisjointSet() {delete [] parent;}
        void Union(int root1, int root2);
        int Find(int x);
};
DisjointSet::DisjointSet(int n)
{
    size = n;
    parent = new int[size];
    for(int i = 0; i < size; ++i)
        parent[i] = -1;
}
void DisjointSet::Union(int root1, int root2)
{
    if(root1 == root2)
        return;
    if(parent[root1] > parent[root2])
    {
        parent[root2] += parent[root1];
        parent[root1] = root2;
    }
    else
    {
        parent[root1] += parent[root2];
        parent[root2] = root1;
    }
}

int DisjointSet::Find(int x)
{
    int start = x, tmp;
    while(parent[x] >= 0)
        x = parent[x];
    while(start != x)
    {
        tmp = parent[start];
        parent[start] = x;
        start = tmp;
    }
    return x;
}

void BFS(int start, int end)
{
    int s, e;
    int head, tail;
    s = start;
    head = tail = 0;
    walk[s] = 0;
    visited[s] = true;
    q[tail++] = s;
    while(head != tail)
    {
        s = q[head++];
        for(int i = 0; i < 4; ++i)
        {
            e = tree[s][i];
            if(e < 0 || visited[e])
                continue;
            walk[e] = walk[s] + 1;
            visited[e] = true;
            foot[e][i] = s;
            q[tail++] = e;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, a, b, pos1, pos2, op;
    cin >> n >> a >> b;
    DisjointSet s(n*(n+1)/2);
    memset(tree, -1, sizeof(tree));
    memset(walk, -1, sizeof(walk));
    memset(visited, false, sizeof(visited));
    memset(foot, -1, sizeof(foot));
    --a;
    --b;
    while(s.Find(a) != s.Find(b))
    {
        while(true)
        {
            cin >> pos1 >> op;
            int row = (int)(sqrt((double)pos1 * 2)) + 10;
            for(; row >= 1; row--)
            {
                if(row * (row + 1) < 2 * pos1)
                    break;
            }
            int col = pos1 - row * (row + 1) / 2;
            ++row;
            if(op == 0)
            {
                if(row > 1 && col > 1)
                {
                    pos2 = (row - 1) * (row - 2) / 2 + col - 1;
                    pos1--;
                    pos2--;
                    tree[pos2+1][3-op] = pos1+1;
                    tree[pos1+1][op] = pos2+1;
                    if(s.Find(pos1) != s.Find(pos2))
                        break;
                }
            }
            if(op == 1)
            {
                if(row > 1 && col < row)
                {
                    pos2 = (row - 1) * (row - 2) / 2 + col;
                    pos1--;
                    pos2--;
                    tree[pos2+1][3-op] = pos1+1;
                    tree[pos1+1][op] = pos2+1;
                    if(s.Find(pos1) != s.Find(pos2))
                        break;
                }
            }
            if(op == 2)
            {
                if(row < n)
                {
                    pos2 = row * (row + 1) / 2 + col;
                    pos1--;
                    pos2--;
                    tree[pos2+1][3-op] = pos1+1;
                    tree[pos1+1][op] = pos2+1;
                    if(s.Find(pos1) != s.Find(pos2))
                        break;
                }
            }
            if(op == 3)
            {
                if(row < n)
                {
                    pos2 = row * (row + 1) / 2 + col + 1;
                    pos1--;
                    pos2--;
                    tree[pos2+1][3-op] = pos1+1;
                    tree[pos1+1][op] = pos2+1;
                    if(s.Find(pos1) != s.Find(pos2))
                        break;
                }
            }
        }
        s.Union(s.Find(pos1), s.Find(pos2));
    }
    BFS(++a, ++b);
    int k = 0, pos = b;
    path[k++] = pos;
    while(pos != a)
    {
        for(int i = 0; i < 4; ++i)
        {
            if(foot[pos][i] > 0)
            {
                path[k++] = foot[pos][i];
                pos = foot[pos][i];
                break;
            }
        }
    }

    for(int i = k-1; i >= 0; --i)
        cout << path[i] << ' ';
    cout << '\n';
    cout << flush;
    return 0;
}
