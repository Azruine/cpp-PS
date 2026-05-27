/*==== Copyright 2025 Azruine ====*/

#include <ranges>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
struct Range {
    template <typename Sentinel>
    constexpr auto operator()(Sentinel sentinel) const noexcept {
        return std::views::iota(static_cast<Sentinel>(0), sentinel);
    }
    template <typename Start, typename Sentinel>
    constexpr auto operator()(Start start, Sentinel sentinel) const noexcept {
        return std::views::iota(start, sentinel);
    }
    template <typename Start, typename Sentinel, typename Step>
    constexpr auto operator()(Start start, Sentinel sentinel,
                              Step step) const noexcept {
        return std::views::iota(start, sentinel) | std::views::stride(step);
    }
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
constexpr Range _iota{};
#pragma GCC diagnostic pop
}  // namespace

#include <algorithm>
#include <cstdint>
#include <string>

class Solution {
public:
    int32_t numberOfSpecialChars(std::string word) {
        auto [low, up, bad] = std::ranges::fold_left(
            word, std::tuple{0U, 0U, 0U}, [](auto acc, char chr) {
                auto [l, u, b] = acc;
                uint32_t m = 1U << ((chr | 32) - 'a');
                return std::islower(chr) ? std::tuple{l | m, u, b | (u & m)}
                                         : std::tuple{l, u | m, b};
            });
        return std::popcount(low & up & ~bad);
    }
};
