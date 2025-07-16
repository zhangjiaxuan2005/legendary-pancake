//
// Created by 17246 on 2025/7/14.
//
#include <fstream>
using namespace std;

int main()
{
    ofstream ofs;
    ofs.open("test.txt", ios::out);
    ofs << "hello world" << endl;
    ofs.close();
    return 0;
}
