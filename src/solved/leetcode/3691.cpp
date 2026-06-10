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
#include <bit>
#include <cstdint>
#include <vector>

class SparseTable {
    size_t n = 0;
    struct MinMax {
        int32_t min = 0, max = 0;
    };
    std::vector<MinMax> table;

public:
    explicit SparseTable(std::vector<int32_t> const& data) : n(data.size()) {
        size_t max_level = std::bit_width(n);
        table.resize(n * max_level);

        for (auto i : _iota(n)) {
            table[i].min = table[i].max = data[i];
        }
        for (size_t level = 1; level < max_level; level++) {
            size_t len = 1UL << level;
            size_t half = len >> 1;
            size_t base = (level * n);
            size_t prev = ((level - 1) * n);
            for (size_t i = 0; i < n - len + 1; i++) {
                auto const& a = table[prev + i];
                auto const& b = table[prev + i + half];
                table[base + i] = {
                    .min = std::min(a.min, b.min),
                    .max = std::max(a.max, b.max),
                };
            }
        }
    }
    int32_t query(size_t left, size_t right) const {
        size_t len = right - left + 1;
        size_t level = std::bit_width(len) - 1;
        size_t width = 1UL << level;
        auto const& a = table[(level * n) + left];
        auto const& b = table[(level * n) + right + 1 - width];
        return std::max(a.max, b.max) - std::min(a.min, b.min);
    }
};

class Solution {
public:
    int64_t maxTotalValue(std::vector<int32_t>& nums, int32_t k) {
        int64_t ret = 0;
        size_t n = nums.size();

        auto [min, max] = std::ranges::minmax_element(nums);
        int64_t diff = *max - *min;
        if (diff == 0) {
            return 0;
        }

        int32_t count = 0;
        int32_t min_pos = -1;
        int32_t max_pos = -1;

        for (auto i : _iota(0U, n)) {
            if (nums[i] == *min) {
                min_pos = i;
            }
            if (nums[i] == *max) {
                max_pos = i;
            }
            count += std::min(min_pos, max_pos) + 1;
            if (count >= k) {
                return diff * k;
            }
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
        std::ranges::make_heap(heap, cmp);
        while (k--) {
            std::ranges::pop_heap(heap, cmp);
            Rng& cur = heap.back();
            ret += cur.value;
            if (cur.right > cur.left) {
                cur.right -= 1;
                cur.value = table.query(cur.left, cur.right);
                std::ranges::push_heap(heap, cmp);
            } else {
                heap.pop_back();
            }
        }
        return ret;
    }
};
