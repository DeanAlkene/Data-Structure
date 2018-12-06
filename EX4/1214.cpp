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
            Node *child;
            Node *brother;
            int childIndex;
            int brotherIndex;
            Node():child(NULL), brother(NULL), childIndex(0), brotherIndex(0) {}
            Node(const T &x, Node *ch = NULL, Node *br = NULL, int ci = 0, int bi = 0)
            {
                elem = x;
                child = ch;
                brother = br;
                childIndex = ci;
                brotherIndex = bi;
            }
            ~Node() {}
        };

        Node *root;
        void clear(Node *&t);
        void preOrder(Node *&t) const;
        void postOrder(Node *&t) const;
    public:
        binaryTree():root(NULL) {}
        binaryTree(T x) {root = new Node(x);}
        ~binaryTree() {clear(root);}
        void clear() {clear(root);}
        bool isEmpty() const {return root == NULL;}
        void createTree();
        void preOrder() {preOrder(root);}
        void postOrder() {postOrder(root);}
        void levelOrder();
};

template<class T>
void binaryTree<T>::clear(binaryTree<T>::Node *&t)
{
    if(t == NULL) return;
    clear(t->child);
    clear(t->brother);
    delete t;
    t = NULL;
}
template<class T>
void binaryTree<T>::createTree()
{
    Node** nodeList;
    nodeList = new Node*[MAXN];
    int i, n, childI, brotherI, value;
    cin >> n;
    for(i = 1; i <= n; ++i)
    {
        cin >> childI >> brotherI >> value;
        nodeList[i] = new Node;
        nodeList[i]->childIndex = childI;
        nodeList[i]->brotherIndex = brotherI;
        nodeList[i]->elem = value;
        checkList[childI] = true;
        checkList[brotherI] = true;
    }
    for(i = 1; i <= n; ++i)
    {
        if(nodeList[i]->childIndex != 0)
            nodeList[i]->child = nodeList[nodeList[i]->childIndex];
        if(nodeList[i]->brotherIndex != 0)
            nodeList[i]->brother = nodeList[nodeList[i]->brotherIndex];
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
void binaryTree<T>::preOrder(Node *&t) const
{
    if(t == NULL) return;
    cout << t->elem << ' ';
    preOrder(t->child);
    preOrder(t->brother);
}

template<class T>
void binaryTree<T>::postOrder(Node *&t) const
{
    if(t == NULL) return;
    postOrder(t->child);
    cout << t->elem << ' ';
    postOrder(t->brother);
}

template<class T>
void binaryTree<T>::levelOrder()
{
    seqQueue<Node*> que;
    Node *cur_p;
    if(root == NULL) return;
    que.enQueue(root);
    cout << root->elem << ' ';
    while(!que.isEmpty())
    {
        cur_p = que.deQueue();
        
        if(cur_p->child != NULL)
        {
            cur_p = cur_p->child;
            cout << cur_p->elem << ' ';
            que.enQueue(cur_p);

            while(cur_p->brother != NULL)
            {
                cur_p = cur_p->brother;
                cout << cur_p->elem << ' ';
                que.enQueue(cur_p);
            }
        }
    }
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    binaryTree<int> bt;
    bt.createTree();
    bt.preOrder();
    cout << '\n';
    bt.postOrder();
    cout << '\n';
    bt.levelOrder();
    cout << flush;
    return 0;
}