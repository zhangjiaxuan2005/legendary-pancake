//
// Created by 17246 on 2025/7/14.
//
#include <iostream>
#include <string>
using namespace std;

class MyPrinter
{
public:
    void operator()(string test)
    {
        cout << test << endl;
    }
};

int main()
{
    MyPrinter printer;
    printer("hello world");
    return 0;
}