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
#include <cstdint>
#include <vector>

class SparseTable {
    size_t n = 0;
    std::vector<int32_t> logs;
    std::vector<int32_t> min_table;
    std::vector<int32_t> max_table;

public:
    explicit SparseTable(std::vector<int32_t> const& data) : n(data.size()) {
        logs.resize(n + 1, 0);
        for (auto i : _iota(2U, n + 1)) {
            logs[i] = logs[i / 2] + 1;
        }
        size_t max_level = logs[n] + 1;
        min_table.resize(n * max_level, 0);
        max_table.resize(n * max_level, 0);

        for (auto i : _iota(n)) {
            min_table[i] = max_table[i] = data[i];
        }
        for (size_t level = 1; level < max_level; level++) {
            size_t len = 1UL << level;
            size_t half = len >> 1;
            for (size_t i = 0; i < n - len + 1; i++) {
                size_t base = (level * n) + i;
                size_t prev = ((level - 1) * n) + i;
                min_table[base] =
                    std::min(min_table[prev], min_table[prev + half]);
                max_table[base] =
                    std::max(max_table[prev], max_table[prev + half]);
            }
        }
    }
    int32_t query(size_t left, size_t right) const {
        size_t len = right - left + 1;
        size_t level = logs[len];
        size_t width = 1UL << level;
        return std::max(max_table[(level * n) + right + 1 - width],
                        max_table[(level * n) + left])
               - std::min(min_table[(level * n) + right + 1 - width],
                          min_table[(level * n) + left]);
    }
};

class Solution {
public:
    int64_t maxTotalValue(std::vector<int32_t>& nums, int32_t k) {
        int64_t ret = 0;
        size_t n = nums.size();

        auto [min_it, max_it] = std::minmax_element(nums.begin(), nums.end());
        int32_t global_min = *min_it;
        int32_t global_max = *max_it;
        int64_t global_diff = global_max - global_min;

        if (global_diff == 0) {
            return 0;
        }

        int64_t count = 0;
        int32_t min_pos = -1;
        int32_t max_pos = -1;

        for (auto i : _iota(0U, n)) {
            if (nums[i] == global_min) {
                min_pos = i;
            }
            if (nums[i] == global_max) {
                max_pos = i;
            }
            if (min_pos != -1 && max_pos != -1) {
                count += std::min(min_pos, max_pos) + 1;
            }
        }

        if (count >= k) {
            return global_diff * k;
        }

        SparseTable table(nums);
        struct Rng {
            uint32_t left = 0, right = 0;
            int32_t value = 0;
        };
        auto cmp = [](Rng const& lhs, Rng const& rhs) {
            return lhs.value < rhs.value;
        };
        std::vector<Rng> heap;
        heap.reserve(n);
        for (auto left : _iota(0U, n)) {
            heap.emplace_back(left, n - 1, table.query(left, n - 1));
        }
        std::make_heap(heap.begin(), heap.end(), cmp);
        while (k--) {
            std::pop_heap(heap.begin(), heap.end(), cmp);
            auto cur = heap.back();
            heap.pop_back();
            ret += cur.value;

            if (cur.right > cur.left) {
                size_t next_right = cur.right - 1;
                heap.emplace_back(cur.left, next_right,
                                  table.query(cur.left, next_right));
                std::push_heap(heap.begin(), heap.end(), cmp);
            }
        }
        return ret;
    }
};
