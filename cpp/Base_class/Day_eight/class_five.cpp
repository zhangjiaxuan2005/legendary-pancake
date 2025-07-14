//
// Created by 17246 on 2025/7/14.
//
#include <iostream>
using namespace std;

class animal
{
public:
    virtual ~animal() = default;
    virtual void speak() =0;
};

class dog : public animal
{
public:
    void speak() override
    {
        cout << "dog speak" << endl;
    }
};

class cat : public animal
{
public:
    void speak() override
    {
        cout << "cat speak" << endl;
    }
};

void doSpeak(animal& animal)
{
    animal.speak();
}

int main()
{
    dog dog;
    cat cat;
    doSpeak(dog);
    doSpeak(cat);
}
