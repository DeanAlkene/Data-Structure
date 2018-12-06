#include <iostream>
#include <cstdio>
#define MAXN 1000000
using namespace std;

struct Bracket
{
    char elem;
    bool match = false;
};

bool ifMatch(char a, char b)
{
    switch(a)
    {
    case '(':
        if(b == ')')
            return true;
        else
            return false;
    case '[':
        if(b == ']')
            return true;
        else
            return false;
    case '{':
        if(b == '}')
            return true;
        else
            return false;
    default:
        return false;
    }
}

template<class T>
class seqStack
{
private:
    T *data;
    int top_p;
    int maxSize;
    void doubleSpace();
public:
    seqStack(int initSize = 1000000);
    ~seqStack();
    bool isEmpty() const;
    void push(const T &x);
    T pop();
    T top() const;
    int getLength() {return top_p + 1;}
    void reverse()
    {
        if(data[top_p].match)
            data[top_p].match = false;
        else
            data[top_p].match = true;
    }
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
    return (top_p == -1);
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

int main()
{
    seqStack<Bracket> bracketStack, backup;
    int n, i, j = 0, op;
    char input;
    Bracket tmp;
    scanf("%d", &n);
    for(i = 0; i < n; ++i)
    {
        scanf("%d", &op);
        switch(op)
        {
        case 1:
            getchar();
            scanf("%c", &input);
            tmp.elem = input;
            tmp.match = false;
            bracketStack.push(tmp);
            if(!backup.isEmpty() && ifMatch(backup.top().elem, input))
            {
                backup.pop();
                bracketStack.reverse();
            }
            else
                backup.push(tmp);
            break;
        case 2:
            if(!bracketStack.isEmpty())
            {
                tmp = bracketStack.pop();
                if(tmp.match)
                {
                    char r;
                    Bracket in;
                    if(tmp.elem == ')')
                        r = '(';
                    else if(tmp.elem == ']')
                        r = '[';
                        else
                            r = '{';
                    in.elem = r;
                    backup.push(in);
                }
                else
                    backup.pop();
            }
            break;
        case 3:
            if(!bracketStack.isEmpty())
            {
                printf("%c", bracketStack.top());
                printf("\n");
            }
            break;
        case 4:
            if(backup.isEmpty())
            {
                printf("%s", "YES\n");
            }
            else
            {
                printf("%s", "NO\n");
            }
            break;
        }
    }
    return 0;
}