#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

ull modMul128(ull a, ull b, ull m)
{
    a %= m, b %= m;
    __uint128_t a128 = a, b128 = b, m128 = m;
    return (ull)((a128 * b128) % m128);
}

ull modPow128(ull a, ull r, ull m)
{
    a %= m;
    __uint128_t a128 = a, ret = 1, m128 = m;
    while (r > 0)
    {
        if (r & 1)
            ret = (ret * a128) % m128;
        a128 = (a128 * a128) % m128;
        r >>= 1;
    }
    return (ull)ret;
}

ull comb(ull n, ull r, ull p)
{
    if (r > n)
        return 0;
    if (r == 0 || r == n)
        return 1;

    static std::vector<ull> fac;
    static ull cachedP = 0;
    if (p != cachedP)
    {
        fac.assign(p, 1);
        for (ull i = 1; i < p; i++)
            fac[i] = modMul128(fac[i - 1], i, p);
        cachedP = p;
    }

    ull numerator = fac[n];
    ull denominator = modMul128(fac[r], fac[n - r], p);

    ull invDen = modPow128(denominator, p - 2, p);

    return modMul128(numerator, invDen, p);
}

ull lucas(ull n, ull r, ull p)
{
    if (r > n)
        return 0;
    ull res = 1;
    while (n > 0 || r > 0)
    {
        ull n_i = n % p;
        ull r_i = r % p;
        if (r_i > n_i)
            return 0;
        res = modMul128(res, comb(n_i, r_i, p), p);
        n /= p;
        r /= p;
    }
    return res;
}

ull modInv(ull a, ull b)
{
    ll s0 = 1, s1 = 0;
    ll r0 = a, r1 = b;

    while (r1 != 0)
    {
        ll q = r0 / r1;
        ll tmp = r0 % r1;
        r0 = r1;
        r1 = tmp;

        tmp = s0 - q * s1;
        s0 = s1;
        s1 = tmp;
    }

    if (r0 != 1)
        return 0;

    if (s0 < 0)
        s0 += b;
    return (ull)s0;
}

int crt(int a, int b)
{
    const ull M = 100007;
    const ull m1 = 1031;
    const ull m2 = 97;

    ull inv1 = modInv(m1, 97);
    ull inv2 = modInv(m2, 1031);

    ull term1 = modMul128(a, m1, M);
    term1 = modMul128(term1, inv1, M);
    ull term2 = modMul128(b, m2, M);
    term2 = modMul128(term2, inv2, M);

    return (term1 + term2) % M;
}

class Solver
{
private:
    int t;
    ull n, m;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> t;
        while (t--)
        {
            std::cin >> n >> m;
            if (n == 0)
            {
                std::cout << (m == 1) << '\n';
                continue;
            }
            if (m == 1)
            {
                std::cout << 0 << '\n';
                continue;
            }

            n -= 1, m -= 2;

            std::cout << crt(lucas(n, m, 97), lucas(n, m, 1031)) << '\n';
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