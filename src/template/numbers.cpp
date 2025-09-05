/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Numbers {
/*
Done
linear sieve
prime test
modular arithmetic
combinatorics
factorization
extended gcd
chinese remainder theorem

Todo
number theoretic transform
discrete logarithm
Möbius function
Euler's totient function
Tonelli Shanks algorithm
Dirichlet convolution
Legendre symbol
Lucas theorem
Fermat's little theorem
Garner's algorithm
Meissel Lehmer algorithm
Berlekamp Massey algorithm
*/
// 128 bit integers
using int128_t = __int128_t;
using uint128_t = __uint128_t;
namespace {
/*========== Helper Functions ==========*/
inline int64_t mod_mul(int64_t lhs, int64_t rhs, int64_t mod) {
    return static_cast<int64_t>((static_cast<int128_t>(lhs) * rhs) % mod);
}

int64_t power(int64_t base, int64_t exp, int64_t mod) {
    int64_t res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = mod_mul(base, res, mod);
        }
        base = mod_mul(base, base, mod);
        exp /= 2;
    }
    return res;
}
}  // namespace

/*========== Extended Euclidian Algorithm ==========*/
std::pair<int64_t, int64_t> extended_gcd(int64_t lhs, int64_t rhs) {
    if (rhs == 0) {
        return {1, 0};
    }
    auto [x1, y1] = extended_gcd(rhs, lhs % rhs);
    return {y1, x1 - ((lhs / rhs) * y1)};
}

/*========== Chinese Remainder Theorem ==========*/
int64_t crt(std::vector<int64_t> const& rems,
            std::vector<int64_t> const& mods) {
    assert(rems.size() == mods.size() &&
           "Remainders and moduli must have the same size");
    int64_t prod = 1;
    for (auto const& mod : mods) {
        prod *= mod;
    }
    int64_t result = 0;
    for (size_t i = 0; i < rems.size(); i++) {
        int64_t ni = prod / mods[i];
        auto [u, _] = extended_gcd(ni, mods[i]);
        int64_t inv = (u % mods[i] + mods[i]) % mods[i];
        result += rems[i] * inv * ni;
    }
    return result % prod;
}

/*========== Linear Sieve ==========*/
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

/*========== Modular Arithmetic ==========*/
template <std::integral auto const N>
    requires(N > 1)
class ModInt {
    static_assert(N <= std::numeric_limits<int64_t>::max(),
                  "N is too large for ModInt");
    constexpr static int64_t MOD = static_cast<int64_t>(N);
    int64_t value;

    constexpr static bool is_prime_mod = []() constexpr {
        if constexpr (MOD == 2 || MOD == 3) {
            return true;
        }
        if constexpr (MOD % 2 == 0 || MOD % 3 == 0) {
            return false;
        }
        for (int64_t i = 5; i * i <= MOD; i += 6) {
            if (MOD % i == 0 || MOD % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }();

    constexpr static int128_t BARRETT = (static_cast<int128_t>(1) << 64) / MOD;

    constexpr static int64_t reduce(int128_t x) noexcept {
        if constexpr ((MOD & (MOD - 1)) != 0) {
            int128_t quotient = (x * BARRETT) >> 64;
            auto remainder = static_cast<int64_t>(x - (quotient * MOD));
            return remainder < MOD ? remainder : remainder - MOD;
        } else {
            return static_cast<int64_t>(x & (MOD - 1));
        }
    }

public:
    /*========== Constructors & Destructors ==========*/
    constexpr ModInt() : value(0) {}
    constexpr ~ModInt() = default;
    template <typename U>
        requires std::is_integral_v<U>
    explicit constexpr ModInt(U val) noexcept {
        auto temp_val = static_cast<int128_t>(val);
        if (temp_val < 0) {
            temp_val = (temp_val % MOD + MOD) % MOD;
        } else {
            temp_val %= MOD;
        }
        value = static_cast<int64_t>(temp_val);
    }
    constexpr ModInt(ModInt const&) = default;
    constexpr ModInt& operator=(ModInt const&) = default;
    constexpr ModInt(ModInt&&) = default;
    constexpr ModInt& operator=(ModInt&&) = default;

    /*========== Static Helper Methods ==========*/
    static constexpr ModInt zero() noexcept { return ModInt(0); }
    static constexpr ModInt one() noexcept { return ModInt(1); }

    /*========== Boolean Operators ==========*/
    constexpr bool operator==(ModInt const& rhs) const noexcept = default;
    constexpr auto operator<=>(ModInt const& rhs) const noexcept = default;
    explicit constexpr operator bool() const noexcept { return value != 0; }

    /*========== Arithmetic Operators ==========*/
    constexpr ModInt& operator+=(ModInt const& rhs) noexcept {
        int64_t tmp = value + rhs.value;
        if (tmp >= MOD) {
            tmp -= MOD;
        }
        value = tmp;
        return *this;
    }
    constexpr ModInt& operator-=(ModInt const& rhs) noexcept {
        int64_t tmp = value - rhs.value;
        if (tmp < 0) {
            tmp += MOD;
        }
        value = tmp;
        return *this;
    }
    constexpr ModInt& operator*=(ModInt const& rhs) noexcept {
        int128_t prod =
            static_cast<int128_t>(value) * static_cast<int128_t>(rhs.value);
        value = reduce(prod);
        return *this;
    }
    constexpr ModInt& operator/=(ModInt const& rhs) {
        assert(rhs.value != 0 && "Division by zero in ModInt");
        *this = *this * rhs.inv();
        return *this;
    }

    // ModInt ⊕ ModInt
    friend constexpr ModInt operator+(ModInt lhs, ModInt const& rhs) noexcept {
        lhs += rhs;
        return lhs;
    }
    friend constexpr ModInt operator-(ModInt lhs, ModInt const& rhs) noexcept {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr ModInt operator*(ModInt lhs, ModInt const& rhs) noexcept {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr ModInt operator/(ModInt lhs, ModInt const& rhs) {
        lhs /= rhs;
        return lhs;
    }

    // ModInt ⊕ integral
    template <std::integral U>
    friend constexpr ModInt operator+(ModInt lhs, U rhs) noexcept {
        lhs += ModInt(rhs);
        return lhs;
    }
    template <std::integral U>
    friend constexpr ModInt operator-(ModInt lhs, U rhs) noexcept {
        lhs -= ModInt(rhs);
        return lhs;
    }
    template <std::integral U>
    friend constexpr ModInt operator*(ModInt lhs, U rhs) noexcept {
        lhs *= ModInt(rhs);
        return lhs;
    }
    template <std::integral U>
    friend constexpr ModInt operator/(ModInt lhs, U rhs) {
        lhs /= ModInt(rhs);
        return lhs;
    }

    // integral ⊕ ModInt
    template <std::integral U>
    friend constexpr ModInt operator+(U lhs, ModInt rhs) noexcept {
        return ModInt(lhs) + rhs;
    }
    template <std::integral U>
    friend constexpr ModInt operator-(U lhs, ModInt rhs) noexcept {
        return ModInt(lhs) - rhs;
    }
    template <std::integral U>
    friend constexpr ModInt operator*(U lhs, ModInt rhs) noexcept {
        return ModInt(lhs) * rhs;
    }
    template <std::integral U>
    friend constexpr ModInt operator/(U lhs, ModInt rhs) {
        return ModInt(lhs) / rhs;
    }

    // Increment and Decrement Operators
    constexpr ModInt& operator++() noexcept { return *this += 1; }
    constexpr ModInt operator++(int) noexcept {
        auto temp = *this;
        *this += 1;
        return temp;
    }
    constexpr ModInt& operator--() noexcept { return *this -= 1; }
    constexpr ModInt operator--(int) noexcept {
        auto temp = *this;
        *this -= 1;
        return temp;
    }

    /*========== Inverse and Power ==========*/
    constexpr ModInt inv() const noexcept {
        assert(std::gcd(value, MOD) == 1 && "Inverse does not exist");
        assert(value != 0 && "Cannot compute inverse of zero in ModInt");
        if (is_prime_mod) {
            return pow(MOD - 2);
        }
        int64_t remainder = value;
        int64_t modulus = MOD;
        int64_t prev = 0;
        int64_t curr = 1;
        while (modulus != 0) {
            int64_t quotient = remainder / modulus;
            int64_t temp = modulus;
            modulus = remainder % modulus;
            remainder = temp;
            temp = prev;
            prev = curr - quotient * prev;
            curr = temp;
        }
        if (curr < 0) {
            curr += MOD;
        }
        curr %= MOD;
        assert(curr < MOD && "Inverse is out of bounds");
        return ModInt(curr);
    }

    template <std::integral U>
    constexpr ModInt pow(U exponent) const noexcept {
        if (exponent == 0) {
            return ModInt(1);
        }
        if (exponent < 0) {
            assert(value != 0 && "Cannot raise zero to a negative exponent");
            return inv().pow(-exponent);
        }
        ModInt result(1);
        ModInt base = *this;
        while (exponent > 0) {
            if (exponent & 1) {
                result *= base;
            }
            base *= base;
            exponent >>= 1;
        }
        return result;
    }

    /*=========== iostream operator overloading ==========*/
    friend std::istream& operator>>(std::istream& is, ModInt& mod_int) {
        int64_t temp = 0;
        is >> temp;
        mod_int = ModInt(temp);
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, ModInt const& mod_int) {
        os << mod_int.value;
        return os;
    }
};  // class ModInt

namespace MillarRabin {
/*========== Millar Rabin ==========*/
bool is_prime(int64_t n) {
    if (n < 2) {
        return false;
    }
    if (n == 2 || n == 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    static constexpr std::array<int64_t, 12> bases = {2,  3,  5,  7,  11, 13,
                                                      17, 19, 23, 29, 31, 37};
    int64_t odd = n - 1;
    while (odd % 2 == 0) {
        odd /= 2;
    }

    for (int64_t base : bases) {
        if (n == base) {
            return true;
        }
        int64_t temp = power(base, odd, n);
        int64_t res = odd;
        while (temp != 1 && temp != n - 1 && res != n - 1) {
            temp = mod_mul(temp, temp, n);
            res *= 2;
        }
        if (temp != n - 1 && res % 2 == 0) {
            return false;
        }
    }
    return true;
}
}  // namespace MillarRabin

namespace PollardRho {
int64_t convert(int64_t x, int64_t n) {
    constexpr static int64_t constant = 5;
    return mod_mul(x, x, n) + constant;
}

std::pair<int64_t, int64_t> pollard_rho(
    int64_t n, std::unordered_map<int64_t, int>& factors_set) {
    if (n == 1) {
        return {1, 1};
    }
    if (MillarRabin::is_prime(n)) {
        factors_set[n]++;
        return {n, 1};
    }

    int64_t x = 0, y = 0, temp = 30, prd = 2, i = 1, q = 0;
    while (temp++ % 40 || std::gcd(prd, n) == 1) {
        if (x == y) {
            x = ++i, y = convert(x, n);
        }
        if ((q = mod_mul(prd, std::max(x, y) - std::min(x, y), n))) {
            prd = q;
        }
        x = convert(x, n), y = convert(convert(y, n), n);
    }

    int64_t div = std::gcd(prd, n);
    if (div == n) {
        return {1, 1};
    }
    return {div, n / div};
}
auto factorize(int64_t n) {
    std::unordered_map<int64_t, int> factors_set;
    if (n == 1) {
        return factors_set;
    }
    if (MillarRabin::is_prime(n)) {
        factors_set[n]++;
        return factors_set;
    }

    while (n % 2 == 0) {
        factors_set[2]++;
        n /= 2;
    }
    while (n % 3 == 0) {
        factors_set[3]++;
        n /= 3;
    }
    std::vector<int64_t> stack;
    stack.push_back(n);
    while (!stack.empty()) {
        int64_t cur = stack.back();
        stack.pop_back();
        if (cur == 1) {
            continue;
        }
        auto [dividend, quotient] = pollard_rho(cur, factors_set);
        if (dividend != 1) {
            stack.push_back(quotient);
        }
        if (quotient != 1) {
            stack.push_back(dividend);
        }
    }
    return factors_set;
}

auto factorize_ordered(int64_t n) {
    std::unordered_map<int64_t, int> factors_set = factorize(n);
    std::vector<std::pair<int64_t, int>> ordered_factors;
    ordered_factors.reserve(factors_set.size());
    for (const auto& [factor, count] : factors_set) {
        ordered_factors.emplace_back(factor, count);
    }
    std::ranges::sort(ordered_factors);
    return ordered_factors;
}
}  // namespace PollardRho

namespace Combinatorics {
template <std::integral auto const MOD = 0>
class Combination {
    static_assert(MOD >= 0, "MOD must be non-negative");

    using mint = ::Numbers::ModInt<MOD>;
    std::vector<mint> fact, inv_fact;

    constexpr static bool is_prime_mod = []() constexpr {
        if constexpr (MOD == 2 || MOD == 3) {
            return true;
        }
        if constexpr (MOD % 2 == 0 || MOD % 3 == 0) {
            return false;
        }
        for (int64_t i = 5; i * i <= MOD; i += 6) {
            if (MOD % i == 0 || MOD % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }();

    static int128_t nCr_raw(int64_t n, int64_t k) {
        if (k < 0 || k > n) {
            return 0;
        }
        k = std::min(k, n - k);
        int128_t res = 1;
        for (int i = 1; i <= k; ++i) {
            res = res * (n - k + i) / i;
        }
        return res;
    }

    mint nCr_small(int64_t n, int64_t k) const {
        if (k < 0 || k > n) {
            return mint(0);
        }
        if (!fact.empty() && static_cast<size_t>(n) < fact.size()) {
            return fact[static_cast<size_t>(n)] *
                   inv_fact[static_cast<size_t>(k)] *
                   inv_fact[static_cast<size_t>(n - k)];
        }
        if (k > n / 2) {
            k = n - k;
        }
        mint res(1);
        for (int64_t i = 1; i <= k; ++i) {
            res = res * (n - i + 1) / i;
        }
        return res;
    }

    mint nCr_lucas(int64_t n, int64_t k) const {
        if (k < 0 || k > n) {
            return mint(0);
        }
        if (k == 0) {
            return mint(1);
        }
        return nCr_lucas(n / MOD, k / MOD) * nCr_small(n % MOD, k % MOD);
    }

    static int64_t nCr_prime_power(int64_t n, int64_t k, int64_t prime,
                                   int64_t exponent) {
        int64_t mod_pe = 1;
        for (int i = 0; i < exponent; ++i) {
            mod_pe *= prime;
        }

        auto count_p = [&](int64_t num) {
            int64_t count = 0;
            while (num > 0) {
                num /= prime;
                count += num;
            }
            return count;
        };

        if (count_p(n) - count_p(k) - count_p(n - k) >= exponent) {
            return 0;
        }

        auto fact_mod = [&](auto self, int64_t num) -> int64_t {
            if (num == 0) {
                return 1;
            }
            int64_t res = 1;
            for (int64_t i = 1; i < mod_pe; ++i) {
                if (i % prime) {
                    res = mod_mul(res, i, mod_pe);
                }
            }
            res = power(res, num / mod_pe, mod_pe);
            for (int64_t i = 1; i <= num % mod_pe; ++i) {
                if (i % prime) {
                    res = mod_mul(res, i, mod_pe);
                }
            }
            return mod_mul(res, self(self, num / prime), mod_pe);
        };

        int64_t num_val = fact_mod(fact_mod, n);
        int64_t den1_val = fact_mod(fact_mod, k);
        int64_t den2_val = fact_mod(fact_mod, n - k);

        int64_t p_exp = count_p(n) - count_p(k) - count_p(n - k);

        int64_t phi = 1;
        for (int i = 0; i < exponent - 1; ++i) {
            phi *= prime;
        }
        phi *= (prime - 1);

        int64_t den_inv =
            power(mod_mul(den1_val, den2_val, mod_pe), phi - 1, mod_pe);

        int64_t res = mod_mul(num_val, den_inv, mod_pe);
        res = mod_mul(res, power(prime, p_exp, mod_pe), mod_pe);
        return res;
    }

    static int64_t nCr_composite(int64_t n, int64_t k, int64_t m) {
        if (k < 0 || k > n) {
            return 0;
        }
        auto factors = PollardRho::factorize_ordered(m);
        std::vector<int64_t> rems;
        std::vector<int64_t> mods;
        for (auto [p, e] : factors) {
            int64_t mod_pe = 1;
            for (int i = 0; i < e; ++i) {
                mod_pe *= p;
            }
            rems.push_back(nCr_prime_power(n, k, p, e));
            mods.push_back(mod_pe);
        }
        return crt(rems, mods);
    }

public:
    explicit Combination(size_t max_n = 0) {
        if constexpr (is_prime_mod) {
            if (max_n == 0) {
                return;
            }
            fact.resize(max_n + 1);
            inv_fact.resize(max_n + 1);
            fact[0] = mint(1);
            for (size_t i = 1; i <= max_n; ++i) {
                fact[i] = fact[i - 1] * mint(i);
            }
            inv_fact[max_n] = fact[max_n].inv();
            for (size_t i = max_n; i > 0; --i) {
                inv_fact[i - 1] = inv_fact[i] * mint(i);
            }
        }
    }

    auto nCr(int64_t n, int64_t k) const {
        if constexpr (MOD == 0) {
            return nCr_raw(n, k);
        } else {
            if (k < 0 || k > n) {
                return mint(0);
            }

            if (!fact.empty() && static_cast<size_t>(n) < fact.size()) {
                return fact[static_cast<size_t>(n)] *
                       inv_fact[static_cast<size_t>(k)] *
                       inv_fact[static_cast<size_t>(n - k)];
            }

            if constexpr (is_prime_mod) {
                return nCr_lucas(n, k);
            } else {
                return mint(nCr_composite(n, k, MOD));
            }
        }
    }

    static int64_t nCr(int64_t n, int64_t k, int64_t m) {
        return nCr_composite(n, k, m);
    }
};
}  // namespace Combinatorics
}  // namespace Numbers
