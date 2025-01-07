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
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (j + arr[j].first <= i)
                {
                    dp[i] = std::max(dp[i], dp[j] + arr[j].second);
                }
            }
        }
        std::cout << dp.back();
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}