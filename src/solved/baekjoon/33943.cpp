/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

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

class Solver {
public:
    void solve() {
        cin >> n >> m;
        if (n == 0 && m != 0) {
            cout << -1 << '\n';
            return;
        }
        if (m == 0) {
            cout << 0 << '\n';
            return;
        }
        coins.resize(n);
        for (auto& coin : coins) {
            cin >> coin;
            queue.push(coin);
            depth_map[coin] = 1;
        }
        while (!queue.empty()) {
            int32_t cur = queue.front();
            queue.pop();
            size_t cur_depth = depth_map[cur];
            if (cur == m) {
                cout << cur_depth << '\n';
                return;
            }
            for (const auto& coin : coins) {
                int32_t next = cur + coin;
                if (!depth_map.contains(next) && std::abs(next) <= 2'000'000) {
                    depth_map[next] = cur_depth + 1;
                    queue.push(next);
                }
            }
        }
        cout << -1 << '\n';
    }

private:
    size_t n{0};
    int32_t m{0};
    std::vector<int32_t> coins;
    std::unordered_map<int32_t, size_t> depth_map;
    std::queue<int32_t> queue;
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
