#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

using std::cin, std::cout;
using Point = std::pair<size_t, size_t>;

namespace {
inline void fastio() {
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
    void solve() {
        size_t loc{0};
        int32_t res{MAX};
        cur_table.fill({MAX, MAX, MAX, MAX, MAX});
        cur_table.front().front() = 0;
        next_table.fill({MAX, MAX, MAX, MAX, MAX});
        while (cin >> loc && loc != 0) {
            for (size_t left = 0; left < DDR; left++) {
                for (size_t right = 0; right < DDR; right++) {
                    int32_t cur_cost = cur_table.at(left).at(right);
                    if (cur_cost == MAX) {
                        continue;
                    }
                    if (left == loc || right == loc) {
                        next_table.at(left).at(right) = std::min(
                            next_table.at(left).at(right), cur_cost + 1);
                    } else {
                        if (right != loc) {
                            next_table.at(loc).at(right) =
                                std::min(next_table.at(loc).at(right),
                                         cur_cost + cost(left, loc));
                        }
                        if (left != loc) {
                            next_table.at(left).at(loc) =
                                std::min(next_table.at(left).at(loc),
                                         cur_cost + cost(right, loc));
                        }
                    }
                }
            }
            std::swap(cur_table, next_table);
            next_table.fill({MAX, MAX, MAX, MAX, MAX});
        }
        for (auto const& row : cur_table) {
            for (auto const& i : row) {
                res = std::min(i, res);
            }
        }
        cout << res;
    }

private:
    constexpr static int32_t MAX = 1'000'000'000;
    constexpr static size_t DDR = 5;
    std::array<std::array<int32_t, DDR>, DDR> cur_table;
    std::array<std::array<int32_t, DDR>, DDR> next_table;
    static int32_t cost(size_t const from, size_t const to) {
        int32_t ret{0};
        if (from == to) {
            ret = 1;
        } else if (from == 0) {
            ret = 2;
        } else if (from + 2 == to || to + 2 == from) {
            ret = 4;
        } else {
            ret = 3;
        }
        return ret;
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
