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

#include <array>
#include <cstdint>
#include <vector>

class Solution {
    constexpr static size_t MAX = 16;
    constexpr static auto pow = []() {
        std::array<int64_t, MAX> ret = {};
        for (size_t i = 0; i < MAX; i++) {
            ret[i] = 1LL << (i * 2);
        }
        return ret;
    }();
    constexpr static auto prefix = []() {
        std::array<int64_t, MAX> ret = {};
        ret[0] = 0;
        auto floor_sum = [](int x) {
            auto left = pow[as<size_t>(x - 1)];
            auto right = pow[as<size_t>(x)] - 1;
            auto cnt = right - left + 1;
            return cnt * x;
        };
        for (size_t i = 1; i < MAX; i++) {
            ret[i] = ret[i - 1] + floor_sum(as<int32_t>(i));
        }
        return ret;
    }();
    constexpr static int log(int x) {
        if (x == 0) {
            return 1;
        }
        auto ret = std::bit_width(as<uint32_t>(x)) + 1;
        return (ret >> 1);
    }
    int64_t solve_query(std::vector<int>& query) {
        auto left_log = log(query[0]);
        auto right_log = log(query[1]);
        int64_t ret =
            prefix[as<size_t>(right_log)] - prefix[as<size_t>(left_log - 1)];
        auto left_offset = query[0] - pow[as<size_t>(left_log - 1)];
        auto right_offset = pow[as<size_t>(right_log)] - query[1] - 1;
        ret -= left_offset * left_log;
        ret -= right_offset * right_log;
        return (ret + 1) / 2;
    }

public:
    int64_t minOperations(std::vector<std::vector<int>>& queries) {
        int64_t ret = 0;
        for (auto& query : queries) {
            ret += solve_query(query);
        }
        return ret;
    }
};
