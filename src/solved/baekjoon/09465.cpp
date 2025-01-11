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
    int t;
    int n;
    std::vector<std::array<int, 2>> arr;
    std::vector<std::array<int, 3>> dp;

public:
    Solver()
    {
        std::cin >> t;
    }
    ~Solver() {}
    int getDp(int n)
    {
        if (dp[n][0] == INT_MAX)
        {
            dp[n][0] = getDp(n - 1);
            dp[n][1] = std::max(dp[n - 1][0], dp[n - 1][2]) + arr[n][0];
            dp[n][2] = std::max(dp[n - 1][0], dp[n - 1][1]) + arr[n][1];
            return *std::max_element(dp[n].begin(), dp[n].end());
        }
        return *std::max_element(dp[n].begin(), dp[n].end());
    }
    void solve()
    {
        while (t--)
        {
            std::cin >> n;
            arr.resize(n);
            dp.assign(n, {INT_MAX, INT_MAX, INT_MAX});
            for (auto &i : arr)
                std::cin >> i[0];
            for (auto &i : arr)
                std::cin >> i[1];
            dp[0][0] = 0, dp[0][1] = arr[0][0], dp[0][2] = arr[0][1];
            std::cout << getDp(n - 1) << '\n';
        }
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}