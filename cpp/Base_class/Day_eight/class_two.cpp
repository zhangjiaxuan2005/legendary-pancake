//
// Created by 17246 on 2025/7/8.
//

#include <string>
#include <iostream>
using namespace std;
class Building;

class goodGay
{
public:
    goodGay();
    ~goodGay();
    void visit() const;
    Building* building;
};

class Building
{
    friend class goodGay;
public:
    Building();
    string sittingRoom;

private:
    string bedRoom;
};

Building::Building()
{
    this->sittingRoom = "����";
    this->bedRoom = "����";
}

goodGay::goodGay()
{
    building = new Building;
}
goodGay::~goodGay()//��������
{
    if (building != nullptr)
    {
        delete building;
        building = nullptr;//��ֹҰָ��
    }
}

void goodGay::visit() const
{
    cout << "�û������ڷ��ʣ�" << building->sittingRoom << endl;
    cout << "�û������ڷ��ʣ�" << building->bedRoom << endl;
}
void test01()
{
    goodGay gg;
    gg.visit();
}

int main()
{
    test01();
}
