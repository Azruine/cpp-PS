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
    auto divideArray(std::vector<int>& nums, int k) {
        std::ranges::sort(nums);
        auto ranges =
            nums | std::views::chunk(3) | std::views::transform([](auto&& vec) {
                return std::vector<int>(std::begin(vec), std::end(vec));
            });
        auto result =
            std::vector<std::vector<int>>(ranges.begin(), ranges.end());
        if (std::ranges::any_of(result, [&](auto const& vec) {
                return vec.back() - vec.front() <= k;
            })) {
            result.clear();
        }
        return result;
    }
};

