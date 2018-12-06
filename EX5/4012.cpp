#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 1e4+7;
int INF = 1e9;

struct Node
{
    int weight;
    int parent, left, right;
};


int main()
{
    Node nodeList[2 * MAXN];
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, min1, min2, l, r, total = 0;
    cin >> n;
    for(int i = n; i < 2 * n; ++i)
    {
        cin >> nodeList[i].weight;
        nodeList[i].parent = nodeList[i].left = nodeList[i].right = 0;
    }

    for(int i = n - 1; i > 0; --i)
    {
        min1 = min2 = INF;
        l = r = 0;
        for(int j = i + 1; j < 2 * n; ++j)
        {
            if(nodeList[j].parent == 0)
            {
                if(nodeList[j].weight < min1)
                {
                    min2 = min1;
                    min1 = nodeList[j].weight;
                    l = r;
                    r = j;
                }
                else
                {
                    if(nodeList[j].weight < min2)
                    {
                        min2 = nodeList[j].weight;
                        l = j;
                    }
                }
            }
        }
            nodeList[i].weight = min1 + min2;
            nodeList[i].left = l;
            nodeList[i].right = r;
            nodeList[i].parent = 0;
            nodeList[l].parent = i;
            nodeList[r].parent = i;
    }
    for(int i = 1; i < n; ++i)
    {
        total += nodeList[i].weight;
    }
    cout << total << '\n';
    cout << flush;
    return 0;
}