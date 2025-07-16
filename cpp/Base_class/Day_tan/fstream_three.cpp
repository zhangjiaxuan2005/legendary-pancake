//
// Created by 17246 on 2025/7/14.
//
#include <fstream>
using namespace std;

class person
{
public:
    char name[64] = {};
    int age = 0;
};

int main()
{
    ofstream ofs("person.txt", ios::binary | ios::out);
    person p1={"Tom", 18} ;
    ofs.write((const char*)&p1, sizeof(person));
    ofs.close();
    return 0;
}
