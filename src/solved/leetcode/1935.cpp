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
}  // namespace

#include <cstdint>
#include <string>

class Solution {
public:
    static int canBeTypedWords(std::string const& text,
                               std::string const& brokenLetters) {
        uint64_t mask = 0;
        for (auto const& chr : brokenLetters) {
            mask |= (1ULL << (chr & 0B0001'1111));
        }
        bool flag = false;
        int32_t total = 1;
        int32_t broken = 0;
        for (auto const& chr : text) {
            if (chr == ' ') {
                total += 1;
            }
            if (flag) {
                flag = (chr != ' ');
                continue;
            }
            if ((mask >> (chr & 0B0001'1111)) & 1) {
                flag = true;
                broken += 1;
            }
        }
        return total - broken;
    }
};
