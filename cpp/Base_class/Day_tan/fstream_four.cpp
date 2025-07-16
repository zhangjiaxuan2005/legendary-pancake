//
// Created by 17246 on 2025/7/14.
//
#include <fstream>
#include <iostream>
using namespace std;

class person
{
public:
    char name[64] = {};
    int age = 0;
};

int main()
{
    fstream ifs("person.txt", ios::binary | ios::in);
    if (!ifs.is_open())
    {
        cout << "�ļ���ʧ��" << endl;
        return -1;
    }
    person p1;
    ifs.read((char*)&p1, sizeof(person));
    cout << "������" << p1.name << " ���䣺" << p1.age << endl;
    ifs.close();
    return 0;
}
