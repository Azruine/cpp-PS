#include <functional>
#include <iostream>
#include <print>
#include <vector>

using ll = int64_t;
using ull = uint64_t;
using ld = long double;
using pair = std::pair<int, int>;

using std::cin, std::cout;

namespace {
inline void fastio() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

template <typename To, typename From>
inline To as(From target) {
    return static_cast<To>(target);
}

pair operator+(pair const& pair1, pair const& pair2) {
    return std::make_pair(pair1.first + pair2.first, pair1.second + pair2.second);
}
}  // namespace

class Solver {
private:
    static constexpr std::array<pair, 4> dir = {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};

    int row = 0;
    int col = 0;

    pair goal;
    std::vector<std::vector<int>> map;
    std::vector<std::vector<int>> dp;

    bool is_legit(pair const& node) const {
        return (node.first >= 0) && (node.first < row) && (node.second >= 0) && (node.second < col);
    }

    int const& get_node_value(pair const& node) const {
        return map.at(as<size_t>(node.first)).at(as<size_t>(node.second));
    }

public:
    void solve() {
        cin >> row >> col;
        map.assign(as<size_t>(row), std::vector<int>(as<size_t>(col), 0));
        dp.assign(as<size_t>(row), std::vector<int>(as<size_t>(col), -1));

        for (auto& i : map) {
            for (auto& j : i) {
                cin >> j;
            }
        }
        goal = std::make_pair(row - 1, col - 1);
        dp[0][0] = 1;

        std::function<int(pair const&)> get_dp = [&](pair const& cur_node) -> int {
            auto const& cur_row = as<size_t>(cur_node.first);
            auto const& cur_col = as<size_t>(cur_node.second);
            if (dp[cur_row][cur_col] != -1) {
                return dp[cur_row][cur_col];
            }
            int count = 0;
            for (auto const& d_node : dir) {
                auto prev_node = cur_node + d_node;
                if (is_legit(prev_node) && get_node_value(cur_node) < get_node_value(prev_node)) {
                    count += get_dp(prev_node);
                }
            }
            return dp[cur_row][cur_col] = count;
        };

        std::print("{}", get_dp(goal));
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}