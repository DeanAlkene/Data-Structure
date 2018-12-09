#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 2e6 + 7;
int rate[MAXN], day[MAXN], tree[4 * MAXN];

void pushUp(int root)
{
    if (rate[tree[2 * root]] < rate[tree[2 * root + 1]])
        tree[root] = tree[2 * root];
    else
    {
        if (rate[tree[2 * root]] > rate[tree[2 * root + 1]])
            tree[root] = tree[2 * root + 1];
        else
        {
            if (day[tree[2 * root]] > day[tree[2 * root + 1]])
                tree[root] = tree[2 * root];
            else
                tree[root] = tree[2 * root + 1];
        }
    }
}

void build(int left, int right, int root)
{
    if (left == right)
    {
        tree[root] = left;
        return;
    }
    int mid = (left + right) / 2;
    build(left, mid, 2 * root);
    build(mid + 1, right, 2 * root + 1);
    pushUp(root);
}

void update(int left, int right, int root, int index)
{
    if (left == right)
        return;
    int mid = (left + right) / 2;
    if (index <= mid)
        update(left, mid, 2 * root, index);
    else
        update(mid + 1, right, 2 * root + 1, index);
    pushUp(root);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, x, y, today;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> rate[i];
        day[i] = i;
    }
    today = n + 1;
    build(1, n, 1);
    for (int i = 0; i < m; ++i)
    {
        cin >> x >> y;
        day[x] = today++;
        rate[x] += y;
        update(1, n, 1, x);
        cout << tree[1] << '\n';
    }

    cout << flush;
    return 0;
}