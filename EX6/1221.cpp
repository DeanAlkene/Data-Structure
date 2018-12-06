#include <iostream>
#include <cstring>
#include <cstdio>
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
        Node *find_ith(const int &i, Node* t);
        void insert(const int &x, Node* &t);
        void remove(const int &x, Node* &t);
        void removeLessThan(const int &x, Node* &t);
        void removeGreaterThan(const int &x, Node* &t);
        void removeInterval(const int &a, const int &b, Node* &t);
        void makeEmpty(Node* t);
        int size(Node* t);
        Node *root;
    public:
        BST() {root = NULL;}
        ~BST() {makeEmpty(root);}
        Node *find(const int &x) const {return find(x, root);}
        Node *find_ith(const int &i) {return find_ith(i, root);}
        void insert(const int &x) {insert(x, root);}
        void remove(const int &x) {remove(x, root);}
        void removeLessThan(const int &x) {removeLessThan(x, root);}
        void removeGreaterThan(const int &x) {removeGreaterThan(x, root);}
        void removeInterval(const int &a, const int &b) {removeInterval(a, b, root);}
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
Node *BST::find_ith(const int &i, Node* t)
{
    if(t == NULL)
        return NULL;
    int tmp = size(t->left);
    if(i <= tmp)
        return find_ith(i, t->left);
    else
    {
        if(i > tmp + t->num)
            return find_ith(i - tmp - t->num, t->right);
        else
        {
            if(i > tmp && i <= tmp + t->num)
                return t;
        }
    }
}
void BST::removeLessThan(const int &x, Node* &t)
{
    if(t == NULL)
        return;
    if(x > t->key)
    {
        Node* tmp = t;
        t = t->right;
        makeEmpty(tmp->left);
        delete tmp;
        removeLessThan(x, t);
    }
    else
        removeLessThan(x, t->left);
}
void BST::removeGreaterThan(const int &x, Node* &t)
{
    if(t == NULL)
        return;
    if(x < t->key)
    {
        Node* tmp = t;
        t = t->left;
        makeEmpty(tmp->right);
        delete tmp;
        removeGreaterThan(x, t);
    }
    else
        removeGreaterThan(x, t->right);
}
void BST::removeInterval(const int &a, const int &b, Node* &t)
{
    if(t == NULL)
        return;
    if(a >= t->key)
        removeInterval(a, b, t->right);
    else
    {
        if(b <= t->key)
            removeInterval(a, b, t->left);
        else
        {
            remove(t->key, t);
            removeInterval(a, b, t);
        }
    }
}
int BST::size(Node *t)
{
    if(t == NULL)
        return 0;
    return size(t->left) + size(t->right) + t->num;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, x, a, b;
    Node *result;
    char oprand[30], flag;
    BST tree;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        cin >> oprand;
        flag = oprand[0];
        switch(flag)
        {
            case 'i':
                cin >> x;
                tree.insert(x);
                break;
            case 'd':
                if(strlen(oprand) <= 6)
                {
                    cin >> x;
                    tree.remove(x);
                }
                else
                {
                    if(oprand[7] == 'l')
                    {
                        cin >> x;
                        tree.removeLessThan(x);
                    }
                    else
                    {
                        if(oprand[7] == 'g')
                        {
                            cin >> x;
                            tree.removeGreaterThan(x);
                        }
                        else
                        {
                            cin >> a >> b;
                            tree.removeInterval(a, b);
                        }
                    }
                }
                break;
            case 'f':
                if(strlen(oprand) <= 4)
                {
                    cin >> x;
                    result = tree.find(x);
                    if(result != NULL)
                        cout << 'Y' << '\n';
                    else
                        cout << 'N' << '\n';
                }
                else
                {
                    cin >> x;
                    result = tree.find_ith(x);
                    if(result != NULL)
                        cout << result->key << '\n';
                    else
                        cout << 'N' << '\n';
                }
                break;
        }
    }
    cout << flush;
    return 0;
}
