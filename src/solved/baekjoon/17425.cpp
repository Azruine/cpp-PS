#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

ll power(ll a, ll r)
{
    if (a == 1 || r == 0)
        return 1;
    ll ret = 1;
    while (r > 0)
    {
        if (r & 1)
            ret *= a;
        r >>= 1;
        a *= a;
    }
    return ret;
}

class Solver
{
private:
    int n, t;
    std::vector<int> minPrime;
    std::vector<int> primes;
    std::vector<ll> sum;
    std::vector<ll> cumulative;
    std::vector<int> c;

    void sieve()
    {
        const int MAX = 1'000'010;
        minPrime.assign(MAX, -1);
        sum.assign(MAX, 0);
        c.assign(MAX, 0);
        cumulative.assign(MAX, 0);

        sum[1] = 1;
        minPrime[1] = 1;
        cumulative[1] = 1;
        for (int i = 2; i < MAX; i++)
        {
            if (minPrime[i] == -1)
            {
                primes.emplace_back(i);
                minPrime[i] = i;
                c[i] = 1;

                sum[i] = i + 1;
            }
            for (int &p : primes)
            {
                ll x = (ll)i * p;
                if (x > MAX)
                    break;
                minPrime[x] = p;

                if (i % p == 0)
                {
                    c[x] = c[i] + 1;

                    sum[x] = sum[i] * (power(p, c[i] + 2) - 1) / (power(p, c[i] + 1) - 1);
                    break;
                }
                c[x] = 1;
                sum[x] = sum[i] * sum[p];
            }
            cumulative[i] += cumulative[i - 1] + sum[i];
        }
    }

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        sieve();
        std::cin >> t;
        while (std::cin >> n)
            std::cout << cumulative[n] << '\n';
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}