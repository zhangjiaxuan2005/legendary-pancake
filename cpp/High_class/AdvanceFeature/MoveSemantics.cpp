//
// Created by 17246 on 2025/8/3.
//

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

class BigMemoryPool
{
    static const int size = 4096;

public:
    BigMemoryPool(): pool_(new char[size])
    {
    }

    ~BigMemoryPool()
    {
        delete[] pool_;
    }

    BigMemoryPool(BigMemoryPool&& other)
        noexcept
    {
        cout << "move constructor" << endl;
        pool_ = other.pool_;
        other.pool_ = nullptr;
    }

    BigMemoryPool(const BigMemoryPool& other): pool_(new char[size])
    {
        cout << "copy constructor" << endl;
        memcpy(pool_, other.pool_, size);
    }

    BigMemoryPool& operator=(BigMemoryPool&& other) noexcept
    {
        cout << "move assignment" << endl;
        delete[] pool_;
        pool_ = other.pool_;
        other.pool_ = nullptr;
        return *this;
    }

private:
    char* pool_;
};

class BigMemoryPool2
{
    static const int size = 4096;

public:
    BigMemoryPool2(): pool_(new char[size])
    {
    }

    ~BigMemoryPool2()
    {
        delete[] pool_;
    }

    BigMemoryPool2(BigMemoryPool2&& other) noexcept
    {
        pool_ = other.pool_;
        other.pool_ = nullptr;
    }

    BigMemoryPool2(const BigMemoryPool2& other): pool_(new char[size])
    {
        memcpy(pool_, other.pool_, size);
    }

    BigMemoryPool2& operator=(BigMemoryPool2&& other) noexcept
    {
        delete[] pool_;
        pool_ = other.pool_;
        other.pool_ = nullptr;
        return *this;
    }

private:
    char* pool_;
};

class BigMemoryPool3
{
    static const int size = 8192;

public:
    BigMemoryPool3(): pool_(new char[size])
    {
    }

    ~BigMemoryPool3()
    {
        delete[] pool_;
    }

    BigMemoryPool3(const BigMemoryPool3& other): pool_(new char[size])
    {
        memcpy(pool_, other.pool_, size);
    }

    BigMemoryPool3& operator=(BigMemoryPool3&& other) noexcept
    {
        delete[] pool_;
        pool_ = other.pool_;
        other.pool_ = nullptr;
        return *this;
    }

private:
    char* pool_;
};

namespace pool
{
    BigMemoryPool get_pool(const BigMemoryPool& pool)
    {
        return pool;
    }

    BigMemoryPool make_pool()
    {
        BigMemoryPool pool;
        pool = get_pool(pool);
        return pool;
        //由于C++23中,return里面加入了move函数
        // return get_pool(pool);

    }
}

namespace pool2
{
    BigMemoryPool2 get_pool(const BigMemoryPool2& pool)
    {
        return pool;
    }

    BigMemoryPool2 make_pool()
    {
        BigMemoryPool2 pool;
        pool = get_pool(pool);
        return pool;
    }
}

namespace pool3
{
    BigMemoryPool3 get_pool(const BigMemoryPool3& pool)
    {
        return pool;
    }

    BigMemoryPool3 make_pool()
    {
        BigMemoryPool3 pool;
        pool = get_pool(pool);
        return pool;
    }
}

class Xdata
{
public:
    Xdata()
    {
        cout << "create\n";
    }

    ~Xdata()
    {
        cout << "destroy\n";
    }

    Xdata(const Xdata&)
    {
        cout << "copy\n";
    }

    Xdata(Xdata&&) noexcept
    {
        cout << "move\n";
    }
};

void SetData(const vector<Xdata>& data)
{
}

auto Getdata()
{
    vector<Xdata> xdata(3);
    return xdata;
}

int main()
{
    BigMemoryPool my_pool = pool::make_pool();
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++)
    {
        BigMemoryPool2 pool = pool2::make_pool();
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << duration.count() << endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++)
    {
        BigMemoryPool3 pool = pool3::make_pool();
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << duration.count() << endl;
    vector<Xdata> xdatas(3);
    // vector<Xdata> xdata2 = xdatas;
    auto xdatas1 = move(xdatas);
    // SetData(move(xdatas));
    auto xdata = Getdata();
}




