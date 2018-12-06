#include <iostream>
#include <cstring>
#define MAXN 1001
using namespace std;

class seqStack
{
private:
    char **data;
    int top_p;
    int maxSize;
    void doubleSpace();
public:
    seqStack(int initSize = 10);
    ~seqStack();
    bool isEmpty() const;
    void push(char* x);
    char *pop();
    char *top() const;
};

seqStack::seqStack(int initSize)
{
    data = new char*[initSize];
    top_p = -1;
    maxSize = initSize;
}

seqStack::~seqStack()
{
    for(int i = 0; i < top_p + 1; ++i)
    {
        delete [] data[i];
    }
    delete [] data;
}

bool seqStack::isEmpty() const
{
    return top_p == -1;
}

void seqStack::push(char* x)
{
    if(top_p == maxSize - 1)
        doubleSpace();
    data[++top_p] = x;
}

char *seqStack::pop()
{
    return data[top_p--];
}

char *seqStack::top() const
{
    return data[top_p];
}

void seqStack::doubleSpace()
{
    char **tmp = data;
    data = new char*[2 * maxSize];
    for(int i = 0; i < maxSize; ++i)
    {
        data[i] = tmp[i];
    }
    maxSize *= 2;
    delete [] tmp;
}

int main()
{
    bool flag = true, flag_in = false, flag_if = false;
    char tmp[MAXN];
    char *s;
    seqStack stringStack;

    while(cin >> tmp)
    {
        s = new char[MAXN];
        strcpy(s, tmp);
        if(strcmp(s, "begin") == 0)
        {
            flag_in = true;
            stringStack.push(s);
        }
        else
        {
            if(strcmp(s, "end") == 0)
            {
                flag_in = true;
                if(!stringStack.isEmpty() && strcmp(stringStack.top(), "begin") == 0)
                {
                    stringStack.pop();
                }
                else
                {
                    flag = false;
                }
            }
            else
            {
                if(strcmp(s, "if") == 0)
                {
                    flag_in = true;
                    stringStack.push(s);
                }
                else
                {
                    if(strcmp(s, "then") == 0)
                    {
                        if(strcmp(stringStack.top(), "if") == 0)
                        {
                            flag_in = true;
                            stringStack.pop();
                            flag_if = true;
                        }
                        else
                            flag = false;
                    }
                    else
                    {
                        if(strcmp(s, "else") == 0)
                        {
                            flag_in = true;
                            if(!flag_if)
                               flag = false;
                            //flag_if = false;
                        }
                    }
                }
            }
        }
    }

    if(flag && stringStack.isEmpty() && flag_in)
        cout << "Match!" << endl;
    else
        cout << "Error!" << endl;
    return 0;
}