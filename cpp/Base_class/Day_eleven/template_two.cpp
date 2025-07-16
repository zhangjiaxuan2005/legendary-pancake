//
// Created by 17246 on 2025/7/15.
//
#include <iostream>
using namespace std;
template<typename T>
class person
{
public:
    T m_a;
    T m_b;
    person(T a, T b)
    {
        this->m_a = a;
        this->m_b = b;
    }
};
template<typename  T>
void print_person(person<T> p)
{
    cout << p.m_a << " " << p.m_b << endl;
}
int main()
{
    person p1(1, 2);
    person p2(1.1, 2.2);
    print_person(p1);
    print_person(p2);
}