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
#include <limits>
#include <vector>

class Solution {
    constexpr static int32_t MOD = 1'000'000'007;
    std::vector<std::vector<int64_t>> min_grid, max_grid;

public:
    int maxProductPath(std::vector<std::vector<int>>& grid) {
        auto n = grid.size(), m = grid.front().size();
        min_grid.resize(n, std::vector(m, std::numeric_limits<int64_t>::min()));
        max_grid.resize(n, std::vector(m, std::numeric_limits<int64_t>::max()));
        max_grid[0][0] = grid[0][0];
        min_grid[0][0] = grid[0][0];
        for (auto row = 0UL; row < n; row++) {
            for (auto col = 0UL; col < m; col++) {
                if (row == 0 && col == 0) {
                    continue;
                }
                auto local_min = std::numeric_limits<int64_t>::max();
                auto local_max = std::numeric_limits<int64_t>::min();
                for (auto [prev_row, prev_col] :
                     {std::pair{row - 1, col}, {row, col - 1}}) {
                    if (prev_row >= n || prev_col >= m) {
                        continue;
                    }
                    auto cand_1 = min_grid[prev_row][prev_col] * grid[row][col];
                    auto cand_2 = max_grid[prev_row][prev_col] * grid[row][col];
                    local_max = std::ranges::max({local_max, cand_1, cand_2});
                    local_min = std::ranges::min({local_min, cand_1, cand_2});
                }
                min_grid[row][col] = local_min;
                max_grid[row][col] = local_max;
            }
        }
        return max_grid.back().back() >= 0 ? max_grid.back().back() % MOD : -1;
    }
};
