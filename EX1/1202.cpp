#include <iostream>
using namespace std;

class bigInt
{
	friend bigInt operator+(const bigInt &a, const bigInt &b);
private:
	struct Node
	{
		int data;
		Node *prev, *next;

		Node(const int &x, Node *p = NULL, Node *n = NULL)
		{
			data = x;
			prev = p;
			next = n;
		}
		Node() :prev(NULL), next(NULL) {};
		~Node() {};
	};

	Node *head, *tail;
public:
	bigInt(const char *num = "");
	~bigInt();
	void clear();
    void insert(const int &num);
	void show() const;
};

bigInt::bigInt(const char *num)
{
	const char *num_p = num;
	Node *p;

	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
	p = head->next;

	while (*num_p)
	{
		Node *cur_p = new Node(*num_p - '0', head, p);
		head->next = cur_p;
		p->prev = cur_p;
		p = cur_p;
		++num_p;
	}
}
bigInt::~bigInt()
{
	clear();
	delete head;
	delete tail;
}

void bigInt::clear()
{
	Node *p = head->next, *q;
	head->next = tail;
	tail->prev = head;
	while (p->next)
	{
		q = p->next;
		delete p;
		p = q;
	}
}

void bigInt::insert(const int &num)
{
    Node *cur_p = new Node(num, tail->prev, tail);
	tail->prev->next = cur_p;
	tail->prev = cur_p;
}

bigInt operator+(const bigInt &a, const bigInt &b)
{
	bigInt::Node *p_a = a.head->next, *p_b = b.head->next;
    bigInt result;
    int carry = 0;
    while(p_a != a.tail && p_b != b.tail)
    {
        int tmp = p_a->data + p_b->data + carry;
        result.insert(tmp % 10);
        carry = tmp / 10;
        p_a = p_a->next;
        p_b = p_b->next;
    }
    while(p_a != a.tail)
    {
        int tmp = p_a->data + carry;
        result.insert(tmp % 10);
        carry = tmp / 10;
        p_a = p_a->next;
    }
    while(p_b != b.tail)
    {
        int tmp = p_b->data + carry;
        result.insert(tmp % 10);
        carry = tmp / 10;
        p_b = p_b->next;
    }

    if(carry != 0)
        result.insert(carry);

    return result;
}

void bigInt::show() const
{
	Node *p = tail->prev;
	while (p!=head)
	{
		cout << p->data;
		p = p->prev;
	}
	cout << endl;
}

int main()
{
	char a[1000001], b[1000001];
	cin >> a;
    cin >> b;
	bigInt num1(a);
    bigInt num2(b);
    bigInt result = num1 + num2;
	result.show();
	return 0;
}
