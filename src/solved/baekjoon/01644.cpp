#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                    \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

const int MAX = 4'000'100;

class Solver
{
private:
    int n;
    std::vector<int> prime;
    std::vector<int> minPrime;

    void sieve()
    {
        minPrime[1] = 1;
        for (int i = 2; i < MAX; i++)
        {
            if (minPrime[i] == 0)
            {
                prime.push_back(i);
                minPrime[i] = i;
            }
            for (auto &p : prime)
            {
                if (p > minPrime[i] || (ll)i * p >= MAX)
                    break;
                minPrime[i * p] = p;
                if (i % p == 0)
                    break;
            }
        }
        minPrime[1] = 0;
    }

public:
    Solver()
    {
        minPrime.assign(MAX, 0);
    }
    ~Solver() {}
    
    void solve()
    {
        sieve();
        std::cin >> n;
        int l = 0, r = 0;
        int cnt = 0, sum = 0;
        if (minPrime[n] == n)
            cnt++;
        while (l <= r)
        {
            if (r == prime.size() || prime[r] > n)
                break;

            if (sum < n)
                sum += prime[r++];
            else if (sum > n)
                sum -= prime[l++];
            else
            {
                cnt++;
                sum -= prime[l++];
            }
        }
        std::cout << cnt;
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}