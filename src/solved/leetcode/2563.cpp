/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
public:
    int64_t countFairPairs(std::vector<int>& nums, int lower, int upper) {
        std::ranges::sort(nums);
        size_t len = nums.size();
        int64_t ans = 0;
        for (auto i : std::ranges::views::iota(size_t{0}, len)) {
            auto lower_bound = std::ranges::lower_bound(
                std::next(nums.begin(), as<int64_t>(i + 1)), nums.end(),
                lower - nums[i]);
            auto upper_bound = std::ranges::upper_bound(
                std::next(nums.begin(), as<int64_t>(i + 1)), nums.end(),
                upper - nums[i]);
            ans += std::distance(lower_bound, upper_bound);
        }
        return ans;
    }
};
