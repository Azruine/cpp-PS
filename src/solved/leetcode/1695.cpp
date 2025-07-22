/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <array>
#include <cstdint>
#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
private:
    constexpr static size_t MAX = 10'001;
    std::array<size_t, MAX> seen = {};

public:
    int32_t maximumUniqueSubarray(std::vector<int32_t>& nums) {
        size_t left = 0, right = 0, n = nums.size();
        int32_t sum = 0, max_sum = 0;
        while (right < n) {
            if (seen[as<size_t>(nums[right])] == 0) {
                seen[as<size_t>(nums[right])] = right + 1;
                sum += nums[right];
                right += 1;
            } else {
                while (left < seen[as<size_t>(nums[right])]) {
                    sum -= nums[left];
                    seen[as<size_t>(nums[left])] = 0;
                    left += 1;
                }
                seen[as<size_t>(nums[right])] = right + 1;
                sum += nums[right];
                right += 1;
            }
            max_sum = std::max(max_sum, sum);
        }
        return max_sum;
    }
};
