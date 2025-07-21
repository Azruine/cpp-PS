/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <utility>
#include <vector>

using std::cin, std::cout;

namespace {
inline void fastio() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

namespace sieve {
template <typename T>
    requires std::is_integral_v<T>
class LinearSieve {
public:
    explicit LinearSieve(T n) : is_prime(n + 1, true), min_factor(n + 1, 0) {
        is_prime[0] = is_prime[1] = false;
        for (T i = 2; i <= n; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
                min_factor[i] = i;
            }
            for (const T& prime : primes) {
                if (prime * i > n || prime > min_factor[i]) {
                    break;
                }
                is_prime[prime * i] = false;
                min_factor[prime * i] = prime;
            }
        }
    }
    std::vector<T> const& get_primes() const { return primes; }
    std::vector<bool> const& get_is_prime() const { return is_prime; }
    std::vector<T> const& get_min_factor() const { return min_factor; }

private:
    std::vector<T> primes;
    std::vector<bool> is_prime;
    std::vector<T> min_factor;
};
};  // namespace sieve

class Solver {
public:
    void solve() {
        cin >> n >> m;
        auto primes = linear_sieve.get_is_prime();
        acc_primes.resize(MAX + 1, 0);
        acc_primes[1] = 1;
        for (size_t i = 2; i <= MAX; i++) {
            acc_primes[i] = acc_primes[i - 1] + as<size_t>(primes[i]);
        }
        while (cin >> a >> b) {
            cout << acc_primes[b] - acc_primes[a - 1] << '\n';
        }
    }

private:
    constexpr static size_t MAX = 5'000'010;
    size_t n = 0, m = 0, a = 0, b = 0;
    sieve::LinearSieve<size_t> linear_sieve{MAX};
    std::vector<size_t> acc_primes;
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
