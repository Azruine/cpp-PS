#include <bits/stdc++.h>
#include <array>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

/*
45656이란 수를 보자.

이 수는 인접한 모든 자리의 차이가 1이다. 이런 수를 계단 수라고 한다.

N이 주어질 때, 길이가 N인 계단 수가 총 몇 개 있는지 구해보자. 0으로 시작하는 수는 계단수가 아니다.
*/

class Solver
{
private:
    int n;
    std::vector<std::vector<int>> dp;

public:
    Solver()
    {
        std::cin >> n;
    }
    ~Solver() {}
    void solve()
    {
        const int MOD = 1'000'000'000;
        dp.assign(n + 1, std::vector<int>(10, -1));
        dp[1][0] = 0;
        std::fill(++dp[1].begin(), dp[1].end(), 1);
        auto fillTable = [&](int idx)
        {
            dp[idx][0] = dp[idx - 1][1];
            dp[idx][9] = dp[idx - 1][8];
            for (int i = 1; i < 9; i++)
                dp[idx][i] = (dp[idx - 1][i - 1] + dp[idx - 1][i + 1]) % MOD;
        };
        for (int i = 2; i <= n; i++)
            fillTable(i);
        std::cout << std::accumulate(dp[n].begin(), dp[n].end(), 0, [&](int acc, int x)
                                     { return (acc + x) % MOD; });
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}