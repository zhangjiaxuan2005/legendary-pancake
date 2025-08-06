//
// Created by 17246 on 2025/8/3.
//


#include <iostream>
using namespace std;

namespace f1
{
    void foo()
    {
        cout << "f1" << endl;
    }
}

namespace f2
{
    void foo()
    {
        cout << "f2" << endl;
    }
}


namespace parent
{
    namespace child1
    {
        void foo()
        {
            cout << "child1" << endl;
        }
    }

    inline namespace child2
    {
        void foo()
        {
            cout << "child2" << endl;
        }
    }
}

namespace A::B::C
{
    void foo()
    {
        cout << "A::B::C" << endl;
    }
}

namespace a::inline b::inline c
{
    void foo()
    {
        cout << "a::b::c" << endl;
    }
}


int main()
{
    f1::foo();
    f2::foo();
    parent::child1::foo();
    parent::foo();
    A::B::C::foo();
    a::foo();
}

