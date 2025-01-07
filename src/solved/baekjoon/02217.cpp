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
    std::vector<int> arr;

public:
    Solver()
    {
        std::cin >> n;
        arr.resize(n);
        for (auto &i : arr)
            std::cin >> i;
    }
    ~Solver() {}
    void solve()
    {
        std::sort(arr.begin(), arr.end(), std::greater<int>());
        int ans = INT_MIN;
        for (int i = 0; i < n; i++)
        {
            ans = std::max(ans, arr[i] * (i + 1));
        }
        std::cout << ans << "\n";
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}