/*==== Copyright 2025 Azruine ====*/

#include <string>
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
    std::string triangleType(std::vector<int32_t>& nums) {
        if (nums[0] + nums[1] <= nums[2] || nums[1] + nums[2] <= nums[0] ||
            nums[2] + nums[0] <= nums[1]) {
            return "none";
        } else if (nums[0] == nums[1] && nums[1] == nums[2]) {
            return "equilateral";
        } else if (nums[0] == nums[1] || nums[1] == nums[2] ||
                   nums[2] == nums[0]) {
            return "isosceles";
        } else {
            return "scalene";
        }
    }
};
