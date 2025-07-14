//
// Created by 17246 on 2025/7/10.
//
#include <iostream>
using namespace std;
class person
{
    friend ostream &operator<<(ostream &out, const person &p);
public:
    person(int a, int b)
    {
        m_A = a;
        m_B = b;
    }
private:
    int m_A;
    int m_B;

};
ostream &operator<<(ostream &out, const person &p)
{
    out << "A:" << p.m_A <<" "<< "B:" << p.m_B << endl;
    return out;
}

int main()
{
    person p1(10, 20);
    cout << p1 << endl;
}
