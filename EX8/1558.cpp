#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e5 + 7;
int lb[MAXN], cowNum[MAXN];
inline int max(int a, int b) { return a > b ? a : b; }
struct Node
{
    int label;
    int index;
    Node(int a = 0, int b = 0) : label(a), index(b) {}
    friend bool operator>(const Node &a, const Node &b) { return a.label > b.label; }
    friend bool operator<(const Node &a, const Node &b) { return a.label < b.label; }
    friend bool operator>=(const Node &a, const Node &b) { return a.label >= b.label; }
    friend bool operator<=(const Node &a, const Node &b) { return a.label <= b.label; }
};
Node cow[MAXN];
bool numOp(const Node &a, const Node &b) { return a.index > b.index; }
class Heap
{
  private:
    Node *array;
    int sz;
    int maxSize;

  public:
    Heap(int initSize = 101)
    {
        array = new Node[initSize];
        sz = 0;
        maxSize = initSize;
    }
    Node deQueue()
    {
        Node tmp = array[1];
        array[1] = array[sz--];
        precolateDown(1);
        return tmp;
    }
    void enQueue(Node x)
    {
        if (sz == maxSize - 1)
            doubleSpace();
        int hole = ++sz;
        for (; hole > 1 && numOp(x, array[hole / 2]); hole /= 2)
        {
            array[hole] = array[hole / 2];
        }
        array[hole] = x;
    }
    int getSize()
    {
        return sz;
    }
    void precolateDown(int hole)
    {
        int child;
        Node tmp = array[hole];
        for (; 2 * hole <= sz; hole = child)
        {
            child = 2 * hole;
            if (child != sz && numOp(array[child + 1], array[child]))
                child++;
            if (numOp(array[child], tmp))
                array[hole] = array[child];
            else
                break;
        }
        array[hole] = tmp;
    }
    Node getHead()
    {
        return array[1];
    }
    bool isEmpty()
    {
        return sz == 0;
    }
    void doubleSpace()
    {
        Node *tmp = array;
        maxSize *= 2;
        array = new Node[maxSize];
        for (int i = 1; i <= sz; ++i)
        {
            array[i] = tmp[i];
        }
        delete[] tmp;
    }
};

int divide(Node s[], int low, int high)
{
    Node k = s[low];
    do
    {
        while (low < high && s[high] >= k)
            --high;
        if (low < high)
        {
            s[low] = s[high];
            ++low;
        }
        while (low < high && s[low] <= k)
            ++low;
        if (low < high)
        {
            s[high] = s[low];
            --high;
        }
    } while (low != high);
    s[low] = k;
    return low;
}

void quickSort(Node s[], int low, int high)
{
    int mid;
    if (low >= high)
        return;
    mid = divide(s, low, high);
    quickSort(s, low, mid);
    quickSort(s, mid + 1, high);
}

int longestSeq(Heap &h, int n, int k)
{
    int cur, ans;
    cur = ans = cowNum[lb[1]] = 1;
    h.enQueue(Node(lb[1], cowNum[lb[1]]));
    for (int i = 1, j = 1; i <= n && j <= n;)
    {
        while (j < n && cur < k + 1)
        {
            ++j;
            if (cowNum[lb[j]] == 0)
                ++cur;
            ++cowNum[lb[j]];
            h.enQueue(Node(lb[j], cowNum[lb[j]]));
        }
        while (j < n && cur == k + 1 && cowNum[lb[j + 1]] != 0)
        {
            ++j;
            ++cowNum[lb[j]];
            h.enQueue(Node(lb[j], cowNum[lb[j]]));
        }
        while (!h.isEmpty() && h.getHead().index != cowNum[h.getHead().label])
            h.deQueue();
        if (!h.isEmpty())
            ans = max(ans, h.getHead().index);
        --cowNum[lb[i]];
        if (cowNum[lb[i]] == 0)
            --cur;
        h.enQueue(Node(lb[i], cowNum[lb[i]]));
        ++i;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    memset(lb, 0, sizeof(lb));
    memset(cowNum, 0, sizeof(cowNum));
    Heap h(MAXN);
    int n, k, index = 0, ans;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
    {
        cin >> cow[i].label;
        cow[i].index = i;
    }
    quickSort(cow, 1, n);
    cow[0].label = -1;
    lb[0] = -1;
    for (int i = 1; i <= n; ++i)
    {
        if (cow[i].label != cow[i - 1].label)
            index++;
        lb[cow[i].index] = index;
    }
    ans = longestSeq(h, n, k);
    cout << ans << '\n';
    cout << flush;
    return 0;
}