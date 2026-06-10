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

#include <algorithm>
#include <vector>

class Solution {
public:
    std::vector<int32_t> leftRightDifference(std::vector<int32_t>& nums) {
        size_t n = nums.size();
        std::vector<int32_t> ret(n, 0);
        int32_t right = std::ranges::fold_left(ret, 0, std::plus<>());
        int32_t left = 0;
        right -= nums[0];
        for (size_t i = 0; i < n; i++) {
            ret[i] = left - right;
            left += nums[i];
            if (i + 1 < n) {
                right -= nums[i + 1];
            }
        }
        return ret;
    }
};
