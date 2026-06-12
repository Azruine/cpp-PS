/*==== Copyright 2025 Azruine ====*/

#include <limits>
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
constexpr int32_t MAX = 10'001;
constexpr std::array<int32_t, 10> mp = {0, 1, 5, -1, -1, 2, 9, -1, 8, 6};
constexpr int32_t get_rev(int32_t x) {
    constexpr static int32_t TEN = 10;

    if (x < 0) {
        return -1;
    }
    if (x == 0) {
        return 0;
    }
    int64_t ret = 0;
    int64_t place = 1;
    while (x > 0) {
        int32_t digit = x % TEN;
        int32_t mapped = mp[digit];
        if (mapped == -1) {
            return -1;
        }
        ret += mapped * place;
        if (ret > std::numeric_limits<int32_t>::max()) {
            return -1;
        }
        place *= TEN;
        x /= TEN;
    }
    return as<int32_t>(ret);
}
}  // namespace

#include <algorithm>
#include <array>
#include <cstdint>

class Solution {
    constexpr static std::array<bool, MAX> is_good = []() {
        std::array<bool, MAX> ret{};
        for (int32_t i = 0; i < MAX; i++) {
            int32_t rev = get_rev(i);
            if (rev != -1 && rev != i) {
                ret[i] = true;
            }
        }
        return ret;
    }();

public:
    int rotatedDigits(int n) {
        return std::ranges::count(is_good.begin(), is_good.begin() + n + 1,
                                  true);
    }
};
