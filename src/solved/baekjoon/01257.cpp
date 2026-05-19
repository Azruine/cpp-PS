/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <utility>

using std::cin, std::cout;

namespace {
inline void fastio() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

#include <algorithm>
#include <queue>
#include <vector>

class Solver {
    static std::pair<int64_t, std::vector<int32_t>> read() {
        int64_t ret_m = 0;
        size_t n = 0;
        std::vector<int32_t> ret_coins;
        cin >> ret_m >> n;
        ret_coins.resize(n, 0);
        for (auto& coin : ret_coins) {
            cin >> coin;
        }
        return {ret_m, ret_coins};
    }
    static int64_t get_min(int64_t m, std::span<int32_t const> coins) {
        int32_t max = std::ranges::max(coins);
        std::vector<int64_t> dists(max, std::numeric_limits<int64_t>::max());
        dists[0] = 0;
        std::priority_queue<std::pair<int64_t, int32_t>,
                            std::vector<std::pair<int64_t, int32_t>>,
                            std::greater<>>
            pq;
        pq.emplace(0, 0);
        while (!pq.empty()) {
            auto [cur_dist, cur_node] = pq.top();
            pq.pop();
            if (cur_dist > dists[cur_node]) {
                continue;
            }
            for (auto coin : coins) {
                if (coin == max) {
                    continue;
                }
                auto next_node = (cur_node + coin) % max;
                int64_t next_dist = cur_dist + (max - coin);
                if (next_dist >= dists[next_node]) {
                    continue;
                }
                dists[next_node] = next_dist;
                pq.emplace(next_dist, next_node);
            }
        }
        return (m + dists[m % max]) / max;
    }

public:
    static void solve() {
        auto [m, coins] = read();
        cout << get_min(m, coins);
    }
};

int main() {
    fastio();
    Solver::solve();
    return 0;
}
