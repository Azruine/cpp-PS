/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
#include <unordered_map>
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
    int64_t countGood(std::vector<int>& nums, int k) {
        std::unordered_map<int, int64_t> counts;
        size_t n = nums.size();
        size_t left = 0;
        size_t right = 0;
        int64_t ans = 0;
        int64_t size = 0;
        counts[nums.front()]++;
        while (left <= right && right < n) {
            if (size < k) {
                if (++right < n) {
                    counts[nums[right]]++;
                    size += (counts[nums[right]] - 1);
                }
            } else {
                ans += as<int64_t>(n - right);
                size -= (counts[nums[left]] - 1);
                counts[nums[left]]--;
                left++;
            }
        }
        return ans;
    }
};
