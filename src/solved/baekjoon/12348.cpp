#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    ll n;
    ll getDigitSum(ll n)
    {
        ll res = 0;
        while (n)
        {
            res += n % 10;
            n /= 10;
        }
        return res;
    }

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n;
        int len = std::to_string(n).length();
        ll start = n - len * 9;
        bool haveAns = false;
        for (; start < n; start++)
        {
            if (n == getDigitSum(start) + start)
            {
                std::cout << start;
                haveAns = true;
                break;
            }
        }
        if (!haveAns)
            std::cout << 0;
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}