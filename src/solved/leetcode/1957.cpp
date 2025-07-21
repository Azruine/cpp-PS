/*==== Copyright 2025 Azruine ====*/

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
    std::string makeFancyString(std::string str) {
        return str |
               std::views::chunk_by([](char a, char b) { return a == b; }) |
               std::views::transform(
                   [](auto&& chunk) { return chunk | std::views::take(2); }) |
               std::views::join |
               std::ranges::to<std::string>();
    }
};
