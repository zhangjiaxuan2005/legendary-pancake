//
// Created by 17246 on 2025/7/10.
//
#include <iostream>
using namespace std;
class person
{
public:
    int m_A;
    int m_B;
    person(int a, int b)
    {
        m_A = a;
        m_B = b;
    }
    person operator+(person &p) const
    {
        person temp(0, 0);
        temp.m_A = m_A + p.m_A;
        temp.m_B = m_B + p.m_B;
        return temp;
    }
};

int main()
{
    person p1(10, 20);
    person p2(30, 40);
    person p3 = p1 + p2;
    cout << "p3.m_A = " << p3.m_A << endl;
    cout << "p3.m_B = " << p3.m_B << endl;
}