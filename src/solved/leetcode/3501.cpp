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
#include <string>
#include <vector>

class Solution {
public:
    std::vector<int32_t> maxActiveSectionsAfterTrade(
        std::string const& str, std::vector<std::vector<int32_t>>& queries) {
        std::vector<int32_t> sparse;
        std::vector<int32_t> zeros;
        std::vector<std::pair<int32_t, int32_t>> zero_bounds;
        std::vector<int32_t> zero_sum;
        std::vector<int32_t> ret;
        ret.reserve(queries.size());
        int32_t active = std::ranges::count(str, '1');
        {
            int32_t len = 0;
            int32_t left = -1;
            for (size_t index : _iota(str.length())) {
                if (str[index] == '0') {
                    len += 1;
                    if (left == -1) {
                        left = as<int32_t>(index);
                    }
                } else if (left != -1) {
                    zeros.emplace_back(len);
                    len = 0;
                    zero_bounds.emplace_back(left, index);
                    left = -1;
                }
            }
            if (left != -1) {
                zeros.emplace_back(len);
                zero_bounds.emplace_back(left, str.length());
            }
            for (size_t i = 1; i < zeros.size(); i++) {
                zero_sum.emplace_back(zeros[i - 1] + zeros[i]);
            }
        }
        // p * width + i: max on [i, i + (1 << p))
        size_t width = zero_sum.size();
        size_t levels = std::bit_width(width);
        if (width > 0) {
            sparse.resize(width * levels);
            std::ranges::copy(zero_sum, sparse.begin());
            for (size_t pow : _iota(1U, levels)) {
                size_t half = 1U << (pow - 1);
                size_t span = half << 1;
                size_t cur = pow * width;
                size_t prev = (pow - 1) * width;
                for (size_t i : _iota(width - span + 1)) {
                    sparse[cur + i] =
                        std::max(sparse[prev + i], sparse[prev + i + half]);
                }
            }
        }
        auto rmq = [&](size_t left, size_t right) {
            size_t len = right - left;
            size_t pow = std::bit_width(len) - 1;
            size_t span = 1U << pow;
            size_t offset = pow * width;
            return std::max(sparse[offset + left],
                            sparse[offset + right - span]);
        };
        auto find_left = [&](size_t left) {
            auto it = std::ranges::upper_bound(
                zero_bounds, left, {}, &std::pair<int32_t, int32_t>::second);
            return it - zero_bounds.begin();
        };
        auto find_right = [&](size_t right) {
            auto it = std::ranges::lower_bound(
                zero_bounds, right, {}, &std::pair<int32_t, int32_t>::first);
            return it - zero_bounds.begin();
        };
        for (auto const& query : queries) {
            // [left_idx, right_idx)
            size_t left_idx = query[0];
            size_t right_idx = query[1] + 1;
            auto left = find_left(left_idx);
            auto right = find_right(right_idx);
            auto cnt = right >= left ? right - left : 0;
            // can't do anything
            if (cnt < 2) {
                ret.emplace_back(active);
                continue;
            }
            // [left, right) -> [left, right]
            right -= 1;
            int32_t left_len =
                std::min(zero_bounds[left].second, as<int32_t>(right_idx))
                - std::max(zero_bounds[left].first, as<int32_t>(left_idx));
            int32_t right_len =
                std::min(zero_bounds[right].second, as<int32_t>(right_idx))
                - std::max(zero_bounds[right].first, as<int32_t>(left_idx));
            if (cnt == 2) {
                ret.emplace_back(active + left_len + right_len);
                continue;
            }
            // check fully included zeros only
            left += 1;
            right -= 1;
            int32_t added =
                std::max(left_len + zeros[left], right_len + zeros[right]);
            if (right > left) {
                added = std::max(added, rmq(left, right));
            }
            ret.emplace_back(added + active);
        }
        return ret;
    }
};
