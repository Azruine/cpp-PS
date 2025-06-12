/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
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
    int maxAdjacentDistance(std::vector<int>& nums) {
        nums.push_back(nums.front());
        auto view =
            nums | std::views::adjacent_transform<2>(
                       [](auto& a, auto& b) { return std::abs(a - b); });
        return std::ranges::max(view);
    }
};
