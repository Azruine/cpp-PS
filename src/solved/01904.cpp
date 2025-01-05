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
    std::vector<int> dp;

public:
    Solver()
    {
        std::cin >> n;
        dp.assign(n + 1, 0);
    }
    ~Solver() {}
    void solve()
    {
        dp[2] = 2;
        dp[1] = 1;
        std::function<int(int)> getDp = [&](int i) -> int
        {
            if (dp[i] != 0)
                return dp[i];
            else
                return dp[i] = (getDp(i - 1) + getDp(i - 2)) % 15746;
        };
        std::cout << getDp(n) << '\n';
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}