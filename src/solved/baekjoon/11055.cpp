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
    std::vector<int> arr;

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
        std::vector<int> dp(n, 0);

        std::copy(arr.begin(), arr.end(), dp.begin());
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (arr[i] > arr[j])
                {
                    dp[i] = std::max(dp[i], dp[j] + arr[i]);
                }
            }
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