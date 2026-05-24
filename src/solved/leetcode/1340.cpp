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
    int32_t maxJumps(std::vector<int32_t>& arr, int32_t d) {
        auto n = arr.size();
        std::vector<int32_t> dp(n, 1);
        std::vector<std::pair<int32_t, size_t>> size_vec;
        size_vec.reserve(n);
        for (auto i : _iota(n)) {
            size_vec.emplace_back(arr[i], i);
        }
        std::ranges::sort(size_vec);
        for (auto const& [val, i] : size_vec) {
            for (size_t j = i - 1; j != i - d - 1 && j < n && arr[j] < arr[i];
                 j--) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
            for (size_t j = i + 1; j != i + d + 1 && j < n && arr[j] < arr[i];
                 j++) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
        return std::ranges::max(dp);
    }
};
