//
// Created by 17246 on 2025/7/10.
//
#include<iostream>
using namespace std;
class person{
    friend ostream& operator<<(ostream& out, const person& p);
public:
    person(int a)
    {
        m_A=a;
    }
    person &operator++()
    {
        m_A++;
        return *this;
    }

    person operator++(int)
    {
        person temp=*this;
        m_A++;
        return temp;
    }

private:
    int m_A;
};
ostream& operator<<(ostream& out, const person& p)
{
    out<<"A:"<<p.m_A<<endl;
    return out;
}

int main()
{
    person p(10);
    cout<<++p<<endl;
    cout<<p++<<endl;
    return 0;
}