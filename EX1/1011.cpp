#include <iostream>
#include <iomanip>
using namespace std;

class MyComplex
{
    friend istream &operator>>(istream &is, MyComplex &obj);
    friend ostream &operator<<(ostream &os, const MyComplex &obj);
    friend MyComplex operator+(const MyComplex &c1, const MyComplex &c2);
    friend MyComplex operator-(const MyComplex &c1, const MyComplex &c2);
    friend MyComplex operator*(const MyComplex &c1, const MyComplex &c2);
    friend MyComplex operator/(const MyComplex &c1, const MyComplex &c2);
private:
    double x, y;
public:
    MyComplex(double re = 0,double im = 0):x(re),y(im) {};
    ~MyComplex() {};
    MyComplex &operator+=(const MyComplex &obj);
    MyComplex &operator-=(const MyComplex &obj);
    MyComplex &operator*=(const MyComplex &obj);
    MyComplex &operator/=(const MyComplex &obj);
};

int main()
{
    MyComplex z1;
    MyComplex z2;

    cin >> z1 >> z2;

    cout << z1 + z2 << endl;
    cout << z1 - z2 << endl;
    cout << z1 * z2 << endl;
    cout << z1 / z2 << endl;
    cout << (z1 += z2) << endl;
    cout << (z1 -= z2) << endl;
    cout << (z1 *= z2) << endl;
    cout << (z1 /= z2) << endl;

    return 0;
}
MyComplex &MyComplex::operator+=(const MyComplex &obj)
{
    x += obj.x;
    y += obj.y;
    return *this;
}

MyComplex &MyComplex::operator-=(const MyComplex &obj)
{
    x -= obj.x;
    y -= obj.y;
    return *this;
}

MyComplex &MyComplex::operator*=(const MyComplex &obj)
{
    double tmp_x = x, tmp_y = y;
    x = tmp_x * obj.x - tmp_y * obj.y;
    y = tmp_y * obj.x + tmp_x * obj.y;
    return *this;
}

MyComplex &MyComplex::operator/=(const MyComplex &obj)
{
    double tmp_x = x, tmp_y = y;
    x = (tmp_x * obj.x + tmp_y * obj.y) / (obj.x * obj.x + obj.y * obj.y);
    y = (tmp_y * obj.x - tmp_x * obj.y) / (obj.x * obj.x + obj.y * obj.y);
    return *this;
}

istream &operator>>(istream &is, MyComplex &obj)
{
    is >> obj.x >> obj.y;
    return is;
}

ostream &operator<<(ostream &os, const MyComplex &obj)
{
    os << fixed << setprecision(2) << obj.x << ' ' << fixed << setprecision(2) << obj.y;
    return os;
}

MyComplex operator+(const MyComplex &c1, const MyComplex &c2)
{
    MyComplex tmp;
    tmp.x = c1.x + c2.x;
    tmp.y = c1.y + c2.y;
    return tmp;
}

MyComplex operator-(const MyComplex &c1, const MyComplex &c2)
{
    MyComplex tmp;
    tmp.x = c1.x - c2.x;
    tmp.y = c1.y - c2.y;
    return tmp;
}

MyComplex operator*(const MyComplex &c1, const MyComplex &c2)
{
    MyComplex tmp;
    tmp.x = c1.x * c2.x - c1.y * c2.y;
    tmp.y = c1.y * c2.x + c1.x * c2.y;
    return tmp;
}

MyComplex operator/(const MyComplex &c1, const MyComplex &c2)
{
    MyComplex tmp;
    tmp.x = (c1.x * c2.x + c1.y * c2.y) / (c2.x * c2.x + c2.y * c2.y);
    tmp.y = (c1.y * c2.x - c1.x * c2.y) / (c2.x * c2.x + c2.y * c2.y);
    return tmp;
}
