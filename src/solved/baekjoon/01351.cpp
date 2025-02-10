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
    ll n, p, q;
    std::unordered_map<ll, ll> db;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n >> p >> q;
        db[0] = 1;
        std::function<ll(ll)> getAns = [&](ll n){
            if (db.contains(n))
                return db[n];
            else
                return db[n] = getAns(n / p) + getAns(n / q);
        };
        std::cout << getAns(n);
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}