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
#include <set>
#include <string>
#include <vector>

class Solution {
public:
    bool canReach(std::string str, int32_t minJump, int32_t maxJump) {
        size_t n = str.size();
        std::set<size_t> zeros;
        for (auto i : _iota(n)) {
            if (str[i] == '0') {
                zeros.insert(i);
            }
        }
        std::vector<size_t> stk;
        stk.emplace_back(0);
        while (!stk.empty()) {
            auto cur = stk.back();
            stk.pop_back();
            auto lower = cur + minJump;
            auto upper = std::min(cur + maxJump, n - 1);
            auto it = zeros.lower_bound(lower);
            while (it != zeros.end() && *it <= upper) {
                auto next = *it;
                if (next == n - 1) {
                    return true;
                }
                it = zeros.erase(it);
                stk.emplace_back(next);
            }
        }
        return false;
    }
};
