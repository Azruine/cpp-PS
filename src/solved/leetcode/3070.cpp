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

#include <vector>

class Solution {
    std::vector<std::vector<int32_t>> prefix;

public:
    int countSubmatrices(std::vector<std::vector<int>>& grid, int k) {
        auto n = grid.size(), m = grid.front().size();
        prefix.resize(n + 1, std::vector<int32_t>(m + 1, 0));
        int32_t ret = 0;
        for (auto i = 0UL; i < n; i++) {
            for (auto j = 0UL; j < m; j++) {
                prefix[i + 1][j + 1] = grid[i][j]
                                       + prefix[i][j + 1]
                                       + prefix[i + 1][j]
                                       - prefix[i][j];
                if (prefix[i + 1][j + 1] <= k) {
                    ret += 1;
                }
            }
        }
        return ret;
    }
};
