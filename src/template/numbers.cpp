/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <ranges>
#include <type_traits>
#include <unordered_map>
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
struct Range {
    template <typename Sentinel>
    constexpr auto operator()(Sentinel sentinel) const noexcept {
        return std::views::iota(static_cast<Sentinel>(0), sentinel);
    }
    template <typename Start, typename Sentinel>
    constexpr auto operator()(Start start, Sentinel sentinel) const noexcept {
        return std::views::iota(start, sentinel);
    }
    template <typename Start, typename Sentinel, typename Step>
    constexpr auto operator()(Start start, Sentinel sentinel,
                              Step step) const noexcept {
        return std::views::iota(start, sentinel) | std::views::stride(step);
    }
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
constexpr Range iota{};
#pragma GCC diagnostic pop
}  // namespace

namespace Numbers {
/*
Done
linear sieve
prime test
modular arithmetic

Todo
combinatorics
factorization
extended gcd
chinese remainder theorem
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
inline uint64_t mod_mul(uint64_t lhs, uint64_t rhs, uint64_t mod) {
    return as<uint64_t>((as<uint128_t>(lhs) * rhs) % mod);
}

uint64_t power(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t res = 1;
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
std::pair<int64_t, int64_t> extended_gcd(int64_t a, int64_t b) {
    if (b == 0) {
        return {1, 0};
    }
    auto [x1, y1] = extended_gcd(b, a % b);
    return {y1, x1 - ((a / b) * y1)};
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
    constexpr static int64_t MOD = as<int64_t>(N);
    int64_t value;

    constexpr static bool is_prime_mod = []() {
        if (MOD == 2 || MOD == 3) {
            return true;
        }
        if (MOD % 2 == 0 || MOD % 3 == 0) {
            return false;
        }
        for (int64_t i = 5; i * i <= MOD; i += 6) {
            if (MOD % i == 0 || MOD % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }();

    constexpr static uint128_t BARRETT = (as<uint128_t>(1) << 64) / MOD;

    constexpr static uint64_t reduce(uint128_t x) noexcept {
        if constexpr ((MOD & (MOD - 1)) != 0) {
            uint128_t quotient = (x * BARRETT) >> 64;
            auto remainder = as<uint64_t>(x - (quotient * MOD));
            return remainder < MOD ? remainder : remainder - MOD;
        } else {
            return as<uint64_t>(x & (MOD - 1));
        }
    }

public:
    /*========== Constructors & Destructors ==========*/
    constexpr ModInt() : value(0) {}
    constexpr ~ModInt() = default;
    template <typename U>
        requires std::is_integral_v<U>
    explicit constexpr ModInt(U val) noexcept {
        auto temp_val = as<int128_t>(val);
        if (temp_val < 0) {
            temp_val = (temp_val % MOD + MOD) % MOD;
        } else {
            temp_val %= MOD;
        }
        value = as<int64_t>(temp_val);
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
        uint128_t prod = as<uint128_t>(value) * as<uint64_t>(rhs.value);
        value = as<int64_t>(reduce(prod));
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
bool is_prime(uint64_t n) {
    if (n < 2) {
        return false;
    }
    if (n == 2 || n == 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    static constexpr std::array<uint64_t, 12> bases = {2,  3,  5,  7,  11, 13,
                                                       17, 19, 23, 29, 31, 37};
    uint64_t odd = n - 1;
    while (odd % 2 == 0) {
        odd /= 2;
    }

    for (uint64_t base : bases) {
        if (n == base) {
            return true;
        }
        uint64_t temp = power(base, odd, n);
        uint64_t res = odd;
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
uint64_t convert(uint64_t x, uint64_t n) {
    constexpr static uint64_t constant = 5;
    return mod_mul(x, x, n) + constant;
}

std::pair<uint64_t, uint64_t> pollard_rho(
    uint64_t n, std::unordered_map<uint64_t, int>& factors_set) {
    if (n == 1) {
        return {1, 1};
    }
    if (MillarRabin::is_prime(n)) {
        factors_set[n]++;
        return {n, 1};
    }

    uint64_t x = 0, y = 0, temp = 30, prd = 2, i = 1, q = 0;
    while (temp++ % 40 || std::gcd(prd, n) == 1) {
        if (x == y) {
            x = ++i, y = convert(x, n);
        }
        if ((q = mod_mul(prd, std::max(x, y) - std::min(x, y), n))) {
            prd = q;
        }
        x = convert(x, n), y = convert(convert(y, n), n);
    }

    uint64_t div = std::gcd(prd, n);
    if (div == n) {
        return {1, 1};
    }
    return {div, n / div};
}
auto factorize(uint64_t n) {
    std::unordered_map<uint64_t, int> factors_set;
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
    std::vector<uint64_t> stack;
    stack.push_back(n);
    while (!stack.empty()) {
        uint64_t cur = stack.back();
        stack.pop_back();
        auto [dividend, quotient] = pollard_rho(cur, factors_set);
        if (dividend == 1 && quotient == 1) {
            continue;
        }
        if (dividend != 1) {
            stack.push_back(quotient);
        }
        if (quotient != 1) {
            stack.push_back(dividend);
        }
    }
    return factors_set;
}

auto factorize_ordered(uint64_t n) {
    std::unordered_map<uint64_t, int> factors_set = factorize(n);
    std::vector<std::pair<uint64_t, int>> ordered_factors;
    ordered_factors.reserve(factors_set.size());
    for (const auto& [factor, count] : factors_set) {
        ordered_factors.emplace_back(factor, count);
    }
    std::ranges::sort(ordered_factors);
    return ordered_factors;
}
}  // namespace PollardRho

namespace Combinatorics {
template <auto MOD>
struct Combination {
    static_assert(MOD > 1, "MOD must be >1");
    static constexpr bool is_prime_mod = ::Numbers::ModInt<MOD>::is_prime_mod;
    using mint = ::Numbers::ModInt<MOD>;

    std::vector<mint> fact, inv_fact;
    explicit Combination(size_t n) : fact(n + 1), inv_fact(n + 1) {
        fact[0] = 1;
        for (size_t i = 1; i <= n; ++i) fact[i] = fact[i - 1] * mint(i);
        inv_fact[n] = fact[n].inv();
        for (size_t i = n; i > 0; --i) inv_fact[i - 1] = inv_fact[i] * mint(i);
    }

    mint comb_prime(size_t n, size_t k) const {
        if (k > n) return 0;
        return fact[n] * inv_fact[k] * inv_fact[n - k];
    }

    int64_t comb_composite(size_t n, size_t k) const {
        return comb_mod_composite(n, k, MOD);
    }
};

inline int128_t comb_raw(int n, int k) {
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

inline int64_t comb_mod_prime_power(int64_t n, int64_t k, int64_t p,
                                    int64_t e) {
    int64_t pe = 1;
    for (int i = 0; i < e; ++i) {
        pe *= p;
    }

    auto fact_mod = [&](auto self, int64_t x) -> int64_t {
        if (x == 0) {
            return 1;
        }
        int64_t res = 1;
        for (int64_t i = 1; i < pe; ++i) {
            if (i % p) {
                res = res * i % pe;
            }
        }
        auto r = as<int64_t>(
            power(as<uint64_t>(res), as<uint64_t>(x / pe), as<uint64_t>(pe)));
        for (int64_t i = 1; i <= x % pe; ++i) {
            if (i % p) {
                r = r * i % pe;
            }
        }
        return r * self(self, x / p) % pe;
    };

    auto vp = [&](int64_t x) {
        int64_t cnt = 0;
        while (x) {
            x /= p;
            cnt += x;
        }
        return cnt;
    };
    if (k < 0 || k > n) {
        return 0;
    }

    int64_t exp = vp(n) - vp(k) - vp(n - k);
    int64_t a = fact_mod(fact_mod, n);
    int64_t b = fact_mod(fact_mod, k) * fact_mod(fact_mod, n - k) % pe;

    auto [u, _] = extended_gcd(b, pe);
    int64_t invb = (u % pe + pe) % pe;
    int64_t res = a * invb % pe;
    for (int64_t i = 0; i < exp; ++i) {
        res = res * p % pe;
    }

    return res;
}

inline int64_t comb_mod_composite(int64_t n, int64_t k, int64_t mod) {
    auto facs = ::Numbers::PollardRho::factorize_ordered(as<uint64_t>(mod));
    std::vector<int64_t> rems, mods;
    for (auto [p, e] : facs) {
        rems.push_back(comb_mod_prime_power(n, k, as<int64_t>(p), e));
        int64_t pe = 1;
        for (int i = 0; i < e; ++i) {
            pe *= p;
        }
        mods.push_back(pe);
    }
    return crt(rems, mods);
}

inline int64_t comb(int64_t n, int64_t k, int64_t p) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (::Numbers::MillarRabin::is_prime(as<uint64_t>(p))) {
        static std::vector<int64_t> fact, invf;
        if (fact.size() != as<size_t>(p)) {
            fact.assign(as<size_t>(p), 1);
            for (auto i = 1; i < p; ++i) {
                fact[as<size_t>(i)] = fact[as<size_t>(i - 1)] * i % p;
            }
            invf.resize(as<size_t>(p));
            invf[as<size_t>(p - 1)] = [](int64_t a, int64_t m) {
                int64_t r = 1, e = m - 2;
                while (e) {
                    if (e & 1) {
                        r = r * a % m;
                    }
                    a = a * a % m;
                    e >>= 1;
                }
                return r;
            }(fact[as<size_t>(p - 1)], p);
            for (auto i = p - 1; i > 0; --i) {
                invf[as<size_t>(i - 1)] = invf[as<size_t>(i)] * i % p;
            }
        }
        auto Csmall = [&](int ni, int ki) {
            return fact[as<size_t>(ni)] * invf[as<size_t>(ki)] % p *
                   invf[as<size_t>(ni - ki)] % p;
        };
        std::function<int64_t(int64_t, int64_t)> lucas = [&](int64_t N,
                                                             int64_t K) {
            if (K == 0) {
                return int64_t{1};
            }
            int64_t ni = N % p, ki = K % p;
            if (ki > ni) {
                return int64_t{0};
            }
            return lucas(N / p, K / p) * Csmall(as<int>(ni), as<int>(ki)) % p;
        };
        return lucas(n, k);
    }
    return comb_mod_composite(n, k, p);
}

template <int64_t MOD = 0>
auto comb(int n, int k, int64_t mod_arg = MOD)
    -> std::conditional_t<MOD == 0, int128_t, int64_t> {
    if constexpr (MOD != 0) {
        static Combination<MOD> Comb(/* max_n */ 1000000);
        if constexpr (::Numbers::ModInt<MOD>::is_prime_mod) {
            return Comb.comb_prime(n, k).value;
        } else {
            return Comb.comb_composite(n, k);
        }
    } else {
        return (mod_arg == 0) ? comb_raw(n, k)
                              : comb_mod_composite(n, k, mod_arg);
    }
}

}  // namespace Combinatorics
}  // namespace Numbers

class Solver {
    int64_t n = 0, k = 0, t = 0;
    constexpr static int64_t MOD = 142857;

public:
    void solve() {
        cin >> t;
        while (t--) {
            cin >> n >> k;
            cout << Numbers::Combinatorics::comb(n, k, MOD) << '\n';
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
