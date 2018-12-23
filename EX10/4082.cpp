#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

class DisjointSet
{
    private:
        int sz;
        int *parent;
    public:
        DisjointSet(int n);
        ~DisjointSet() {};
        void Union(int root1, int root2);
        int Find(int x);
        long long getBlocks()
        {
            long long cnt = 0;
            for(int i = 0; i < sz; ++i)
            {
                if(parent[i] < 0)
                {
                    cnt += (-parent[i]) * (-parent[i] - 1) / 2;
                }
            }
            return cnt;
        }
};
DisjointSet::DisjointSet(int n)
{
     sz = n;
     parent = new int[n+1];
     for(int i = 0; i <= sz; ++i)
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
    if(parent[x] < 0) return x;
    return parent[x] = Find(parent[x]);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int u, v, m, n;
    cin >> n >> m;
    DisjointSet s(n+1);
    for(int i = 0; i < m; ++i)
    {
        cin >> u >> v;
        s.Union(s.Find(u), s.Find(v));
    }
    cout << s.getBlocks() - m << '\n';
    cout << flush;
    return 0;
}
