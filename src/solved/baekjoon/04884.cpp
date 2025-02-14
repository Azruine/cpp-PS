#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    ll g, t, a, d;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        while (std::cin >> g >> t >> a >> d)
        {
            if (g < 0)
                return;
            ll x = 0, temp = 1, tornament;
            x = t * (t - 1) / 2 * g;
            tornament = g * a + d;
            while (temp < tornament)
            {
                x += temp;
                temp <<= 1;
            }
            std::print("{}*{}/{}+{}={}+{}\n", g, a, t, d, x, temp - tornament);

        }
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}