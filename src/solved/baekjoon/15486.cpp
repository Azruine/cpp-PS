#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

std::istream &operator>>(std::istream &is, std::pair<int, int> &p)
{
    is >> p.first >> p.second;
    return is;
}

class Solver
{
private:
    int n;
    std::vector<std::pair<int, int>> arr;

public:
    Solver()
    {
        std::cin >> n;
        arr.resize(n);
        for (int i = 0; i < n; i++)
            std::cin >> arr[i];
    }
    ~Solver() {}
    void solve()
    {
        std::vector<int> dp(n + 1, 0);
        dp[0] = 0;
        for (int i = 0; i < n; i++)
        {
            dp[i + 1] = std::max(dp[i], dp[i + 1]);
            if (i + arr[i].first <= n)
                dp[i + arr[i].first] = std::max(dp[i] + arr[i].second, dp[i + arr[i].first]);
        }
        std::cout << *std::max_element(dp.begin(), dp.end());
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}