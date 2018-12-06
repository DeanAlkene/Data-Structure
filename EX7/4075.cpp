#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef unsigned long long ull;
const ull bit = 233;
const int MAXN = 1e6 + 7;
char A[MAXN], B[MAXN];
ull hashTable[MAXN], power[MAXN];

void getHash(char str[], int len)
{
    hashTable[0] = len;
    power[0] = 1;
    for(int i = 1; i <= len; ++i)
    {
        hashTable[i] = hashTable[i-1] * bit + str[i] + 1;
        power[i] = power[i-1] * bit;
    }
}

ull encode(int left, int right)
{
    return hashTable[right] - hashTable[left - 1] * power[right - left + 1];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int m, n;
    ull hashA, hashB;
    cin >> A;
    cin >> B;
    n = strlen(A);
    m = strlen(B);
    memmove(A+1,A,n);
    memmove(B+1,B,m);
    getHash(B, m);
    hashB = encode(1, m);
    getHash(A, n);
    for(int i = 1; i <= n - m + 1; ++i)
    {
        hashA = encode(i, i + m - 1);
        if(hashA == hashB)
        {
            cout << i-1 << '\n';
            break;
        }
    }
    cout << flush;
    return 0;
}