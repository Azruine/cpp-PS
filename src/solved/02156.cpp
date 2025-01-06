#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    int n;
    std::vector<std::vector<int>> dp;
    std::vector<int> data;

public:
    Solver()
    {
        std::cin >> n;
        data.assign(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            std::cin >> data[i];
        }
        dp.assign(n + 1, std::vector<int>(3, 0));
    }
    ~Solver() {}
    void solve()
    {
        dp[1][0] = data[1];
        dp[1][1] = data[1];
        dp[1][2] = 0;
        for (int i = 2; i <= n; i++)
        {
            dp[i][0] = dp[i - 1][2] + data[i];
            dp[i][1] = dp[i - 1][0] + data[i];
            dp[i][2] = *std::max_element(dp[i - 1].begin(), dp[i - 1].end());
        }
        std::cout << *std::max_element(dp[n].begin(), dp[n].end()) << std::endl;
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}