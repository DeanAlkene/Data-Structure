#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 1e6 + 7;
char tree[MAXN], input[MAXN], result[MAXN];
char op1[10], op2[10];
int n, ind;

void preOrder(int t)
{
    if(t > n) return;
    cout << tree[t];
    preOrder(2 * t);
    preOrder(2 * t + 1);
}
void inOrder(int t)
{
    if(t > n) return;
    inOrder(2 * t);
    cout << tree[t];
    inOrder(2 * t + 1);
}
void postOrder(int t)
{
    if(t > n) return;
    postOrder(2 * t);
    postOrder(2 * t + 1);
    cout << tree[t];
}
void decodePre(int t, int &index)
{
    if(t > n) return;
    result[t] = tree[index++];
    decodePre(2 * t, index);
    decodePre(2 * t + 1, index); 
}
void decodeIn(int t, int &index)
{
    if(t > n) return;
    decodeIn(2 * t, index);
    result[t] = tree[index++];
    decodeIn(2 * t + 1, index);
}
void decodePost(int t, int &index)
{
    if(t > n) return;
    decodePost(2 * t, index);
    decodePost(2 * t + 1, index);
    result[t] = tree[index++];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i)
    {
        tree[0] = '#';
        tree[1] = '\0';
        cin >> n >> op1 >> op2;
        cin >> input;
        strcat(tree, input);
        if(op1[0] == 'I')
        {
            if(op2[0] == 'E')
            {
                inOrder(1);
                cout << '\n';
            }
            else
            {
                ind = 1;
                decodeIn(1, ind);
                for(int j = 1; j <= n; ++j)
                {
                    cout << result[j];
                }
                cout << '\n';
            }
        }
        if(op1[0] == 'P' && op1[1] == 'O')
        {
            if(op2[0] == 'E')
            {
                postOrder(1);
                cout << '\n';
            }
            else
            {
                ind = 1;
                decodePost(1, ind);
                for(int j = 1; j <= n; ++j)
                {
                    cout << result[j];
                }
                cout << '\n';
            }
        }
        if(op1[0] == 'P' && op1[1] == 'R')
        {
            if(op2[0] == 'E')
            {
                preOrder(1);
                cout << '\n';
            }
            else
            {
                ind = 1;
                decodePre(1, ind);
                for(int j = 1; j <= n; ++j)
                {
                    cout << result[j];
                }
                cout << '\n';
            }
        }
    }
    cout << flush;
    return 0;
}