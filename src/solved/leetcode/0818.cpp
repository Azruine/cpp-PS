/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
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

#include <queue>
#include <unordered_set>

struct PairHash {
    std::size_t operator()(const std::pair<int32_t, int32_t>& pair) const {
        return std::hash<int32_t>()(pair.first) ^
               (std::hash<int32_t>()(pair.second) << 1);
    }
};

class Solution {
    constexpr static int32_t MAX = 20'000;
    std::unordered_set<std::pair<int32_t, int32_t>, PairHash> visited;

public:
    int racecar(int target) {
        visited.insert({0, 1});
        std::queue<std::tuple<int32_t, int32_t, int32_t>> q;
        q.emplace(0, 1, 0);
        while (!q.empty()) {
            auto [pos, vel, depth] = q.front();
            q.pop();
            if (pos == target) {
                return depth;
            }
            auto acc_next = pos + vel;
            if (std::abs(acc_next) < MAX &&
                !visited.contains({acc_next, vel * 2})) {
                visited.insert({acc_next, vel * 2});
                q.emplace(acc_next, vel * 2, depth + 1);
            }
            auto rev_next = pos;
            auto rev_next_vel = vel > 0 ? -1 : 1;
            if (std::abs(rev_next) < MAX &&
                !visited.contains({rev_next, rev_next_vel})) {
                visited.insert({rev_next, rev_next_vel});
                q.emplace(rev_next, rev_next_vel, depth + 1);
            }
        }
        std::unreachable();
    }
};
