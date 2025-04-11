#include <bits/stdc++.h>

using ll = int64_t;
using ull = uint64_t;
using ld = long double;

using std::cin, std::cout;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                         \
    cout.tie(NULL);

namespace {
template <typename To, typename From>
inline To as(From value) {
    return static_cast<To>(value);
}

}  // namespace

class Solver {
private:
    int t = 0, n = 0;

    static int constexpr MAX = 10'010;

    std::vector<int> primes;
    std::vector<bool> is_prime;

    void sieve() {
        is_prime.assign(MAX, true);
        for (auto i : std::views::iota(2, MAX)) {
            if (is_prime[as<size_t>(i)]) {
                primes.push_back(i);
            }
            for (auto& j : primes) {
                if (i * j >= MAX) {
                    break;
                }
                is_prime[as<size_t>(i * j)] = false;
                if (i % j == 0) {
                    break;
                }
            }
        }
    }

public:
    void solve() {
        sieve();
        cin >> t;
        while (cin >> n) {
            int x = n / 2;
            while (!is_prime[as<size_t>(x)] || !is_prime[as<size_t>(n - x)]) {
                x--;
            }
            std::print("{} {}\n", x, n - x);
        }
    }
};

int main() {
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}