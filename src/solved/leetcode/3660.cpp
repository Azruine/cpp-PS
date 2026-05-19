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
    std::vector<int32_t> maxValue(std::vector<int32_t>& nums) {
        auto n = nums.size();
        std::vector<int32_t> ret(n, 0);
        std::vector<int32_t> prefix(n, -1), suffix(n, 1 << 31);
        prefix[0] = nums[0], suffix[n - 1] = nums[n - 1];
        for (auto i = 1UL; i < n; i++) {
            prefix[i] = std::max(prefix[i - 1], nums[i]);
            suffix[n - i - 1] = std::min(suffix[n - i], nums[n - i - 1]);
        }
        auto left = 0UL;
        for (auto right = 0UL; right < n; right++) {
            if (right == n - 1 || prefix[right] <= suffix[right + 1]) {
                std::ranges::fill(ret.begin() + left, ret.begin() + right + 1,
                                  prefix[right]);
                left = right + 1;
            }
        }
        return ret;
    }
};
