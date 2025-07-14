//
// Created by 17246 on 2025/7/14.
//
#include <iostream>
using namespace std;

class person
{
public:
    int* m_A;

    person(int a)
    {
        m_A = new int(a);
    }
    ~person()
    {
        if (m_A != nullptr)
        {
            delete m_A;
            m_A = nullptr;
        }
    }
    person& operator=(const person& p)
    {
        if (m_A!= nullptr)
        {
            delete m_A;
            m_A = nullptr;
        }
        m_A = new int(*p.m_A);
        return *this;
    }
};

void test01()
{
    person p1(18);
    person p2(20);
    p2 = p1;
    cout << *p1.m_A << endl;
    cout << *p2.m_A << endl;
}

int main()
{
    test01();
}
