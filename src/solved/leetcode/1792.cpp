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
#include <cassert>
#include <vector>

class Solution {
    static constexpr auto cmp = [](auto const& lhs, auto const& rhs) -> bool {
        auto den_a = as<double>(lhs[1]);
        auto den_b = as<double>(rhs[1]);
        auto num_a = as<double>(lhs[0]);
        auto num_b = as<double>(rhs[0]);
        return (den_a - num_a) * (den_b * (den_b + 1)) <
               (den_b - num_b) * (den_a * (den_a + 1));
    };

public:
    double maxAverageRatio(std::vector<std::vector<int>>& classes,
                           int extraStudents) {
        std::vector<std::array<int, 2>> arr;
        arr.reserve(classes.size());
        for (auto const& cls : classes) {
            arr.push_back({cls[0], cls[1]});
        }
        std::ranges::make_heap(arr, cmp);
        while (extraStudents--) {
            std::ranges::pop_heap(arr, cmp);
            auto& cls = arr.back();
            cls[0] += 1;
            cls[1] += 1;
            std::ranges::push_heap(arr, cmp);
        }
        double ans = 0.0;
        return std::ranges::fold_left(arr, ans,
                                      [](auto sum, auto const& cls) {
                                          return sum + (as<double>(cls[0]) / cls[1]);
                                      }) / as<double>(arr.size());
    }
};
