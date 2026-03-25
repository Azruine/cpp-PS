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
    bool canPartitionGrid(std::vector<std::vector<int>>& grid) {
        std::vector<int64_t> hori, ver;
        auto n = grid.size(), m = grid[0].size();
        hori.resize(n, 0), ver.resize(m, 0);
        for (auto i = 0UL; i < n; i++) {
            hori[i] = std::accumulate(grid[i].begin(), grid[i].end(), 0L,
                                      std::plus<>{});
        }
        for (auto j = 0UL; j < m; j++) {
            for (auto i = 0UL; i < n; i++) {
                ver[j] += grid[i][j];
            }
        }
        auto hori_sum =
            std::accumulate(hori.begin(), hori.end(), 0L, std::plus<>{});
        auto ver_sum =
            std::accumulate(ver.begin(), ver.end(), 0L, std::plus<>{});
        auto hori_acc = 0L, ver_acc = 0L;
        for (auto& hori_elem : hori) {
            if (hori_sum == hori_acc) {
                return true;
            }
            hori_sum -= hori_elem, hori_acc += hori_elem;
        }
        for (auto& ver_elem : ver) {
            if (ver_sum == ver_acc) {
                return true;
            }
            ver_sum -= ver_elem, ver_acc += ver_elem;
        }
        return false;
    }
};
