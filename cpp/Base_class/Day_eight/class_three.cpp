//
// Created by 17246 on 2025/7/8.
//
#include <iostream>
using namespace std;
class base
{
public:
    int m_A;

protected:
    int m_B;

private:
    int m_C;
};

class son1 : public base
{
    void func()
    {
        m_A = 10;
        m_B = 20;
       // m_C = 30;
    }
};

void test01()
{
    son1 s1;
    s1.m_A = 100;
    cout << s1.m_A << endl;
    //s1.m_B = 200;
}
class son2 : protected base
{
    void func()
    {
        m_A = 10;
        m_B = 20;
    }
};
void test02()
{
    son2 s2;
   // s2.m_A = 100;
}
class son3 : private base
{
    void func()
    {
        m_A = 10;
        m_B = 20;
    }
};
void test03()
{
    son3 s3;
   // s3.m_A = 100;
}
int main()
{
    test01();
    test02();
    test03();
}