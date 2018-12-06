#include <iostream>
#include <iomanip>
using namespace std;

template <class T>
class seqQueue
{
    private:
        T *data;
        int maxSize;
        int front, rear;
        void doubleSpace();
    public:
        seqQueue(int size = 10);
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

int main()
{
    int n, p, q, maxTime, coachNum = 0, trunkNum = 0, time_now = 0, onShip = 0;
    double trunkWT = 0, coachWT = 0;
    seqQueue<int> coach, trunk;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        cin >> p >> q;
        if(p == 0)
            coach.enQueue(q);
        else
            trunk.enQueue(q);
    }
    for(time_now = 0; !coach.isEmpty() || !trunk.isEmpty(); time_now += 10)
    {
        for(onShip = 0; onShip < 8 && coach.getHead() <= time_now && !coach.isEmpty(); ++onShip)
        {
            coachWT += time_now - coach.deQueue();
            ++coachNum;
        }
        for(; onShip < 10 && trunk.getHead() <= time_now && !trunk.isEmpty(); ++onShip)
        {
            trunkWT += time_now - trunk.deQueue();
            ++trunkNum;
        }
        for(; onShip < 10 && coach.getHead() <= time_now && !coach.isEmpty(); ++onShip)
        {
            coachWT += time_now - coach.deQueue();
            ++coachNum;
        }
    }
    cout << setprecision(3) << fixed << coachWT / coachNum << ' ' << setprecision(3) << fixed << trunkWT / trunkNum << endl;
    return 0;
}