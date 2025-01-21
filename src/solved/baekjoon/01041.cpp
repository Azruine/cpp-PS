#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                    \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

struct Cube
{
    int a, b, c, d, e, f;
    Cube() : a(0), b(0), c(0), d(0), e(0), f(0) {}
    Cube(int a, int b, int c, int d, int e, int f) : a(a), b(b), c(c), d(d), e(e), f(f) {}
    ll getMinSide()
    {
        return std::min({a, b, c, d, e, f});
    }
    ll getMaxSide()
    {
        return std::max({a, b, c, d, e, f});
    }
    ll getMinTwoSum()
    {
        std::vector<int> v = {a + b, a + c, a + d, a + e, b + c, b + d, b + f, c + e, c + f, d + e, d + f, e + f};
        return *std::min_element(v.begin(), v.end());
    }
    ll getMinThreeSum()
    {
        std::vector<int> v = {a + b + c, a + b + d, a + d + e, a + e + c, b + d + f, b + c + f, f + c + e, f + d + e};
        return *std::min_element(v.begin(), v.end());
    }
    ll getMinFiveSum()
    {
        return (a + b + c + d + e + f) - getMaxSide();
    }
};
std::istream &operator>>(std::istream &is, Cube &cube)
{
    is >> cube.a >> cube.b >> cube.c >> cube.d >> cube.e >> cube.f;
    return is;
}

class Solver
{
private:
    ll n;
    Cube cube;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n;
        std::cin >> cube;
        if (n == 1)
            std::cout << cube.getMinFiveSum();
        else if (n == 2)
        {
            ll ans = 0;
            ans+= cube.getMinThreeSum() * 4;
            ans+= cube.getMinTwoSum() * 4;
            std::cout << ans;
        }
        else
        {
            ll ans = 0;
            ans+= (n - 2) * (n - 2) * cube.getMinSide() + (n - 2) * (n - 1) * cube.getMinSide() * 4;
            ans+= ((n - 1) * 4 + (n - 2) * 4) * cube.getMinTwoSum();
            ans+= (ll)4 * cube.getMinThreeSum();
            std::cout << ans;
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