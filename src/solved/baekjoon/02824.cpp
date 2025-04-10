#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

using std::cin, std::cout, std::endl;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                         \
    cout.tie(NULL);

class Solver {
private:
    bool sky;
    int n, temp;
    int const MAX = 1 << 17;
    int const LIM = 1'000'000'000;

    std::vector<int> primes;
    std::vector<bool> is_prime;

    std::unordered_map<ll, int> a_factor;
    std::unordered_map<ll, int> b_factor;

    void sieve() {
        is_prime.assign(MAX, true);
        for (int i : std::views::iota(2, MAX)) {
            if (is_prime.at(i)) primes.emplace_back(i);
            for (auto& j : primes) {
                if (i * j >= MAX) break;
                is_prime.at(i * j) = false;
                if (i % j == 0) break;
            }
        }
    }

public:
    Solver() {}
    ~Solver() {}
    void solve() {
        sky = false;
        sieve();
        cin >> n;
        while (n--) {
            cin >> temp;
            for (auto& p : primes) {
                while (temp % p == 0) {
                    temp /= p;
                    a_factor[p]++;
                }
            }
            if (temp != 1) a_factor[temp]++;
        }
        cin >> n;
        while (n--) {
            cin >> temp;
            for (auto& p : primes) {
                while (temp % p == 0) {
                    temp /= p;
                    b_factor[p]++;
                }
            }
            if (temp != 1) b_factor[temp]++;
        }
        ll ans = 1;
        for (auto const& [p, r] : a_factor) {
            if (b_factor.contains(p)) {
                while (a_factor[p] > 0 && b_factor[p] > 0) {
                    ans *= p;
                    if (ans >= LIM) {
                        sky = true;
                        ans %= LIM;
                    }
                    a_factor[p]--, b_factor[p]--;
                }
            }
        }
        if (sky)
            std::print("{0:0>9}", ans % LIM);
        else
            std::print("{}", ans);
    }
};

int main() {
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}
