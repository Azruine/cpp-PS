#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                          \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    int n;
    std::vector<std::array<std::array<int, 3>, 3>> dp;
    std::vector<std::array<int, 3>> cost;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n;
        dp.resize(n + 1, {{{INT_MAX, INT_MAX, INT_MAX}, {INT_MAX, INT_MAX, INT_MAX}, {INT_MAX, INT_MAX, INT_MAX}}});
        cost.resize(n + 1);
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < 3; j++)
                std::cin >> cost[i][j];
        for (int i = 0; i < 3; i++)
            dp[1][i][i] = cost[1][i];
        for (int i = 2; i <= n ; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        if (l == j || dp[i - 1][l][k] == INT_MAX)
                            continue;
                        dp[i][j][k] = std::min(dp[i][j][k], dp[i - 1][l][k] + cost[i][j]);
                    }
                }
            }
        }
        int answer = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (i == j)
                    continue;
                answer = std::min(answer, dp[n][i][j]);
            }
        }
        std::cout << answer << '\n';
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}