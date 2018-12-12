#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 2007;
char seq[MAXN], opStack[MAXN];
int numStack[MAXN], result[MAXN];
int n, top_op, top_num, top_res;

int level(char op)
{
    int level;
    switch (op)
    {
    case '+':
    case '-':
        level = 1;
        break;
    case '*':
    case '/':
        level = 2;
        break;
    default:
        level = 0;
        break;
    }
    return level;
}

bool isOperator(char op)
{
    if (op == '+' || op == '-' || op == '*' || op == '/')
        return true;
    return false;
}

void show()
{
    int i, tmp, ans = 0;
    top_op = top_res = -1;
    i = n - 1;
    while (i >= 0)
    {
        while (i >= 0 && seq[i] == ' ')
            i--;
        if (seq[i] >= '0' && seq[i] <= '9')
        {
            tmp = 0;
            int j;
            while (seq[i] >= '0' && seq[i] <= '9')
                i--;
            j = i + 1;
            while (seq[j] >= '0' && seq[j] <= '9')
            {
                tmp = tmp * 10 + seq[j] - '0';
                ++j;
            }
            result[++top_res] = -tmp;
        }
        if (seq[i] == ')')
        {
            opStack[++top_op] = seq[i];
        }
        while (isOperator(seq[i]))
        {
            if (top_op == -1 || opStack[top_op] == ')' || level(seq[i]) >= level(opStack[top_op]))
            {
                opStack[++top_op] = seq[i];
                break;
            }
            else
            {
                result[++top_res] = opStack[top_op--];
            }
        }
        if (seq[i] == '(')
        {
            while (top_op != -1 && opStack[top_op] != ')')
            {
                result[++top_res] = opStack[top_op--];
            }
            top_op--;
        }
        i--;
    }
    while (top_op != -1)
    {
        result[++top_res] = opStack[top_op--];
    }
    n = top_res;
    if (top_res != -1)
    {
        int out = result[top_res--];
        if (out > 0)
            cout << (char)out;
        else
            cout << -out;
    }
    while (top_res != -1)
    {
        int out = result[top_res--];
        if (out > 0)
            cout << ' ' << (char)out;
        else
            cout << ' ' << -out;
    }
    cout << '\n';
}

int calc()
{
    top_num = -1;
    int num1, num2, i, ans;
    char op;
    i = 0;
    while (i <= n)
    {
        if (result[i] > 0)
        {
            op = (char)result[i];
            num1 = numStack[top_num--];
            num2 = numStack[top_num--];
            if (op == '+')
                numStack[++top_num] = num1 + num2;
            if (op == '-')
                numStack[++top_num] = num1 - num2;
            if (op == '*')
                numStack[++top_num] = num1 * num2;
            if (op == '/')
                numStack[++top_num] = num1 / num2;
        }
        else
        {
            numStack[++top_num] = -result[i];
        }
        i++;
    }
    ans = numStack[top_num--];
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin.getline(seq, MAXN, '\n');
    n = strlen(seq);
    show();
    int ans = calc();
    cout << ans << '\n';

    cout << flush;
    return 0;
}
