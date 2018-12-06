#include <iostream>
#include <cmath>
using namespace std;

long long int bigMod(int a, long long int k, int n)
{
    long long int ans = 1;
    int base = a, mod = n;
    while(k)
    {
        if(k % 2 != 0)
        {
            ans = ans * base % n;
        }
        base = base * base % n;
        k /= 2;
    }
    return temp;
}

int main()
{
    long long int n, m, x, index0 = 0;
    long long int i = 0, k;
    cin >> n >> m >> k >> x;

    long long int mod = bigMod(10, k, n);
    cout << (mod * m + x) % n << endl;
    return 0;
}
/*
index_0(k) = (index_0(k-1) + n - m)
find freq:
while(index_0(k) != 0)
++
get freqlist
mod = 10^k / freq
(freqlist[mod] + x) % n
*/