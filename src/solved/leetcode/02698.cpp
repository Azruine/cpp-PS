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
    const int n = 1000;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        for (int i = 1; i <= n; i++)
        {
            if (isP(i))
                std::cout << i << ",}"[i == n];
        }
    }
    bool isP(int n)
    {
        int x = n * n;
        int l = std::to_string(x).length() - 1;
        for (int i = 0; i < (1 << l); i++)
        {
            std::vector<int> interval({0});
            int temp = 0;
            while (temp < l)
            {
                if (i & (1 << temp))
                    interval.emplace_back(temp + 1);
                temp++;
            }
            interval.emplace_back(l + 1);
            int sumParts = 0;
            for (size_t i = 0; i < interval.size() - 1; i++)
            {
                int start = interval[i];
                int len = interval[i + 1] - interval[i];
                std::string part = std::to_string(x).substr(start, len);
                int num = std::stoi(part);
                sumParts += num;
            }
            if (sumParts == n)
                return true;
        }
        return false;
    }
};

class Solution
{
private:
    std::vector<int> kar = {1, 9, 10, 36, 45, 55, 82, 91, 99, 100, 235, 297, 369, 370, 379, 414, 657, 675, 703, 756, 792, 909, 918, 945, 964, 990, 991, 999, 1000};

public:
    int punishmentNumber(int n)
    {
        auto ub = std::upper_bound(kar.begin(), kar.end(), n);
        return std::accumulate(kar.begin(), ub, 0, [&](int acc, int x)
                               { return acc + x * x; });
    }
};
