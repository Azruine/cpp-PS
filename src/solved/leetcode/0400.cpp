/*==== Copyright 2025 Azruine ====*/

#include <utility>
#include <cstdint>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
private:
    static constexpr int64_t BASE = 10;

public:
    int64_t pow(int64_t base, int64_t exp) {
        int64_t ret = 1;
        while (exp > 0) {
            if (exp & 1) {
                ret *= base;
            }
            base *= base;
            exp >>= 1;
        }
        return ret;
    }
    int64_t get_range(int64_t& n) {
        int64_t ret = 1;
        int64_t range = (BASE - 1) * pow(BASE, ret - 1) * ret;
        while (n > 0) {
            range = (BASE - 1) * pow(BASE, ret - 1) * ret;
            n -= range;
            ret++;
        }
        n += range;
        ret--;
        return ret;
    }
    int64_t findNthDigit(int64_t n) {
        int64_t range = get_range(n);
        int64_t start = pow(BASE, range - 1);
        int64_t num = start + ((n - 1) / range);
        n %= range;
        if (n == 0) {
            n = range;
        }
        int64_t digit = range - n;
        while (digit > 0) {
            num /= BASE;
            digit--;
        }
        return num % BASE;
    }
};
