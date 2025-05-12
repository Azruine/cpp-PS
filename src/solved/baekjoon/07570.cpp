#include <algorithm>
#include <iostream>
#include <ranges>
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
    void solve() {
        cin >> n;
        children.resize(n, 0);
        dp.resize(n, -1);
        for (auto& child : children) {
            cin >> child;
            child--;
        }
        int32_t max_sub = -1;
        for (size_t i : std::views::iota(size_t{0}, n)) {
            if (i == 0 || children[i] == 0 || dp[children[i] - 1] == -1) {
                dp[children[i]] = 1;
            } else {
                dp[children[i]] = dp[children[i] - 1] + 1;
            }
            max_sub = std::max(max_sub, dp[children[i]]);
        }
        cout << as<int32_t>(n) - max_sub;
    }

private:
    size_t n{0};
    std::vector<size_t> children;
    std::vector<int32_t> dp;
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
