#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 5e5 + 7;
struct Node
{
    int key;
    int num;
    Node *left;
    Node *right;
    Node *next;
    Node() : left(NULL), right(NULL), next(NULL) {}
    Node(const int &x, Node *lc = NULL, Node *rc = NULL) : key(x), left(lc), right(rc), num(1) {}
};

class BST
{
  private:
    Node *find(const int &x, Node *t) const;
    Node *find_ith(const int &i, Node *t);
    void insert(const int &x, Node *&t);
    void remove(const int &x, Node *&t);
    void makeEmpty(Node *t);
    int size(Node *t);
    Node *root;

  public:
    BST() { root = NULL; }
    ~BST() { makeEmpty(root); }
    Node *find(const int &x) const { return find(x, root); }
    Node *find_ith(const int &i) { return find_ith(i, root); }
    void insert(const int &x) { insert(x, root); }
    void remove(const int &x) { remove(x, root); }
};

Node *BST::find(const int &x, Node *t) const
{
    if (t == NULL || t->key == x)
    {
        return t;
    }
    if (x < t->key)
        return find(x, t->left);
    else
        return find(x, t->right);
}
void BST::insert(const int &x, Node *&t)
{
    if (t == NULL)
        t = new Node(x);
    else
    {
        if (x == t->key)
            ++t->num;
        else
        {
            if (x < t->key)
                insert(x, t->left);
            else
                insert(x, t->right);
        }
    }
}
void BST::remove(const int &x, Node *&t)
{
    if (t == NULL)
        return;
    if (x < t->key)
        remove(x, t->left);
    else
    {
        if (x > t->key)
            remove(x, t->right);
        else
        {
            if (t->num > 1)
                --t->num;
            else
            {
                if (t->left != NULL && t->right != NULL)
                {
                    Node *tmp = t->right;
                    while (tmp->left != NULL)
                        tmp = tmp->left;
                    t->key = tmp->key;
                    remove(t->key, t->right);
                }
                else
                {
                    Node *del = t;
                    t = (t->left != NULL) ? t->left : t->right;
                    delete del;
                }
            }
        }
    }
}
void BST::makeEmpty(Node *t)
{
    if (t == NULL)
        return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}
Node *BST::find_ith(const int &i, Node *t)
{
    if (t == NULL)
        return NULL;
    int tmp = size(t->left);
    if (i <= tmp)
        return find_ith(i, t->left);
    else
    {
        if (i > tmp + t->num)
            return find_ith(i - tmp - t->num, t->right);
        else
        {
            if (i > tmp && i <= tmp + t->num)
                return t;
        }
    }
}
int BST::size(Node *t)
{
    if (t == NULL)
        return 0;
    return size(t->left) + size(t->right) + t->num;
}

BST tree;

struct Suger
{
    int idx = -1;
    bool eaten = false;
};
class DisjointSet
{
  private:
    int sz;
    int box;
    Suger *parent;

  public:
    DisjointSet(int n);
    ~DisjointSet() { delete[] parent; }
    void Union(int root1, int root2);
    int Find(int x);
    void Eat(int x);
    int getBox() { return box; }
};
DisjointSet::DisjointSet(int n)
{
    sz = n;
    box = n;
    parent = new Suger[sz + 1];
    for (int i = 0; i < n; ++i)
        tree.insert(1);
}
void DisjointSet::Union(int root1, int root2)
{
    if (parent[root1].eaten || parent[root2].eaten)
        return;
    if (root1 == root2)
        return;
    tree.remove(-parent[root1].idx);
    tree.remove(-parent[root2].idx);
    if (parent[root1].idx > parent[root2].idx)
    {
        parent[root2].idx += parent[root1].idx;
        parent[root1].idx = root2;
        tree.insert(-parent[root2].idx);
    }
    else
    {
        parent[root1].idx += parent[root2].idx;
        parent[root2].idx = root1;
        tree.insert(-parent[root1].idx);
    }
    box--;
}

int DisjointSet::Find(int x)
{
    if (parent[x].idx < 0)
        return x;
    return parent[x].idx = Find(parent[x].idx);
}

void DisjointSet::Eat(int x)
{
    int index = Find(x);
    if (parent[index].eaten)
        return;
    parent[index].eaten = true;
    tree.remove(-parent[index].idx);
    sz += parent[index].idx;
    box--;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, x, y, p;
    char op;
    cin >> n >> m;
    DisjointSet s(n);
    for (int i = 0; i < m; ++i)
    {
        cin >> op;
        switch (op)
        {
        case 'C':
            cin >> x >> y;
            s.Union(s.Find(x), s.Find(y));
            break;
        case 'D':
            cin >> x;
            s.Eat(x);
            break;
        case 'Q':
            cin >> p;
            cout << tree.find_ith(s.getBox() - p + 1)->key << '\n';
            break;
        }
    }
    cout << flush;
    return 0;
}
