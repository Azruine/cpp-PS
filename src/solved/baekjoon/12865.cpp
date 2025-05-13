/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <iostream>
#include <print>
#include <ranges>
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
private:
    size_t n{0};
    size_t k{0};
    std::vector<size_t> weight;
    std::vector<size_t> value;
    std::vector<size_t> dp;

public:
    void solve() {
        cin >> n >> k;
        weight.resize(n);
        value.resize(n);
        for (auto i : std::views::iota(size_t{0}, n)) {
            cin >> weight[i] >> value[i];
        }
        dp.resize(k + 1);
        for (auto i : std::views::iota(size_t{0}, n)) {
            for (size_t cur_weight = k; cur_weight >= weight[i]; cur_weight--) {
                dp[cur_weight] =
                    std::max(dp[cur_weight], dp[cur_weight - weight[i]] + value[i]);
            }
        }
        std::print("{}", dp[k]);
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
