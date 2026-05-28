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
    int32_t threeSumClosest(std::vector<int32_t>& nums, int32_t target) {
        std::ranges::sort(nums);
        size_t n = nums.size();
        int32_t ret = nums[0] + nums[1] + nums[2];
        for (size_t i = 0; i < n - 2; i++) {
            size_t left = i + 1, right = n - 1;
            while (left < right) {
                int32_t cur_sum = nums[left] + nums[right] + nums[i];
                if (std::abs(ret - target) > std::abs(cur_sum - target)) {
                    ret = cur_sum;
                }
                if (cur_sum < target) {
                    left += 1;
                } else if (cur_sum > target) {
                    right -= 1;
                } else {
                    return target;
                }
            }
        }
        return ret;
    }
};
