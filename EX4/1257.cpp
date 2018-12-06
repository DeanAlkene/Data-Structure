#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 1e6 + 7;

template<class T>
class binaryTree
{
    private:
        struct Node
        {
            T elem;
            Node *left;
            Node *right;
            Node *prev;
            Node():left(NULL), right(NULL), prev(NULL) {}
            Node(const T &x, Node *lc = NULL, Node *rc = NULL, Node *pf = NULL)
            {
                elem = x;
                left = lc;
                right = rc;
                prev = pf;
            }
            ~Node() {}
        };
        Node *root;
        Node **checkList;
        void preOrder(Node *&t) const;
        void clear(Node *&t);
    public:
        binaryTree()
        {
            root = new Node(1); 
            checkList = new Node*[MAXN]; 
            memset(checkList, 0, sizeof(Node*) * MAXN);
            checkList[1] = root;
        }
        binaryTree(T x) {root = new Node(x);}
        ~binaryTree() {clear(root); delete [] checkList;}
        void preOrder() {preOrder(root);}
        Node *find(T x);
        void add(T a, T b, T c);
        void ask(T a);
        void exchange(T a);
        bool check(T a, T b, T c);
};
 
template<class T>
void binaryTree<T>::preOrder(binaryTree<T>::Node *&t) const
{
    if(t == NULL) return;
    cout << t->elem << ' ';
    preOrder(t->left);
    preOrder(t->right);
}
template<class T>
typename binaryTree<T>::Node *binaryTree<T>::find(T x)
{
    return checkList[x];
}
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
void binaryTree<T>::add(T a, T b, T c)
{
    Node *tmp, *lc, *rc;
    if(check(a, b, c))
    {
        tmp = find(a);
        lc = new Node(b, NULL, NULL, tmp);
        rc = new Node(c, NULL, NULL, tmp);
        tmp->left = lc;
        tmp->right = rc;
        checkList[b] = lc;
        checkList[c] = rc;
        cout << "Ok!\n";
    }
    else
        cout << "Error!\n";
}
template<class T>
void binaryTree<T>::ask(T a)
{
    Node *tmp;
    tmp = find(a);
    if(tmp != NULL)
    {
        if(tmp->prev != NULL)
            cout << tmp->prev->elem << ' ';
        else
            cout << 0 << ' ';
        if(tmp->left != NULL)
            cout << tmp->left->elem << ' ';
        else
            cout << 0 << ' ';
        if(tmp->right != NULL)
            cout << tmp->right->elem << '\n';
        else
            cout << 0 << '\n';
    }
    else
        cout << "Error!\n";
}
template<class T>
void binaryTree<T>::exchange(T a)
{
    Node *cur = find(a);
    Node *tmp;
    T left_elem, right_elem;
    if(cur != NULL && a != 1)
    {
        cur = cur->prev;

        if(cur->left != NULL)
            left_elem = cur->left->elem;
        else
            left_elem = 0;
        if(cur->right != NULL)
            right_elem = cur->right->elem;
        else
            right_elem = 0;
            
        if(left_elem == a)
            cout << right_elem << '\n';
        else
            cout << left_elem << '\n';
 
        tmp = cur->left;
        cur->left = cur->right;
        cur->right = tmp;
        if(left_elem != 0) //BUG AT HERE!
            checkList[right_elem] = cur->left;
        if(right_elem != 0)
            checkList[left_elem] = cur->right;
    }
    else
        cout << "Error!\n";
}
 
template<class T>
bool binaryTree<T>::check(T a, T b, T c)
{
    Node *tmp;
    tmp = find(a);
    if(tmp == NULL)
        return false;
    if(tmp->left != NULL || tmp->right != NULL)
        return false;
    tmp = find(b);
    if(tmp != NULL)
        return false;
    tmp = find(c);
    if(tmp != NULL)
        return false;
    if(b == c)
        return false;
    return true;
}
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    binaryTree<int> bt;
    int m;
    int op, a, b, c;
    cin >> m;
    for(int i = 0; i < m; ++i)
    {
        cin >> op;
        switch(op)
        {
            case 1:
                cin >> a >> b >> c;
                bt.add(a, b, c);
                break;
            case 2:
                cin >> a;
                bt.ask(a);
                break;
            case 3:
                cin >> a;
                bt.exchange(a);
                break;
        }
    }
    bt.preOrder();
    cout << '\n';
    cout << flush;
    return 0;
}