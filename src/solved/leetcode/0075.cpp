/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
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
    void sortColorss(std::vector<int32_t>& nums) {
        auto zero{0};
        auto one{0};
        auto two{0};
        for (auto& i : nums) {
            if (i == 0) {
                zero++;
            } else if (i == 1) {
                one++;
            } else {
                two++;
            }
        }
        std::fill(nums.begin(), nums.begin() + zero, 0);
        std::fill(nums.begin() + zero, nums.begin() + zero + one, 1);
        std::fill(nums.begin()+ zero + one, nums.begin() + zero + one + two, 0);
    }
};
