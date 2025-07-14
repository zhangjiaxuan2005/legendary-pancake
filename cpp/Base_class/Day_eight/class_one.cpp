
//
// Created by 17246 on 2025/6/24.
//
#include <string>
#include <iostream>
using namespace std;

class person
{
public:
    string name;
    int age;

    person(string name, int age)
    {
        this->name = name;
        this->age = age;
    }

    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};

int main()
{
    person p1("John", 20);
    p1.display();
}
