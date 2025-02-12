#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                           \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    ll n, p, q, x, y;
    std::unordered_map<ll, ll> map;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n >> p >> q >> x >> y;
        std::cout << getDp(n);
    }
    ll getDp(ll n)
    {
        if (n <= 0)
            return 1;
        if (map.contains(n))
            return map[n];
        else
            return map[n] = getDp(n / p - x) + getDp(n / q - y);
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}