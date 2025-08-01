/*==== Copyright 2025 Azruine ====*/

#include <ranges>
#include <utility>
#include <vector>

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

class Solution {
public:
    std::vector<std::vector<int>> generate(int numRows) {
        std::vector<std::vector<int>> row;
        row.resize(as<size_t>(numRows));
        for (auto n : _iota(as<size_t>(numRows))) {
            for (auto k : _iota(n + 1)) {
                if (k == 0 || k == n) {
                    row[n].push_back(1);
                } else {
                    row[n].push_back(row[n - 1][k - 1] + row[n - 1][k]);
                }
            }
        }
        return row;
    }
};
