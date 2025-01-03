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

public:
    Solver()
    {
        std::cin >> n;
    }
    ~Solver() {}
    void solve()
    {
        std::cout << n;
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}