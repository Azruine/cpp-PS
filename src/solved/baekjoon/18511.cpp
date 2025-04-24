/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <print>
#include <vector>

using std::cin, std::cout;

namespace {
inline void fastio() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
}  // namespace

class Solver {
private:
    static constexpr int32_t BASE = 10;
    int32_t n{0};
    size_t k{0};
    std::vector<int32_t> number;

public:
    void solve() {
        cin >> n >> k;
        number.resize(k);
        std::ranges::for_each(number, [](int32_t& i) { cin >> i; });
        std::ranges::sort(number, std::less<>());
        int32_t max{std::numeric_limits<int32_t>::min()};
        int32_t cur{0};
        std::vector<int> stk{number};
        while (!stk.empty()) {
            cur = stk.back();
            stk.pop_back();
            max = std::max(max, cur);
            std::ranges::for_each(number, [&](int32_t& i) {
                int32_t next = (cur * BASE) + i;
                if (next <= n) {
                    stk.push_back(next);
                }
            });
        }
        std::print("{}", max);
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
