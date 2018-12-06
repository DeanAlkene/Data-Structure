#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

struct Node
{
    int key;
    int num;
    Node* left;
    Node* right;
    //Node* parent;
    Node* next;
    Node(): left(NULL), right(NULL), next(NULL){}
    Node(const int &x, Node* lc = NULL, Node* rc = NULL): key(x), left(lc), right(rc), num(1){}
};

class BST
{
    private:
        Node *find(const int &x, Node* t) const;
        void insert(const int &x, Node* &t);
        void remove(const int &x, Node* &t);
        void makeEmpty(Node* t);
        int getClosest(const int &x, Node* t);
        Node *root;
    public:
        BST() {root = NULL;}
        ~BST() {makeEmpty(root);}
        Node *find(const int &x) const {return find(x, root);}
        void insert(const int &x) {insert(x, root);}
        void remove(const int &x) {remove(x, root);}
        int getClosest(const int &x) {return getClosest(x, root);}
};

Node *BST::find(const int &x, Node* t) const
{
    if(t == NULL || t->key == x)
    {
        return t;
    }
    if(x < t->key)
        return find(x, t->left);
    else
        return find(x, t->right);
}
void BST::insert(const int &x, Node* &t)
{
    if(t == NULL)
        t = new Node(x);
    else
    {
        if(x == t->key)
           ++t->num;
        else
        {
            if(x < t->key)
                insert(x, t->left);
            else
                insert(x, t->right);
        }
    }
}
void BST::remove(const int &x, Node* &t)
{
    if(t == NULL) return;
    if(x < t->key)
        remove(x, t->left);
    else
    {
        if(x > t->key)
            remove(x, t->right);
        else
        {
            if(t->num > 1)
                --t->num;
            else
            {
                if(t->left != NULL && t->right != NULL)
                {
                    Node* tmp = t->right;
                    while(tmp->left != NULL)
                        tmp = tmp->left;
                    t->key = tmp->key;
                    remove(t->key, t->right);
                }
                else
                {
                    Node* del = t;
                    t = (t->left != NULL) ? t->left : t->right;
                    delete del;
                }
            }
        }
    }
}
void BST::makeEmpty(Node* t)
{
    if(t == NULL)
        return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}
int BST::getClosest(const int &x, Node* t)
{
    if(t->key == x) return t->key;
    if(t->key < x)
    {
        if(t->right == NULL)
            return t->key;
        int r = getClosest(x, t->right);
        if(abs(t->key - x) < abs(r - x))
            return t->key;
        return r;
    }
    else
    {
        if(t->left == NULL)
            return t->key;
        int l = getClosest(x, t->left);
        if(abs(t->key - x) < abs(l - x))
            return t->key;
        return l;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    BST tree;
    int m, x, op;
    cin >> m;
    for(int i = 0; i < m; ++i)
    {
        cin >> op;
        switch(op)
        {
            case 0:
                cin >> x;
                cout << abs(x - tree.getClosest(x)) << '\n';
                break;
            case 1:
                cin >> x;
                tree.insert(x);
                break;
            case 2:
                cin >> x;
                tree.remove(x);
                break;
        }
    }
    
    cout << flush;
    return 0;
}