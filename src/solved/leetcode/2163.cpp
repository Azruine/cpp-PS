/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
#include <queue>
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
    int64_t minimumDifference(std::vector<int32_t>& nums) {
        size_t n = nums.size() / 3;
        std::vector<int64_t> prefix(n * 3, -1);
        std::priority_queue<int32_t> max_heap;
        int64_t cur_sum = 0;
        for (size_t i = 0; i < n * 3; i++) {
            max_heap.emplace(nums[i]);
            cur_sum += nums[i];
            if (max_heap.size() > n) {
                cur_sum -= max_heap.top();
                max_heap.pop();
            }
            if (max_heap.size() == n) {
                prefix[i] = cur_sum;
            } else {
                prefix[i] = INT64_MIN;
            }
        }

        std::vector<int64_t> suffix(n * 3, -1);
        std::priority_queue<int32_t, std::vector<int32_t>,
                            std::greater<int32_t>>
            min_heap;
        cur_sum = 0;
        for (size_t i = nums.size() - 1; i != UINT64_MAX; i--) {
            min_heap.emplace(nums[i]);
            cur_sum += nums[i];
            if (min_heap.size() > n) {
                cur_sum -= min_heap.top();
                min_heap.pop();
            }
            if (min_heap.size() == n) {
                suffix[i] = cur_sum;
            } else {
                suffix[i] = INT64_MIN;
            }
        }
        int64_t result = INT64_MAX;
        for (size_t i = n; i <= n * 2; i++) {
            result = std::min(result, prefix[i - 1] - suffix[i]);
        }
        return result;
    }
};
