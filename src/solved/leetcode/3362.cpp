/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
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
    int32_t maxRemoval(std::vector<int32_t>& nums,
                       std::vector<std::vector<int32_t>>& queries) {
        std::ranges::sort(queries, [](auto const& lhs, auto const& rhs) {
            return lhs[0] < rhs[0];
        });
        std::priority_queue<size_t> min_heap;
        std::vector<int32_t> delta(nums.size() + 1, 0);
        int32_t cur_sum{0};
        bool is_valid{true};
        for (size_t i{0}, j{0}; i < nums.size(); i++) {
            cur_sum += delta[i];
            while (j < queries.size() && queries[j][0] == as<int32_t>(i)) {
                min_heap.push(as<size_t>(queries[j][1]));
                j++;
            }
            while (cur_sum < nums[i] && !min_heap.empty() &&
                   min_heap.top() >= i) {
                cur_sum++;
                delta[as<size_t>(min_heap.top()) + 1]--;
                min_heap.pop();
            }
            if (cur_sum < nums[i]) {
                is_valid = false;
                break;
            }
        }
        return (is_valid) ? as<int32_t>(min_heap.size()) : -1;
    }
};
