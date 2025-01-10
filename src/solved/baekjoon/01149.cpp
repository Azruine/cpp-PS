#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                    \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    int n;
    std::vector<std::array<int, 3>> cost;
    std::vector<std::array<int, 3>> dp;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n;
        cost.resize(n);
        dp.resize(n);
        while (n--)
            std::cin >> cost[n][0] >> cost[n][1] >> cost[n][2];
        std::inclusive_scan(cost.begin(), cost.end(), dp.begin(), [](const auto &a, const auto &b) {
            return std::array<int, 3>{std::min(a[1], a[2]) + b[0], std::min(a[0], a[2]) + b[1], std::min(a[0], a[1]) + b[2]};
        });
        std::cout << *std::min_element(dp.back().begin(), dp.back().end()) << '\n';
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}