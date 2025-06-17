/*==== Copyright 2025 Azruine ====*/

#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From &&from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

// MOD for modular arithmetic
// INV for precalculated modular inverse
constexpr unsigned int MOD = 1'000'000'007;
std::array<int, 10> INV = {0,           1,           500'000'004, 333'333'336,
                           250'000'002, 400'000'003, 166'666'668, 142'857'144,
                           125'000'001, 111'111'112};

// Modular int struct
template <unsigned M_>
struct ModInt {
    static constexpr unsigned M = M_;
    unsigned x;

    // Constructors
    constexpr ModInt() : x(0U) {}
    constexpr ModInt(unsigned int x_) : x(x_ % M) {}
    constexpr ModInt(uint64_t x_) : x(x_ % M) {}
    constexpr ModInt(int x_)
        : x(((x_ %= static_cast<int>(M)) < 0) ? (x_ + static_cast<int>(M))
                                              : x_) {}
    constexpr ModInt(int64_t x_)
        : x(((x_ %= static_cast<long long>(M)) < 0)
                ? (x_ + static_cast<int64_t>(M))
                : x_) {}
    constexpr ModInt(__int128_t x) : x(x % M) {}

    // Operators
    ModInt &operator+=(const ModInt &a) {
        x = ((x += a.x) >= M) ? (x - M) : x;
        return *this;
    }
    ModInt &operator-=(const ModInt &a) {
        x = ((x -= a.x) >= M) ? (x + M) : x;
        return *this;
    }
    ModInt &operator*=(const ModInt &a) {
        x = (static_cast<unsigned long long>(x) * a.x) % M;
        return *this;
    }
    ModInt &operator/=(const ModInt &a) { return (*this *= a.inv()); }
    ModInt operator+() const { return *this; }
    ModInt operator-() const {
        ModInt a;
        a.x = x ? (M - x) : 0U;
        return a;
    }
    ModInt operator+(const ModInt &a) const { return (ModInt(*this) += a); }
    ModInt operator-(const ModInt &a) const { return (ModInt(*this) -= a); }
    ModInt operator*(const ModInt &a) const { return (ModInt(*this) *= a); }
    ModInt operator/(const ModInt &a) const { return (ModInt(*this) /= a); }
    template <class T>
    friend ModInt operator+(T a, const ModInt &b) {
        return (ModInt(a) += b);
    }
    template <class T>
    friend ModInt operator-(T a, const ModInt &b) {
        return (ModInt(a) -= b);
    }
    template <class T>
    friend ModInt operator*(T a, const ModInt &b) {
        return (ModInt(a) *= b);
    }
    template <class T>
    friend ModInt operator/(T a, const ModInt &b) {
        return (ModInt(a) /= b);
    }
    explicit operator bool() const { return x; }
    bool operator==(const ModInt &a) const { return (x == a.x); }
    bool operator!=(const ModInt &a) const { return (x != a.x); }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &a) {
        return os << a.x;
    }

    // Functions
    ModInt pow(int64_t e) const {
        if (e < 0) return inv().pow(-e);
        ModInt a = *this, b = 1U;
        for (; e; e >>= 1) {
            if (e & 1) b *= a;
            a *= a;
        }
        return b;
    }

    ModInt inv() const {
        if (x < 10 && M == MOD) return ModInt(INV[x]);
        unsigned a = M, b = x;
        int y = 0, z = 1;
        for (; b;) {
            const unsigned q = a / b;
            const unsigned c = a - q * b;
            a = b;
            b = c;
            const int w = y - static_cast<int>(q) * z;
            y = z;
            z = w;
        }
        assert(a == 1U);
        return ModInt(y);
    }
};

using mInt = ModInt<MOD>;

class Solution {
public:
    int countGoodArrays(int n, int m, int k) {
        mInt ret{m};
        ret *= binomial(n - 1, k);
        ret *= mInt(m - 1).pow(n - k - 1);
        return ret.x;
    }

private:
    mInt binomial(int n, int k) {
        if (k < 0 || k > n) {
            return mInt(0);
        }
        mInt res = 1;
        for (int i = 0; i < k; ++i) {
            res *= mInt(n - i);
            res /= mInt(i + 1);
        }
        return res;
    }
};
