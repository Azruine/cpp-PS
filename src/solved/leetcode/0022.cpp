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

#include <string>
#include <vector>

class Solution {
    struct State {
        std::string str;
        size_t open = 0;
        size_t close = 0;
    };

public:
    std::vector<std::string> generateParenthesis(size_t n) {
        std::vector<std::string> ret;
        std::vector<State> stk;

        stk.emplace_back("");
        while (!stk.empty()) {
            auto [cur_str, cur_open, cur_close] = stk.back();
            stk.pop_back();
            if (cur_str.length() == n << 1) {
                if (cur_open == cur_close) {
                    ret.emplace_back(cur_str);
                }
                continue;
            }
            if (cur_open > cur_close) {
                stk.emplace_back(cur_str + '(', cur_open + 1, cur_close);
                stk.emplace_back(cur_str + ')', cur_open, cur_close + 1);
            } else {
                stk.emplace_back(cur_str + '(', cur_open + 1, cur_close);
            }
        }
        return ret;
    }
};

int main() {
    Solution sol;
    auto n = sol.generateParenthesis(3).size();
    return (n & 1);
}
