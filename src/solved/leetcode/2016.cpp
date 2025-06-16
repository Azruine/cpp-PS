/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
#include <limits>
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
    int32_t maximumDifference(std::vector<int32_t>& nums) {
        auto n{nums.size()};
        auto max_diff{std::numeric_limits<int32_t>::min()};
        for (size_t i{0}; i < n; ++i) {
            for (size_t j{i + 1}; j < n; ++j) {
                if (nums[j] <= nums[i]) {
                    continue;
                }
                auto diff{as<int32_t>(nums[j] - nums[i])};
                max_diff = std::max(max_diff, diff);
            }
        }
        return max_diff == std::numeric_limits<int32_t>::min() ? -1 : max_diff;
    }
};
