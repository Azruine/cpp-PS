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
    int k;
    std::vector<int> vec;
    std::vector<int> sum;

public:
    Solver()
    {
        std::cin >> n >> k;
        vec.resize(n);
        for (auto &i : vec)
            std::cin >> i;
    }
    ~Solver() {}
    void solve()
    {
        sum.resize(n - k + 1);
        sum[0] = std::accumulate(vec.begin(), vec.begin() + k, 0);
        for (int i = k; i < n; i++)
            sum[i - k + 1] = sum[i - k] - vec[i - k] + vec[i];
        std::cout << *std::max_element(sum.begin(), sum.end()) << "\n";
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}