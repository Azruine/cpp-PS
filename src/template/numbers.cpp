/*==== Copyright 2025 Azruine ====*/

#include <cassert>
#include <concepts>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

namespace Numbers {
using int128_t = __int128_t;
using uint128_t = __uint128_t;
template <std::integral auto const N>
    requires(N > 1)
class ModInt {
    static_assert(N <= std::numeric_limits<int64_t>::max(),
                  "N is too large for ModInt");
    constexpr static int64_t MOD = as<int64_t>(N);
    int64_t value;

public:
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

    constexpr bool operator==(ModInt const& rhs) const noexcept = default;
    constexpr auto operator<=>(ModInt const& rhs) const noexcept = default;
    explicit constexpr operator bool() const noexcept { return value != 0; }

    constexpr ModInt& operator+=(ModInt const& rhs) noexcept {
        auto temp_val = as<int128_t>(rhs.value) + value;
        value = temp_val % MOD;
        return *this;
    }
    constexpr ModInt& operator-=(ModInt const& rhs) noexcept {
        auto temp_val = (as<int128_t>(value) - rhs.value) % MOD;
        if (temp_val < 0) {
            temp_val += MOD;
        }
        value = as<int64_t>(temp_val);
        return *this;
    }
    constexpr ModInt& operator*=(ModInt const& rhs) noexcept {
        auto temp_val = as<int128_t>(rhs.value) * value;
        value = as<int64_t>(temp_val % MOD);
        return *this;
    }
    constexpr ModInt& operator/=(ModInt const& rhs) {
        assert(rhs.value != 0 && "Division by zero in ModInt");
        auto temp_val = as<int128_t>(value) * rhs.inv().value;
        value = as<int64_t>(temp_val % MOD);
        return *this;
    }

    ModInt operator+(ModInt const& rhs) const noexcept {
        ModInt result(*this);
        result += rhs;
        return result;
    }

    ModInt operator-(ModInt const& rhs) const noexcept {
        ModInt result(*this);
        result -= rhs;
        return result;
    }

    ModInt operator*(ModInt const& rhs) const noexcept {
        ModInt result(*this);
        result *= rhs;
        return result;
    }

    ModInt operator/(ModInt const& rhs) const {
        assert(rhs.value != 0 && "Division by zero in ModInt");
        ModInt result(*this);
        result /= rhs;
        return result;
    }

    template <std::integral U>
    constexpr ModInt operator+(U const& rhs) const noexcept {
        return *this + ModInt(rhs);
    }

    template <std::integral U>
    constexpr ModInt operator-(U const& rhs) const noexcept {
        return *this - ModInt(rhs);
    }

    template <std::integral U>
    constexpr ModInt operator*(U const& rhs) const noexcept {
        return *this * ModInt(rhs);
    }

    template <std::integral U>
    constexpr ModInt operator/(U const& rhs) const noexcept {
        return *this / ModInt(rhs);
    }

    constexpr ModInt inv() const {
        assert(std::gcd(value, MOD) == 1 && "Inverse does not exist");
        assert(value != 0 && "Cannot compute inverse of zero in ModInt");
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


}  // namespace Numbers
