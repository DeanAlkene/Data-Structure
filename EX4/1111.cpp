#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 1007;
char pre[30], mid[30], output[MAXN];

struct Node
{
    char elem;
    int index;
    Node *left;
    Node *right;
    Node():left(NULL), right(NULL), index(0) {}
    Node(const char &x, Node *lc = NULL, Node *rc = NULL, int i = 0)
    {
        elem = x;
        left = lc;
        right = rc;
        index = i;
    }
    ~Node() {}
};

template <class T>
class seqQueue
{
    private:
        T *data;
        int maxSize;
        int front, rear;
        void doubleSpace();
    public:
        seqQueue(int size = 1000007);
        ~seqQueue();
        bool isEmpty() const;
        void enQueue(const T &x);
        T deQueue();
        T getHead() const;
};

template <class T>
void seqQueue<T>::doubleSpace()
{
    T* tmp = data;
    data = new T[2 * maxSize];
    for(int i = 1; i < maxSize; ++i)
    {
        data[i] = tmp[(front + i) % maxSize];
    }
    front = 0;
    rear = maxSize - 1;
    maxSize *= 2;
    delete tmp;
}

template <class T>
seqQueue<T>::seqQueue(int size)
{
    data = new T[size];
    maxSize = size;
    front = rear = 0;
}

template <class T>
seqQueue<T>::~seqQueue()
{
    delete [] data;
}

template <class T>
bool seqQueue<T>::isEmpty() const
{
    return front == rear;
}

template <class T>
void seqQueue<T>::enQueue(const T &x)
{
    if((rear + 1) % maxSize == front)
        doubleSpace();
    rear = (rear + 1) % maxSize;
    data[rear] = x;
}

template <class T>
T seqQueue<T>::deQueue()
{
    front = (front + 1) % maxSize;
    return data[front];
}

template <class T>
T seqQueue<T>::getHead() const
{
    return data[(front + 1) % maxSize];
}

Node* createTree(const char* pre, const char* mid, int len)
{
    if(len == 0) return NULL;
    Node *root = new Node(*pre);
    int rootIndex = 0;
    while(*pre != mid[rootIndex])
    {
        rootIndex++;
    }
    root->left = createTree(pre + 1, mid, rootIndex);
    root->right = createTree(pre + rootIndex + 1, mid + rootIndex + 1, len - rootIndex -1);
    return root;
}

void levelOrder(Node *r)
{
    seqQueue<Node*> q;
    memset(output, 0, sizeof(output));
    int n = 1;
    Node *tmp;
    r->index = 1;
    q.enQueue(r);
    while(!q.isEmpty())
    {
        tmp = q.deQueue();
        output[tmp->index] = tmp->elem;
        if(tmp->left)
        {
            n = tmp->left->index = 2 * tmp->index;
            q.enQueue(tmp->left);
        }
        if(tmp->right)
        {
            n = tmp->right->index = 2 * tmp->index + 1;
            q.enQueue(tmp->right);
        }
    }
    
    for(int i = 1; i <= n; ++i)
    {
        if(output[i] == '\0')
            cout << "NULL" << ' ';
        else
            cout << output[i] << ' ';
    }
    cout << '\n';  
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> pre;
    cin >> mid;

    Node *root = createTree(pre, mid, strlen(pre));
    levelOrder(root);
    cout << flush;
    return 0;
}