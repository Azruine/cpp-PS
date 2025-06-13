/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
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
public:
    int32_t minimizeMax(std::vector<int32_t>& nums, int32_t p) {
        if (p == 0) {
            return 0;
        }
        std::ranges::sort(nums);
        auto left = 0;
        auto right = nums.back() - nums.front();
        while (left < right) {
            auto mid = (left + right) / 2;
            if (check(nums, p, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

private:
    static bool check(std::vector<int32_t>& nums, int32_t p, int32_t mid) {
        int32_t count = 0;
        for (size_t i = 1; i < nums.size(); i++) {
            if (nums[i] - nums[i - 1] <= mid) {
                count++;
                i++;
            }
        }
        return count >= p;
    }
};
