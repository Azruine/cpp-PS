#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                          \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        int x, y, d, t;
        std::cin >> x >> y >> d >> t;
        ld dist = sqrt(x * x + y * y);
        ld ans = 0;
        for (; dist >2 * d; dist -= d)
            ans += t;
        ans += std::min({(ld)2.0 * t, dist, std::abs(dist - d) + t});
        std::cout << std::fixed << std::setprecision(10) << std::min(ans, (ld)sqrt(x * x + y * y)) << '\n';
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}