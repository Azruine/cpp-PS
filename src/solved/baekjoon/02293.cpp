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
    int n, k;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n >> k;
        std::vector<int> coin(n);

        for (auto &i : coin)
            std::cin >> i;

        std::sort(coin.begin(), coin.end());
        std::vector<int> dp(k + 1, 0);

        dp[0] = 1;
        for (auto &c : coin)
            for (int i = c; i <= k; i++)
                dp[i] += dp[i - c];

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