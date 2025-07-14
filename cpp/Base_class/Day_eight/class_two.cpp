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
    this->sittingRoom = "客厅";
    this->bedRoom = "卧室";
}

goodGay::goodGay()
{
    building = new Building;
}
goodGay::~goodGay()//析构函数
{
    if (building != nullptr)
    {
        delete building;
        building = nullptr;//防止野指针
    }
}

void goodGay::visit() const
{
    cout << "好基友正在访问：" << building->sittingRoom << endl;
    cout << "好基友正在访问：" << building->bedRoom << endl;
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
