#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 407;
int mat[MAXN][MAXN];
long long tmp[MAXN][2];

void calc(long long n, long long &odd, long long &even)
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i; j <= n; ++j)
        {
            for (int k = 1; k <= n; ++k)
            {
                if ((mat[i - 1][k] + mat[j][k]) % 2) //meet one
                {
                    tmp[k][0] = tmp[k - 1][1];
                    tmp[k][1] = tmp[k - 1][0] + 1;
                }
                else
                {
                    tmp[k][0] = tmp[k - 1][0] + 1;
                    tmp[k][1] = tmp[k - 1][1];
                }
                odd += tmp[k][1];
                even += tmp[k][0];
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int num;
    long long n, odd = 0, even = 0;
    memset(mat[0], 0, sizeof(mat[0]));
    memset(tmp, 0, sizeof(tmp));
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cin >> num;
            mat[i][j] = (num % 2 + mat[i - 1][j]) % 2; //Pre-Sum
        }
    }
    calc(n, odd, even);
    cout << odd << ' ' << even << '\n';
    cout << flush;
    return 0;
}