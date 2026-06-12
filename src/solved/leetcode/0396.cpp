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

#include <numeric>
#include <vector>

class Solution {
public:
    int32_t maxRotateFunction(std::vector<int32_t>& nums) {
        size_t n = nums.size();
        int32_t value = 0;
        for (size_t i = 0; i < n; i++) {
            value += nums[i] * as<int32_t>(i);
        }
        int32_t sum = std::accumulate(nums.begin(), nums.end(), 0);
        int32_t ret = value;
        for (size_t i = n - 1; i < n; i--) {
            value = value - nums[i] * as<int32_t>(n) + sum;
            ret = std::max(ret, value);
        }
        return ret;
    }
};
