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
    constexpr static int32_t MOD = 1'000'000'007;
    constexpr static size_t MAX = 100'010;
    constexpr static size_t LOG = as<size_t>(std::bit_width(MAX));

    struct Pair {
        size_t start = 0;
        size_t end = 0;
    };
    struct Cell {
        uint64_t cnt = 0;
        uint64_t sum = 0;
    };

public:
    int32_t sumCounts(std::vector<int32_t>& nums) {
        size_t n = nums.size();
        std::vector<Pair> intervals;
        intervals.reserve(n);
        std::vector<size_t> prev(MAX, MAX + 1);
        for (size_t i = 0; i < n; i++) {
            if (prev[as<size_t>(nums[i])] != MAX + 1) {
                intervals.emplace_back(prev[as<size_t>(nums[i])], i);
            }
            prev[as<size_t>(nums[i])] = i;
        }
        auto sqr =
            as<uint64_t>(as<__uint128_t>(n) * (n + 1) * (n + 1) * (n + 2) / 12);
        uint64_t lin = 0;
        uint64_t bad = 0;
        for (auto& [start, end] : intervals) {
            uint64_t cover = (start + 1) * (n - end);
            lin += cover * (n + end - start + 1);
            bad += cover;
        }
        std::vector<Cell> table((n >> 1) + 1);
        for (size_t bit = 0; bit < LOG; bit++) {
            std::ranges::fill(table, Cell{});
            for (auto& [start, end] : intervals) {
                Cell& cell = table[start >> (bit + 1)];
                uint64_t one = (start >> bit) & 1;
                uint64_t mask = 0 - one;
                uint64_t weight = start + 1;
                uint64_t got =
                    (cell.sum & mask) | ((weight * cell.cnt) & ~mask);
                cell.cnt += one;
                cell.sum += weight & ~mask;
                bad += (n - end) * (got << 1);
            }
        }
        return as<int32_t>((sqr - lin + bad) % MOD);
    }
};
