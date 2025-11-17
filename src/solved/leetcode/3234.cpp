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
#include <cmath>
#include <string>
#include <vector>

class Solution {
    std::vector<int32_t> cnt_one, cnt_zero;
    static int32_t sqrt(int32_t x) {
        auto val = as<int32_t>(std::floor(std::sqrt(x)));
        while (val * val < x) {
            val++;
        }
        while (val * val > x) {
            val--;
        }
        return val;
    }

public:
    int numberOfSubstrings(std::string& str) {
        size_t n = str.length();
        cnt_one.resize(n + 1, 0);
        cnt_zero.resize(n + 1, 0);
        for (size_t i : _iota(n)) {
            cnt_one[i + 1] = cnt_one[i] + (str[i] == '1');
            cnt_zero[i + 1] = cnt_zero[i] + (str[i] == '0');
        }
        auto max_zero = sqrt(cnt_one.back()) + 1;
        int32_t ret = 0;

        for (size_t left = 0; left < n; left++) {
            size_t right = left;
            while (right < n) {
                auto one = cnt_one[right + 1] - cnt_one[left];
                auto zero = cnt_zero[right + 1] - cnt_zero[left];
                if (zero > max_zero) {
                    break;
                }

                int32_t cnt = 0;
                if (one >= zero * zero) {
                    cnt = std::clamp(sqrt(one) - zero + 1, 0,
                                     as<int32_t>(n - right));
                    ret += cnt;
                } else {
                    cnt = (zero * zero) - one;
                }
                right += as<size_t>(cnt);
            }
        }
        return ret;
    }
};
