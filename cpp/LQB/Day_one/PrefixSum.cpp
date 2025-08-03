//
// Created by 17246 on 2025/8/2.
// QJ.3382
//
#include <cmath>
#include <iostream>
using namespace std;

const int N = 1e5 + 10;
const int MOD = 1e9 + 7;

long long a[N];
long long b[N][10];

int n, m, l, r, k;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        for (int j = 1; j <= 5; j++)
        {
            b[i][j] = b[i - 1][j] + pow(a[i], j);
        }
    }

    while (m--)
    {
        cin >> l >> r >> k;
        cout << (b[r][k] - b[l - 1][k]) % MOD << endl;
    }
}

