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
#include <vector>

class Solution {
public:
    bool hasIncreasingSubarrays(std::vector<int>& nums, int k) {
        auto len = nums.size();
        std::vector test(len, 0);
        std::vector<int> max_len;
        test.back() = 1;
        for (auto i : _iota(len - 1) | std::views::reverse) {
            if (nums[i + 1] > nums[i]) {
                test[i] = test[i + 1] + 1;
            } else {
                max_len.push_back(test[i + 1]);
                test[i] = 1;
            }
        }
        max_len.push_back(test.front());
        int ret = 0;
        int max = max_len.back();
        for (auto i : _iota(max_len.size() - 1)) {
            max = std::max(max, max_len[i]);
            ret = std::max(ret, std::min(max_len[i], max_len[i + 1]));
        }
        return k <= std::max(ret, max / 2);
    }
};
