#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN = 1e6 + 7;
int inSeq[MAXN], outSeq[MAXN];

template<class T>
class seqStack
{
private:
    T *data;
    int top_p;
    int maxSize;
    void doubleSpace();
public:
    seqStack(int initSize = 10);
    ~seqStack();
    bool isEmpty() const;
    void push(const T &x);
    T pop();
    T top() const;
};

template<class T>
seqStack<T>::seqStack(int initSize)
{
    data = new T[initSize];
    top_p = -1;
    maxSize = initSize;
}

template<class T>
seqStack<T>::~seqStack()
{
    delete [] data;
}

template<class T>
bool seqStack<T>::isEmpty() const
{
    return top_p == -1;
}

template<class T>
void seqStack<T>::push(const T &x)
{
    if(top_p == maxSize - 1)
        doubleSpace();
    data[++top_p] = x;
}

template<class T>
T seqStack<T>::pop()
{
    return data[top_p--];
}

template<class T>
T seqStack<T>::top() const
{
    return data[top_p];
}

template <class T>
void seqStack<T>::doubleSpace()
{
    T *tmp = data;
    data = new T[2 * maxSize];
    for(int i = 0; i < maxSize; ++i)
    {
        data[i] = tmp[i];
    }
    maxSize *= 2;
    delete [] tmp;
}

bool check(int outSeq[], int n);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t, n;
    cin >> t;
    for(int i = 0; i < t; ++i)
    {
        cin >> n;
        for(int j = 0; j < n; ++j)
        {
            cin >> outSeq[j];
        }
        if(check(outSeq, n))
            cout << "Yes" << '\n';
        else
            cout << "No" << '\n';
    }
    cout << flush;
    return 0;
}

bool check(int outSeq[], int n)
{
    int i, j;
    seqStack<int> s;
    for(i = 1; i <= n; ++i)
    {
        inSeq[i] = i;
    }

    i = j = 0;
    while(j < n)
    {
        if(inSeq[i] == outSeq[j])
        {
            ++i;
            ++j;
        }
        else 
        {
            if(!s.isEmpty() && s.top() == outSeq[j])
            {
                s.pop();
                ++j;
            }
            else
            {
                if(i < n)
                {
                    s.push(inSeq[i]);
                    ++i;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return true;
}