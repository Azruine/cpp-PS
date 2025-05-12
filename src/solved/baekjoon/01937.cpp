#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

using std::cin, std::cout;

namespace {
void fastio() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}
template <typename To, typename From>
To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solver {
public:
    inline bool is_good(int32_t row, int32_t col) {
        return row >= 0 && row < as<int32_t>(n) && col >= 0 &&
               col < as<int32_t>(n);
    }
    int32_t get_dp(int32_t row, int32_t col) {
        if (dp[as<size_t>(row)][as<size_t>(col)] != -1) {
            return dp[as<size_t>(row)][as<size_t>(col)];
        }
        int32_t res = 1;
        for (int r : {-1, 0, 1}) {
            for (int c : {-1, 0, 1}) {
                if (std::abs(r) + std::abs(c) != 1) {
                    continue;
                }
                int32_t new_row{r + as<int32_t>(row)};
                int32_t new_col{c + as<int32_t>(col)};
                if (is_good(new_row, new_col) &&
                    map[as<size_t>(new_row)][as<size_t>(new_col)] >
                        map[as<size_t>(row)][as<size_t>(col)]) {
                    res = std::max(res, get_dp(new_row, new_col) + 1);
                }
            }
        }
        return dp[as<size_t>(row)][as<size_t>(col)] = res;
    }
    void solve() {
        cin >> n;
        map.assign(n, std::vector<int32_t>(n));
        dp.assign(n, std::vector<int32_t>(n, -1));
        for (auto& row : map) {
            for (auto& i : row) {
                cin >> i;
            }
        }
        int32_t ans = -1;
        for (auto row : std::views::iota(0, as<int32_t>(n))) {
            for (auto col : std::views::iota(0, as<int32_t>(n))) {
                ans = std::max(ans, get_dp(row, col));
            }
        }
        std::cout << ans;
    }

private:
    size_t n{0};
    std::vector<std::vector<int32_t>> map;
    std::vector<std::vector<int32_t>> dp;
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
