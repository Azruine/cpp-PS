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
#include <string>
#include <vector>

class Solution {
    std::pair<int32_t, int32_t> get_depth(std::string const& str) {
        int32_t depth = 0;
        int32_t min = 0;
        for (auto chr : str) {
            if (chr == '(') {
                depth += 1;
            } else if (chr == ')') {
                depth -= 1;
                min = std::min(min, depth);
            }
        }
        return {depth, min};
    }

public:
    std::vector<std::string> removeInvalidParentheses(std::string const& str) {
        std::vector<std::string> ret;
        auto n = str.length();
        auto [depth, min_depth] = get_depth(str);
        int32_t remove = depth - (min_depth << 1);
        if (remove == 0) {
            return {str};
        }
        for (uint64_t bits = (1ULL << remove) - 1; bits < (1ULL << n);) {
            std::string test;
            for (auto i = 0UL; i < n; i++) {
                if (!((bits >> i) & 1)) {
                    test += str[i];
                }
            }
            auto [er_depth, er_min] = get_depth(test);
            if (er_depth == 0 && er_min == 0) {
                ret.emplace_back(std::move(test));
            }
            uint64_t right = bits & -bits;
            uint64_t lift = bits + right;
            bits = lift | (((bits ^ lift) >> 2) >> std::countr_zero(bits));
        }
        std::ranges::sort(ret);
        ret.erase(std::unique(ret.begin(), ret.end()), ret.end());
        return ret;
    }
};
