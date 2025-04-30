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
    int64_t findNumbers(std::vector<int32_t>& nums) {
        return std::ranges::count_if(nums, [](int32_t i) {
            return std::to_string(i).length() % 2 == 0;
        });
    }
};
