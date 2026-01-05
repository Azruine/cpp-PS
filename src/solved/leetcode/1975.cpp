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
    int64_t maxMatrixSum(std::vector<std::vector<int>>& matrix) {
        int64_t ret = 0;
        int32_t min_abs = 100'010;
        bool cnt = true;
        for (auto& row : matrix) {
            for (auto& elem : row) {
                min_abs = std::min(std::abs(elem), min_abs);
                ret += std::abs(elem);
                if (elem < 0) {
                    cnt = !cnt;
                }
            }
        }
        return ret - (cnt ? 0 : min_abs) * 2;
    }
};
