#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                           \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    int n, k;
    std::vector<int> coin;
    std::vector<int> dp;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n >> k;
        coin.resize(n);
        dp.assign(k + 1, 0x00ffffff);
        for (auto &i : coin)
            std::cin >> i;
        dp[0] = 0;
        std::sort(coin.begin(), coin.end());
        coin.erase(std::unique(coin.begin(), coin.end()), coin.end());
        for (int i = 1; i <= k; i++)
        {
            for (auto &c : coin)
            {
                int r = i / c;
                for (int x = 0; x <= r; x++)
                {
                    dp[i] = std::min(dp[i], dp[i - x * c] + x);
                }
            }
        }
        if (dp[k] == 0x00ffffff)
            std::cout << -1;
        else
            std::cout << dp[k];
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}