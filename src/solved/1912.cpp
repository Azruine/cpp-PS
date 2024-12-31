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
    std::vector<int> dp;

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
        dp.assign(n, 0);
        std::inclusive_scan(arr.begin(), arr.end(), dp.begin(), [](int acc, int x)
                            { return std::max(acc + x, x); });
        std::cout << *std::max_element(dp.begin(), dp.end());
    }
};

int main()
{
    fastio;
    Solver s;
    s.solve();
    return 0;
}