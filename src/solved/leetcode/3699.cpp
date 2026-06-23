/*==== Copyright 2025 Azruine ====*/

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

#include <vector>

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        constexpr static int32_t MOD = 1'000'000'007;
        size_t m = r - l + 1;
        if (n == 1) {
            return (r - l + 1) % MOD;
        }
        std::vector<int32_t> prev(m + 1, 0);
        std::vector<int32_t> cur(m + 1, 0);
        for (size_t i = 0; i < m; i++) {
            prev[i + 1] = i;
        }
        for (size_t i = 3; i <= n; i++) {
            int32_t pre = 0;
            for (size_t j = 0; j < m; j++) {
                cur[j + 1] = pre;
                pre = (pre + prev[m - j]) % MOD;
            }
            std::swap(prev, cur);
        }
        int32_t ret = 0;
        for (size_t i = 0; i < m; i++) {
            ret = (ret + prev[i + 1]) % MOD;
        }
        return (ret << 1) % MOD;
    }
};
