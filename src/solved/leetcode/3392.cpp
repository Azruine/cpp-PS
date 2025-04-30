/*==== Copyright 2025 Azruine ====*/

#include <ranges>
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
    int countSubarrays(std::vector<int>& nums) {
        size_t n = nums.size();
        int32_t cnt = 0;
        for (auto i : std::ranges::iota_view(size_t{0}, n - 2)) {
            if ((nums[i] + nums[i + 2]) * 2 == nums[i + 1]) {
                cnt++;
            }
        }
        return cnt;
    }
};
