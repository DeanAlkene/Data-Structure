#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e6 + 7;
inline int max(int a, int b) {return a > b ? a : b;}
inline int min(int a, int b) {return a < b ? a : b;}
struct Node
{
    int lc, rc, max1, sum1, lazyTag;
    bool all_1;
};
bool in[MAXN];
Node tree[4 * MAXN];

void buildTree(int left, int right, int root);
void pushUp(int root);
void pushDown(int root, int left_num, int right_num);
void updateInterval(int L, int R, bool x, int left, int right, int root);
int querySum(int L, int R, int left, int right, int root);
int queryOne(int L, int R, int left, int right, int root);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, op, l, r, x, result;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
    {
        cin >> in[i];
    }
    buildTree(1, n, 1);
    for(int i = 0; i < m; ++i)
    {
        cin >> op;
        switch(op)
        {
            case 1:
                cin >> l >> r >> x;
                updateInterval(l, r, x, 1, n, 1);
                break;
            case 2:
                cin >> l >> r;
                result = querySum(l, r, 1, n, 1);
                cout << result << '\n';
                break;
            case 3:
                cin >> l >> r;
                result = queryOne(l, r, 1, n, 1);
                cout << result << '\n';
                break;
        }
    }

    cout << flush;
    return 0;
}

void buildTree(int left, int right, int root)
{
    tree[root].lazyTag = -1;
    if(left == right)
    {
        if(in[left])
        {
            tree[root].lc = tree[root].rc = tree[root].max1 = tree[root].sum1 = 1;
            tree[root].lazyTag = -1;
            tree[root].all_1 = true;
        }
        else
        {
            tree[root].lc = tree[root].rc = tree[root].max1 = tree[root].sum1 = 0;
            tree[root].lazyTag = -1;
            tree[root].all_1 = false;
        }
        return;
    }
    int mid = (left + right) / 2;
    buildTree(left, mid, 2 * root);
    buildTree(mid + 1, right, 2 * root + 1);
    pushUp(root);
    //tree[root].lazyTag = -1;
}
void pushUp(int root)
{
    Node &cur = tree[root], &left = tree[2 * root], &right = tree[2 * root + 1];
    cur.lc = left.lc + (left.all_1 ? right.lc : 0);
    cur.rc = right.rc + (right.all_1 ? left.rc : 0);
    cur.max1 = max(left.rc + right.lc, max(left.max1, right.max1));
    cur.all_1 = left.all_1 && right.all_1;
    cur.sum1 = left.sum1 + right.sum1;
    cur.lazyTag = -1;
}
void pushDown(int root, int left_num, int right_num)
{
    if(tree[root].lazyTag != -1)
    {
        Node &cur = tree[root], &left = tree[2 * root], &right = tree[2 * root + 1];
        left.lazyTag = cur.lazyTag;
        right.lazyTag = cur.lazyTag;
        left.lc = left.rc = left.max1 = left.sum1 = cur.lazyTag * left_num;
        right.lc = right.rc = right.max1 = right.sum1 = cur.lazyTag * right_num;
        left.all_1 = right.all_1 = cur.lazyTag;
        cur.lazyTag = -1;
    }
}
void updateInterval(int L, int R, bool x, int left, int right, int root)
{
    if(L <= left && right <= R)
    {
        tree[root].lc = tree[root].rc = tree[root].max1 = tree[root].sum1 = x * (right - left + 1);
        tree[root].all_1 = x;
        tree[root].lazyTag = x;
        return;
    }
    int mid = (left + right) / 2;
    pushDown(root, mid - left + 1, right - mid);
    if(L <= mid)
        updateInterval(L, R, x, left, mid, 2 * root);
    if(R > mid)
        updateInterval(L, R, x, mid + 1, right, 2 * root + 1);
    pushUp(root);
}
int querySum(int L, int R, int left, int right, int root)
{
    if(L <= left && right <= R)
    {
        return tree[root].sum1;
    }
    int mid = (left + right) / 2;
    pushDown(root, mid - left + 1, right - mid);
    int tmp = 0;
    if(L <= mid)
        tmp += querySum(L, R, left, mid, 2 * root);
    if(R > mid)
        tmp += querySum(L, R, mid + 1, right, 2 * root + 1);
    return tmp;
}
int queryOne(int L, int R, int left, int right, int root)
{
    if(L <= left && right <= R)
    {
        return tree[root].max1;
    }
    int mid = (left + right) / 2;
    int tmp = 0;
    pushDown(root, mid - left + 1, right - mid);
    if(L <= mid)
        tmp = max(tmp, queryOne(L, R, left, mid, 2 * root));
    if(R > mid)
        tmp = max(tmp, queryOne(L, R, mid + 1, right, 2 * root + 1));
    if(L <= mid && R > mid)
    {
        int lrmax1 = min((mid - L + 1), tree[2 * root].rc);
        int rlmax1 = min((R - mid), tree[2 * root + 1].lc);
        tmp = max(tmp, lrmax1 + rlmax1);
    }
    return tmp;
}
