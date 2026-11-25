/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <utility>

using std::cin, std::cout;

namespace {
constexpr size_t MAX_SIZE = 1 << 8;
constexpr int32_t MAX = 1'000'010;
constexpr int32_t PRIME_LIM = 1'001;
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

#include <bitset>
#include <cmath>
#include <optional>
#include <print>
#include <unordered_map>
#include <vector>

namespace sieve {
template <typename T>
    requires std::is_integral_v<T>
class LinearSieve {
public:
    explicit LinearSieve(T n)
        : is_prime(n + 1, true), min_factor(n + 1, 0), prime_idx(n + 1, -1) {
        is_prime[0] = is_prime[1] = false;
        for (T i = 2; i <= n; i++) {
            if (is_prime[i]) {
                prime_idx[i] = as<T>(primes.size());
                primes.emplace_back(i);
                min_factor[i] = i;
            }
            for (T const& prime : primes) {
                if (prime > n / i || prime > min_factor[i]) {
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
    std::vector<T> const& get_prime_idx() const { return prime_idx; }

private:
    std::vector<T> primes;
    std::vector<bool> is_prime;
    std::vector<T> min_factor;
    std::vector<T> prime_idx;
};
}  // namespace sieve

class XorBasis {
    std::array<std::bitset<MAX_SIZE>, MAX_SIZE> matrix{};
    std::array<bool, MAX_SIZE> has_pivot{};

public:
    bool insert(std::bitset<MAX_SIZE> bitset) {
        for (size_t i = MAX_SIZE - 1; i < MAX_SIZE; i--) {
            if (!bitset.test(i)) {
                continue;
            }
            if (!has_pivot[i]) {
                matrix[i] = bitset;
                has_pivot[i] = true;
                return true;
            }
            bitset ^= matrix[i];
        }
        return false;
    }

    bool contains(std::bitset<MAX_SIZE> bitset) const {
        for (size_t i = MAX_SIZE - 1; i < MAX_SIZE; i--) {
            if (bitset.test(i) && has_pivot[i]) {
                bitset ^= matrix[i];
            }
        }
        return bitset.none();
    }
};

class Solver {
    sieve::LinearSieve<int32_t> sieve{MAX};

    static bool is_square(int32_t x) {
        auto sqrt = as<int64_t>(std::sqrt(x));
        while (sqrt * sqrt < x) {
            sqrt += 1;
        }
        while (sqrt * sqrt > x) {
            sqrt -= 1;
        }
        return sqrt * sqrt == x;
    }

    struct PrimeProfile {
        using Rep = std::unordered_map<int32_t, PrimeProfile>;
        std::bitset<MAX_SIZE> little_parts;
        int32_t big_parts = 0;
    };
    using BigPartsRep = PrimeProfile::Rep;
    PrimeProfile make_profile(int32_t n) const {
        PrimeProfile ret;
        auto const& min_factor = sieve.get_min_factor();
        auto const& prime_idx = sieve.get_prime_idx();
        while (n > 1) {
            auto prime = min_factor[n];
            auto cnt = 0;
            while (n % prime == 0) {
                n /= prime;
                cnt += 1;
            }
            if (cnt & 1) {
                if (prime < PRIME_LIM) {
                    ret.little_parts.set(prime_idx[prime]);
                } else {
                    ret.big_parts = prime;
                }
            }
        }
        return ret;
    }

    std::optional<std::bitset<MAX_SIZE>> reduce_target(
        PrimeProfile const& profile_x, PrimeProfile const& profile_y,
        BigPartsRep const& big_rep) const {
        auto target = profile_x.little_parts ^ profile_y.little_parts;
        auto absorb = [&](int32_t pivot) {
            if (pivot == 0) {
                return true;
            }
            auto it = big_rep.find(pivot);
            if (it == big_rep.end()) {
                return false;
            }
            target ^= it->second.little_parts;
            return true;
        };

        if (profile_x.big_parts != profile_y.big_parts) {
            if (!absorb(profile_x.big_parts)) {
                return std::nullopt;
            }
            if (!absorb(profile_y.big_parts)) {
                return std::nullopt;
            }
        }
        return target;
    }

    int32_t find_preimage(int32_t y) const {
        if (y > 1 && sieve.get_is_prime()[y]) {
            return -1;
        }
        if (is_square(y)) {
            return y;
        }

        auto profile_y = make_profile(y);
        XorBasis basis;
        BigPartsRep big_rep;

        for (int32_t x = y - 1; x >= 1; x--) {
            auto profile_x = make_profile(x);
            auto target_opt = reduce_target(profile_x, profile_y, big_rep);
            if (target_opt && basis.contains(target_opt.value())) {
                return x;
            }
            if (profile_x.big_parts == 0) {
                basis.insert(profile_x.little_parts);
            } else {
                auto it = big_rep.find(profile_x.big_parts);
                if (it == big_rep.end()) {
                    big_rep[profile_x.big_parts] = profile_x;
                } else {
                    basis.insert(profile_x.little_parts
                                 ^ it->second.little_parts);
                    (*it).second = profile_x;
                }
            }
        }
        return -1;
    }

public:
    void solve() {
        int32_t y = 0;
        cin >> y;
        auto res = find_preimage(y);
        if (res == -1) {
            std::println("0");
        } else {
            std::println("1\n{}", res);
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
