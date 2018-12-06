#include <iostream>
#define MAXN 10000
using namespace std;

int main()
{
    int m;
    long long int outList[MAXN], ans = 0;
    cin >> m;
    for(int i = 0; i < m - 1; ++i)
        cin >> outList[i];
    
    //m for the total number i for the current number
    for(int i = 2; i <= m; ++i)
    {
        ans = (ans + outList[m - i]) % i;
    }
    cout << ans + 1 << endl;
    return 0;
}
