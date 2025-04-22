/*==== Copyright 2025 Azruine ====*/

#include <array>
#include <cstdint>
#include <print>
#include <ranges>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
private:
    static const uint64_t MOD{1'000'000'007};
    static const uint64_t MAX{10'110};

    std::array<bool, MAX> is_prime{};
    std::array<uint64_t, MAX> min_prime{};
    std::array<uint64_t, MAX> factorial{};
    std::vector<uint64_t> primes;

    void sieve() {
        is_prime.fill(true);
        is_prime[0] = is_prime[1] = false;
        for (auto i = uint64_t{2}; i < MAX; ++i) {
            if (is_prime.at(i)) {
                primes.push_back(i);
                min_prime.at(i) = i;
            }
            for (const auto& prime : primes) {
                if (prime * i >= MAX) {
                    break;
                }
                is_prime.at(prime * i) = false;
                min_prime.at(prime * i) = prime;
                if (i % prime == 0) {
                    break;
                }
            }
        }
    }
    void factorials() {
        factorial[0] = 1;
        for (auto i = uint64_t{1}; i < MAX; ++i) {
            factorial.at(i) = (factorial.at(i - 1) * i) % MOD;
        }
    }
    static uint64_t mod_pow(uint64_t base, uint64_t exponent) {
        uint64_t result = 1;
        while (exponent > 0) {
            if (exponent & 1) {
                result = (result * base) % MOD;
            }
            base = (base * base) % MOD;
            exponent >>= 1;
        }
        return result;
    }
    static uint64_t mod_inverse(uint64_t value) {
        return mod_pow(value, MOD - 2);
    }
    uint64_t nCk(uint64_t n, uint64_t k) {
        if (k > n) {
            return 0;
        }
        if (k == 0 || k == n) {
            return 1;
        }
        auto numerator = factorial.at(n);
        auto denominator = (factorial.at(k) * factorial.at(n - k)) % MOD;
        return (numerator * mod_inverse(denominator)) % MOD;
    }

public:
    int idealArrays(int n, int maxValue) {
        sieve();
        factorials();
        std::array<uint64_t, MAX> data{};
        data.fill(0);
        std::unordered_map<uint64_t, uint64_t> factors;
        uint64_t result = 1;
        for (auto i :
             std::views::iota(uint64_t{2}, as<uint64_t>(maxValue) + 1)) {
            factors.clear();
            auto num = i;
            while (num > 1) {
                auto prime = min_prime.at(num);
                factors[prime]++;
                num /= prime;
            }
            data.at(i) = 1;
            for (const auto& [prime, exp] : factors) {
                auto nHk = nCk(as<uint64_t>(n) - 1 + exp, exp);
                data.at(i) = (data.at(i) * nHk) % MOD;
            }
            result = (result + data.at(i)) % MOD;
        }
        return as<int>(result);
    }
};
