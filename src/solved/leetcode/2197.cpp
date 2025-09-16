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

#include <numeric>
#include <vector>

class Solution {
public:
    std::vector<int> replaceNonCoprimes(std::vector<int>& nums) {
        std::vector<int32_t> stk;
        for (auto elem : nums) {
            stk.push_back(elem);
            while (stk.size() > 1) {
                auto first = stk.back();
                auto second = *(stk.rbegin() + 1);
                if (std::gcd(first, second) == 1) {
                    // do nothing;
                    break;
                }
                stk.pop_back();
                stk.back() = std::lcm(first, second);
            }
        }
        return stk;
    }
};
