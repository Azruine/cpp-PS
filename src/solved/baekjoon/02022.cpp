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
private:
    ld x, y, c;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> x >> y >> c;
        ld left = 0, right = std::min(x, y);
        while (right - left > 1e-6)
        {
            ld mid = (left + right) / 2;
            ld h1 = std::sqrt(x * x - mid * mid);
            ld h2 = std::sqrt(y * y - mid * mid);
            ld h = (h1 * h2) / (h1 + h2);
            if (h > c)
                left = mid;
            else
                right = mid;
        }
        std::print("{:.3f}", left);
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}