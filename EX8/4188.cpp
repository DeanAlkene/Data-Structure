#include <iostream>
#include <cstring>
#include <cstdio>
typedef unsigned long long ULL;
using namespace std;
const int MAXN = 1e5 + 7;
const ULL SEED = 233;
inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }
std::string list[MAXN];
ULL power[MAXN];
ULL *hashTable[MAXN], hashTotal[MAXN];
ULL code(ULL *h, int left, int right)
{
    return h[right] - h[left - 1] * power[right - left + 1];
}

void init(int n)
{
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        power[i] = power[i - 1] * SEED;
    }
}

ULL getHash(ULL *h, string &s, int n)
{
    h[0] = 0;
    for (int i = 0; i < n; ++i)
    {
        h[i + 1] = h[i] * SEED + s[i] + 1;
    }
    return h[n];
}

bool check0(int len, ULL *hash1, ULL *hash2)
{
    return code(hash1, 1, len) == code(hash2, 1, len);
}
bool check1(int len, int len1, int len2, ULL *hash1, ULL *hash2)
{
    return code(hash1, len1 - len + 1, len1) == code(hash2, len2 - len + 1, len2);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int m, n, op, x, y, l, r, mid, len, len1, len2;
    bool flag = false;
    cin >> n;
    init(MAXN);
    for (int i = 0; i < n; ++i)
    {
        cin >> list[i];
        len = list[i].size();
        hashTable[i] = new ULL[len + 5];
        hashTotal[i] = getHash(hashTable[i], list[i], list[i].size());
    }
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> x;
            flag = false;
            for (int j = 0; j < x - 1; ++j)
            {
                if (hashTotal[j] == hashTotal[x - 1])
                {
                    cout << "yes" << '\n';
                    flag = true;
                    break;
                }
            }
            if (!flag)
                cout << "no" << '\n';
            break;
        case 2:
            cin >> x >> y;
            len1 = list[x - 1].size();
            len2 = list[y - 1].size();
            l = 0;
            r = max(len1, len2);
            while (l < r)
            {
                mid = (l + r) / 2;
                if (check0(mid + 1, hashTable[x - 1], hashTable[y - 1]))
                    l = mid + 1;
                else
                    r = mid;
            }
            cout << r << '\n';
            break;
        case 3:
            cin >> x >> y;
            len1 = list[x - 1].size();
            len2 = list[y - 1].size();
            l = 0;
            r = max(len1, len2);
            while (l < r)
            {
                mid = (l + r) / 2;
                if (check1(mid + 1, len1, len2, hashTable[x - 1], hashTable[y - 1]))
                    l = mid + 1;
                else
                    r = mid;
            }
            cout << r << '\n';
            break;
        }
    }
    cout << flush;
    return 0;
}