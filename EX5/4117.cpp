#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 1e5+7;
long long int seq[MAXN], sum[4 * MAXN], add[4 * MAXN];

void buildTree(int left, int right, int root);
void up(int root);
void down(int root, int left_num, int right_num);
void update(int a, int b, int c, int left, int right, int root);
long long int querySum(int a, int b, int left, int right, int root);
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, a, b, c;
    char op;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
    {
        cin >> seq[i];
    }
    buildTree(1, n, 1);
    for(int i = 0; i < m; ++i)
    {
        cin >> op;
        switch(op)
        {
            case 'Q':
                cin >> a >> b;
                cout << querySum(a, b, 1, n, 1) << '\n';
                break;
            case 'C':
                cin >> a >> b >> c;
                update(a, b, c, 1, n, 1);
                break;
        }
    }
    cout << flush;
    return 0;
}

void buildTree(int left, int right, int root)
{
    if(left == right)
    {
        sum[root] = seq[left];
        return;
    }
    int mid = (left + right) / 2;
    buildTree(left, mid, 2 * root);
    buildTree(mid + 1, right, 2 * root + 1);
    up(root);
}
void up(int root)
{
    sum[root] = sum[2 * root] + sum[2 * root + 1];
}
void down(int root, int left_num, int right_num)
{
    if(add[root])
    {
        add[2 * root] += add[root];
        add[2 * root + 1] += add[root];
        sum[2 * root] += add[root] * left_num;
        sum[2 * root + 1] += add[root] * right_num;
        add[root] = 0;
    }
}
void update(int a, int b, int c, int left, int right, int root)
{
    if(a <= left && right <= b)
    {
        sum[root] += c * (right - left + 1);
        add[root] += c;
        return;
    }
    int mid = (left + right) / 2;
    down(root, mid - left + 1, right - mid);
    if(a <= mid)
        update(a, b, c, left, mid, 2 * root);
    if(b > mid)
        update(a, b, c, mid + 1, right, 2 * root + 1);
    up(root);
}
long long int querySum(int a, int b, int left, int right, int root)
{
    if(a <= left && right <= b)
    {
        return sum[root];
    }
    int mid = (left + right) / 2;
    down(root, mid - left + 1, right - mid);
    long long int tmp = 0;
    if(a <= mid)
        tmp += querySum(a, b, left, mid, 2 * root);
    if(b > mid)
        tmp += querySum(a, b, mid + 1, right, 2 * root + 1);
    return tmp;
}