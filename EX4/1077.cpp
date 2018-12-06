#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 50;
int inorder[MAXN], root[MAXN][MAXN];
long long int point[MAXN][MAXN];
//point[i][j] = max{point[i][k-1] * point[k+1][j] + inorder[k]}
void preOrder(int i, int j)
{
    if(i <= j)
    {
        cout << root[i][j] << ' ';
        preOrder(i, root[i][j] - 1);
        preOrder(root[i][j] + 1, j);
    }
}

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i <= n; ++i)
    {
        for(int j = 0; j <= n; ++j)
        {
            point[i][j] = 1;
        }
    }
    for(int i = 1; i <= n; ++i)
    {
        cin >> inorder[i];
        point[i][i] = inorder[i];
        root[i][i] = i;
    }
    for(int len = 1; len <= n - 1; ++len)
    {
        for(int i = 1; i <= n - len; ++i)
        {
            int j = i + len;
            point[i][j] = 0;
            for(int k = i; k <= j; k++)
            {
                if(point[i][j] < point[i][k-1] * point[k+1][j] + inorder[k])
                {
                    point[i][j] = point[i][k-1] * point[k+1][j] + inorder[k];
                    root[i][j] = k;
                }
            } 
        }
    }
    cout << point[1][n] << '\n';
    preOrder(1, n);
    cout << '\n';
    return 0;
}