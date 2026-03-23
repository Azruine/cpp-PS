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
    std::vector<std::vector<int>> minAbsDiff(
        std::vector<std::vector<int>>& grid, size_t k) {
        auto n = grid.size(), m = grid.front().size();
        std::vector ret(n - k + 1, std::vector(m - k + 1, 0));
        if (k == 1) {
            return ret;
        }
        for (auto i = 0U; i < n - k + 1; i++) {
            for (auto j = 0U; j < m - k + 1; j++) {
                std::vector<int32_t> arr;
                arr.reserve(k * k);
                for (auto row = 0U; row < k; row++) {
                    for (auto col = 0U; col < k; col++) {
                        arr.emplace_back(grid[i + row][j + col]);
                    }
                }
                std::ranges::sort(arr);
                arr.erase(std::unique(arr.begin(), arr.end()), arr.end());
                if (arr.size() != 1) {
                    ret[i][j] = std::ranges::min(
                        arr
                        | std::views::adjacent_transform<2>(std::minus())
                        | std::views::transform(
                            [](auto a) { return std::abs(a); }));
                }
            }
        }
        return ret;
    }
};
