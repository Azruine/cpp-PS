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
        std::vector<int64_t> suffix(n * 3, -1);
        std::priority_queue<int32_t> max_heap;
        std::priority_queue<int32_t, std::vector<int32_t>,
                            std::greater<int32_t>>
            min_heap;
        int64_t cur_sum = 0;
        for (size_t i = 0; i < n; i++) {
            max_heap.emplace(nums[i]);
            cur_sum += nums[i];
        }
        prefix[n - 1] = cur_sum;
        for (size_t i = n; i < n * 3; i++) {
            if (max_heap.top() > nums[i]) {
                cur_sum += nums[i] - max_heap.top();
                max_heap.pop();
                max_heap.emplace(nums[i]);
            }
            prefix[i] = cur_sum;
        }

        cur_sum = 0;
        for (size_t i = n * 2; i < n * 3; i++) {
            min_heap.emplace(nums[i]);
            cur_sum += nums[i];
        }
        suffix[n * 2] = cur_sum;
        for (size_t i = (n * 2) - 1; i != UINT64_MAX; i--) {
            if (min_heap.top() < nums[i]) {
                cur_sum += nums[i] - min_heap.top();
                min_heap.pop();
                min_heap.emplace(nums[i]);
            }
            suffix[i] = cur_sum;
        }
        int64_t result = INT64_MAX;
        for (size_t i = n; i <= n * 2; i++) {
            result = std::min(result, prefix[i - 1] - suffix[i]);
        }
        return result;
    }
};
