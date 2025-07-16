//
// Created by 17246 on 2025/7/14.
//
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    ifstream ifs;
    ifs.open("test.txt", ios::in);
    if (!ifs.is_open())
    {
        cout << "文件打开失败" << endl;
        return -1;
    }

    // char buf[1024] = {0};
    // while (ifs >> buf)
    // {
    //     cout << buf << " ";
    // }

    // char buf2[1024] = {0};
    // while (ifs.getline(buf2, sizeof(buf2)))
    // {
    //     cout << buf2 << " ";
    // }

    string buf3;
    while (getline(ifs, buf3))
    {
        cout << buf3 << " ";
    }

    // char c;
    // while ((c=ifs.get()) != EOF)
    // {
    //     cout << c;
    // }
    ifs.close();
    return 0;
}
