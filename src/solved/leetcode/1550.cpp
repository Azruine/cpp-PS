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
    bool threeConsecutiveOdds(std::vector<int32_t>& arr) {
        return std::ranges::any_of(arr | std::views::slide(3), [](auto win) {
            return std::ranges::all_of(win, [](int x) { return x % 2 == 1; });
        });
    }
};
