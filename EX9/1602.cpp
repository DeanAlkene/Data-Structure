#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e5+7;
int num1[MAXN], num2[MAXN], ans[2*MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int m, n, i, j, k = 0;
    cin >> m;
    cin >> n;
    for(i = 0; i < m; ++i)
        cin >> num1[i];
    for(i = 0; i < n; ++i)
        cin >> num2[i];
    i = j = 0;
    while(i < m && j < n)
    {
        if(num1[i] <= num2[j])
            ans[k++] = num1[i++];
        else
            ans[k++] = num2[j++];
    }
    while(i < m)
        ans[k++] = num1[i++];
    while(j < n)
        ans[k++] = num2[j++];
    for(i = 0 ; i < k; ++i)
        cout << ans[i] << ' ';
    cout << '\n';

    cout << flush;
    return 0;
}