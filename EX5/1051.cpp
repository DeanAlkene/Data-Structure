#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

template <class T>
class linkList
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &x, Node *n = NULL)
        {
            data = x;
            next = n;
        }
        Node():next(NULL){};
        ~Node(){};
    };

    Node *head;
    int length;
    long long int cmpCount;
    Node *move(int i) const;
public:
    linkList();
    ~linkList();
    void clear();
    long long int getCnt() const;
    void insert(int i, const T &x);
    void remove(int i);
    void search(const T &x);
    void input(int len);
};

template<class T>
typename linkList<T>::Node *linkList<T>::move(int i) const
{
    Node *p = head;
    for (int j = 0; j <= i; ++j)
    {
        p = p->next;
    }

    return p;
}

template<class T>
linkList<T>::linkList()
{
    head = new Node;
    length = 0;
    cmpCount = 0;
}

template<class T>
linkList<T>::~linkList()
{
    clear();
    delete head;
}

template<class T>
void linkList<T>::clear()
{
    Node *p = head->next,*q;
    head->next = NULL;
    while(p)
    {
        q = p->next;
        delete p;
        p = q;
    }

    length = 0;
}
template<class T>
long long int linkList<T>::getCnt() const
{
    return cmpCount;
}

template<class T>
void linkList<T>::insert(int i, const T &x)
{
    Node *p = move(i-1);
    Node *cur_p = new Node(x,p->next);
    p->next = cur_p;
    
    length++;
}

template<class T>
void linkList<T>::remove(int i)
{
    Node *p = move(i-1);
    Node *del_p = p->next;
    p->next = del_p->next;
    delete del_p;

    length--;
}

template<class T>
void linkList<T>::search(const T &x)
{
    int i = 0;
    Node *p = head->next;
    while(p)
    {
        if(p->data == x) 
        {
            insert(0, x);
            remove(i + 1);
            ++cmpCount;
            break;
        }
        else
        {
            p = p->next;
            ++i;
            ++cmpCount;
        }
    }
}

template<class T>
void linkList<T>::input(int len)
{
    Node *p = head, *q;
    length = len;
    for (int i = 0; i < length; ++i)
    {
        T tmp;
        cin >> tmp;
        q = new Node(tmp,NULL);
        p->next = q;
        p = p->next;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    linkList<int> s;
    int n, m, x;
    cin >> n;
    s.input(n);
    cin >> m;
    for(int i = 0; i < m; ++i)
    {
        cin >> x;
        s.search(x);
    }
    cout << s.getCnt() << '\n';
    cout << flush;
    return 0;
}