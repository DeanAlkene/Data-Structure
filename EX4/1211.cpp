#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
const int MAXN = 1e6 + 7;
bool checkList[MAXN] = {false};

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

template <class T>
class binaryTree
{
    private:
        struct Node
        {
            T elem;
            Node *left;
            Node *right;
            int leftIndex;
            int rightIndex;
            Node():left(NULL), right(NULL), leftIndex(0), rightIndex(0) {}
            Node(const T &x, Node *lc = NULL, Node *rc = NULL, int li = 0, int ri = 0)
            {
                elem = x;
                left = lc;
                right = rc;
                leftIndex = li;
                rightIndex = ri;
            }
            ~Node() {}
        };

        Node *root;
        void clear(Node *&t);
    public:
        binaryTree():root(NULL) {}
        binaryTree(T x) {root = new Node(x);}
        ~binaryTree() {clear(root);}
        void clear() {clear(root);}
        bool isEmpty() const {return root == NULL;}
        void createTree();
        bool isCBT();
};

template<class T>
void binaryTree<T>::clear(binaryTree<T>::Node *&t)
{
    if(t == NULL) return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = NULL;
}
template<class T>
void binaryTree<T>::createTree()
{
    Node** nodeList;
    nodeList = new Node*[MAXN];
    int i, n, leftI, rightI;
    cin >> n;
    for(i = 1; i <= n; ++i)
    {
        cin >> leftI >> rightI;
        nodeList[i] = new Node;
        nodeList[i]->leftIndex = leftI;
        nodeList[i]->rightIndex = rightI;
        checkList[leftI] = true;
        checkList[rightI] = true;
    }
    for(i = 1; i <= n; ++i)
    {
        if(nodeList[i]->leftIndex != 0)
            nodeList[i]->left = nodeList[nodeList[i]->leftIndex];
        if(nodeList[i]->rightIndex != 0)
            nodeList[i]->right = nodeList[nodeList[i]->rightIndex];
    }
    for(i = 1; i <= n; ++i)
    {
        if(!checkList[i])
            break;
    }
    root = nodeList[i];
    delete [] nodeList;
}
template<class T>
bool binaryTree<T>::isCBT()
{
    seqQueue<Node*> que;
    Node *cur_p, *chi_p;
    int count = 1, last = 1;

    if(root == NULL) return true;
    cur_p = root;
    cur_p->elem = 1;
    que.enQueue(cur_p);
    while(!que.isEmpty())
    {
        cur_p = que.deQueue();
        if(cur_p->left != NULL)
        {
            ++count;
            chi_p = cur_p->left;
            last = chi_p->elem = cur_p->elem * 2;
            que.enQueue(chi_p);
        }
        if(cur_p->right != NULL)
        {
            ++count;
            chi_p = cur_p->right;
            last = chi_p->elem = cur_p->elem * 2 + 1;
            que.enQueue(chi_p);
        }
    }
    return count == last;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    binaryTree<int> bt;
    bt.createTree();
    if(bt.isCBT())
        cout << "Y\n";
    else
        cout << "N\n";
    cout << flush;
    return 0;
}