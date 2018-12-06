#include <iostream>
#define MAXN 1000
using namespace std;

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
    int getLength();
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

template <class T>
int seqStack<T>::getLength()
{
    return top_p + 1;
}

bool ifDispatch(int outSeq[], int m, int n);

int main()
{
    int t, m, n, outSeq[MAXN];
    cin >> t;
    for(int i = 0; i < t; ++i)
    {
        cin >> n >> m;
        for(int j = 0; j < n; ++j)
        {
            cin >> outSeq[j];
        }
        if(ifDispatch(outSeq, m, n))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}

bool ifDispatch(int outSeq[], int m, int n)
{
    int inSeq[MAXN], i, j;
    seqStack<int> station;
    for(i = 0; i < n; ++i)
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
            if(!station.isEmpty() && station.top() == outSeq[j])
            {
                station.pop();
                ++j;
            }
            else
            {
                if(station.getLength() < m && i < n)
                {
                    station.push(inSeq[i]);
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