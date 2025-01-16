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
    ll n, m;
    const ll MOD = 1'000'000'007;
    ll modularExp(ll a, ll r)
    {
        if (r < 0)
            return 0;
        ll res = 1;
        while (r > 0)
        {
            if (r % 2 == 1)
                res = (res * a) % MOD;
            a = (a * a) % MOD;
            r /= 2;
        }
        return res;
    }

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n >> m;
        int x = 0;
        std::vector<int> dance(n, 0);
        for (auto &d : dance)
        {
            std::cin >> d >> d;
            if (d == 1)
                x++;
        }
        if (m == 1 && n - x == 1)
        {
            std::cout << 1 << '\n';
            return;
        }
        else if (m == 1 && n - x > 1)
        {
            std::cout << 0 << '\n';
            return;
        }
        else if (m == 1 && n - x == 0)
        {
            std::cout << n << '\n';
            return;
        }
        ll ans = 0;
        ll temp = modularExp(m - 1, x - 1);
        ans += temp * x;
        ans += temp * (m - 1);
        ans += temp * (m - 1) * (m - 1) * (n - x);
        // ans += modularExp(m - 1, x);
        // ans += modularExp(m - 1, x + 1) * (n - x);
        // ans += modularExp(m - 1, x - 1) * x;
        ans %= MOD;
        std::cout << ans << '\n';
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}