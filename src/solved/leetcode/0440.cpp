/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cstdint>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
public:
    int32_t findKthNumber(int32_t n, int32_t k) {
        int32_t ret{1};
        k -= 1;
        while (k > 0) {
            int64_t prefix1 = ret;
            int64_t prefix2 = ret + 1;
            int32_t steps = count(n, prefix1, prefix2);
            if (steps <= k) {
                k -= steps;
                ret += 1;
            } else {
                ret *= 10;
                k -= 1;
            }
        }
        return ret;
    }
    int32_t count(int32_t n, int64_t prefix1, int64_t prefix2) {
        int32_t steps{0};
        while (prefix1 <= n) {
            steps += std::min(as<int64_t>(n + 1), prefix2) - prefix1;
            prefix1 *= 10;
            prefix2 *= 10;
        }
        return steps;
    }
};
