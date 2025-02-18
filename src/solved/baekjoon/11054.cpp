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
    int n;
    std::vector<int> data;
    // first is increasing sequence, second is decreasing sequance
    // i.e. dp[8][0]: longest bitonic sequence which is increasing now and containing 8th element as last element
    // dp[8][1]: longest bitonic sequence which is decreasing now and containing 8th element as last element
    std::vector<std::array<int, 2>> dp;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n;
        data.resize(n);
        for (auto &i : data)
            std::cin >> i;
        dp.assign(n, {1, 1});
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                // increasing sequence
                if (data[i] > data[j])
                    dp[i][0] = std::max(dp[i][0], dp[j][0] + 1);
                // decreasing sequence
                if (data[i] < data[j])
                    dp[i][1] = std::max(dp[i][1], std::max(dp[j][0], dp[j][1]) + 1);
            }
        }
        int ans = 0;
        for (auto &arr: dp)
            ans = std::max(ans, std::max(arr[0], arr[1]));
        std::cout << ans;
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}