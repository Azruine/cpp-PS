/*==== Copyright 2025 Azruine ====*/

#include <vector>

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
