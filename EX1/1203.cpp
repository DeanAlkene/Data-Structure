#include <iostream>
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

    Node *move(int i) const;
public:
    linkList();
    ~linkList();
    void clear();
    int getLength() const;
    void traverse() const;
    void input();
    void setLength(int len);
    void append(const linkList<T> &obj);
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
int linkList<T>::getLength() const
{
    return length;
}

template<class T>
void linkList<T>::traverse() const
{
    Node *p = head->next;
    while(p)
    {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

template<class T>
void linkList<T>::input()
{
    Node *p = head, *q;
    for (int i = 0; i < length; ++i)
    {
        T tmp;
        cin >> tmp;
        q = new Node(tmp,NULL);
        p->next = q;
        p = p->next;
    }
}

template<class T>
void linkList<T>::setLength(int len)
{
    length = len;
}

/*
template<class T>
linkList<T> linkList<T>::operator+(const linkList<T> &obj)
{
    Node *p = move(length-1);
    p->next = obj.head->next;
    p =  obj.head;
    length += obj.length;
    delete p;

    return *this;
}
*/

template<class T>
void linkList<T>::append(const linkList<T> &obj)
{
    Node *p = move(length-1);
    p->next = obj.head->next;
    p =  obj.head;
    length += obj.length;
    delete p;
}

int main()
{
    char type[20];
    int len1,len2;
    cin >> type;
    cin >> len1 >> len2;
    if(strcmp(type,"int") == 0)
    {
        linkList<int> s1;
        linkList<int> s2;
        s1.setLength(len1);
        s2.setLength(len2);
        s1.input();
        s2.input();
        s1.append(s2);
        s1.traverse();
    }
    else
    {
        if(strcmp(type,"char") == 0)
        {
            linkList<char> s1;
            linkList<char> s2;
            s1.setLength(len1);
            s2.setLength(len2);
            s1.input();
            s2.input();
            s1.append(s2);
            s1.traverse();
        }
        else
        {
            linkList<double> s1;
            linkList<double> s2;
            s1.setLength(len1);
            s2.setLength(len2);
            s1.input();
            s2.input();
            s1.append(s2);
            s1.traverse();
        }
    }

    return 0;
}