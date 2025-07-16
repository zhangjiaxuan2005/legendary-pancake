//
// Created by 17246 on 2025/7/15.
//
#include <iostream>
using namespace std;
template<typename T>
class base
{
public:
    T m_a;
    T m_b;
    base(T a, T b)
    {
        this->m_a = a;
        this->m_b = b;
    }
};
class son1 : public base<int>
{
public:
    son1(int a, int b) : base<int>(a, b)
    {
        this->m_a = a;
        this->m_b = b;
    }
    void print()
    {
        cout << "son1: " << this->m_a << " " << this->m_b << endl;
    }
};
template<typename T>
class son2 : public base<T>
{
public:
    son2(T a, T b) : base<T>(a, b)
    {
        this->m_a = a;
        this->m_b = b;
    }
    void print()
    {
        cout << "son2: " << this->m_a << " " << this->m_b << endl;
    }
};

int main()
{
    son1 s1(1, 2);
    s1.print();
    son2 s2(1, 2);
    s2.print();
}
