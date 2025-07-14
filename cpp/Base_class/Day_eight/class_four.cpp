//
// Created by 17246 on 2025/7/8.
//
#include <iostream>
using namespace std;
class base
{
public:
    int m_A;
    base()
    {
        m_A = 100;
    }
};
class son : public base
{
public:
    int m_A;
    son()
    {
        m_A = 200;
    }
};

void test01()
{
    son s;
    cout << s.m_A << endl;
    cout << s.base::m_A << endl;
}

int main()
{
    test01();
    return 0;
}