/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <numeric>
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
    int64_t minSum(std::vector<int32_t>& nums1, std::vector<int32_t>& nums2) {
        auto zero_count_1 = std::count_if(nums1.begin(), nums1.end(),
                                          [](int32_t n) { return n == 0; });
        auto zero_count_2 = std::count_if(nums2.begin(), nums2.end(),
                                          [](int32_t n) { return n == 0; });
        auto sum_1 = std::accumulate(nums1.begin(), nums1.end(), 0LL);
        auto sum_2 = std::accumulate(nums2.begin(), nums2.end(), 0LL);

        int64_t ans{0};
        if (zero_count_1 == 0 && zero_count_2 == 0) {
            ans = (sum_1 == sum_2) ? sum_1 : -1;
        } else if (zero_count_1 == 0) {
            auto min = zero_count_2 + sum_2;
            ans = (min > sum_1) ? -1 : sum_1;
        } else if (zero_count_2 == 0) {
            auto min = zero_count_1 + sum_1;
            ans = (min > sum_2) ? -1 : sum_2;
        } else {
            ans = std::max(zero_count_1 + sum_1, zero_count_2 + sum_2);
        }
        return ans;
    }
};
