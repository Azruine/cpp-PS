/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cstdint>
#include <limits>
#include <ranges>
#include <string>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
public:
    int32_t maxDifference(std::string s) {
        return std::ranges::max(std::views::iota(0, 26) |
                                std::views::transform([&](int32_t i){return as<int32_t>(std::ranges::count(s, 'a' + i)); }) |
                                std::views::transform([](int32_t val) { return val & 1 ? val : -1; })) -
               std::ranges::min(std::views::iota(0, 26) |
                                std::views::transform([&](int32_t i){return as<int32_t>(std::ranges::count(s, 'a' + i)); }) |
                                std::views::transform([](int32_t val) { return val & 1 ? std::numeric_limits<int32_t>::max() : val; }) |
                                std::views::filter([](int32_t val) { return val != 0; }));
    }
};
