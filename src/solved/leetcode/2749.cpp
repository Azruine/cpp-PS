/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <bit>
#include <ranges>
#include <utility>

namespace {
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
constexpr Range _iota{};
#pragma GCC diagnostic pop
}  // namespace

class Solution {
    int32_t count_bits(int64_t const& n) {
        int32_t ret = 0;
        for (int i : _iota(0, 64)) {
            if (n & (1LL << i)) {
                ret += 1;
            }
        }
        return ret;
    }

public:
    int makeTheIntegerZero(int num1, int num2) {
        int64_t res = num1;
        int32_t count = 0;
        while (res >= 0) {
            auto bits = count_bits(res);
            if (bits <= count && res >= count) {
                return count;
            }
            res -= num2;
            count += 1;
        }
        return -1;
    }
};
