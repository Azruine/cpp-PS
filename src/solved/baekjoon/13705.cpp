#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;
using lld = std::float128_t;

#define 고속입출력                           \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    lld sin(lld x)
    {
        lld pi = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651Q;
        x -= (__int128_t)(x / (pi * 2)) * 2 * pi;
        lld r = x, t = x, f = 1;
        for (int i = 1; i < 100; i++)
        {
            f *= 2 * i * (2 * i + 1);
            t *= -x * x;
            r += t / f;
        }
        return r;
    }

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        lld l = (c - b) / (lld)a, r = (c + b) / (lld)a;
        l -= 0.1, r += 0.1;
        int t = 100;
        while (t--)
        {
            lld m = (l + r) / 2;
            lld val = a * m + b * sin(m);
            if (val < c)
                l = m;
            else
                r = m;
        }
        lld x = (l + r) / 2;
        lld u = 1'000'000'000'000, r_ = 0.5;
        ld y = (ld)((__int128_t)(x * u + r_) / u);
        std::cout << std::fixed << std::setprecision(6) << y << '\n';
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}