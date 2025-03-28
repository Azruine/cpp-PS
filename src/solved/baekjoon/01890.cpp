#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver {
private:
    int n;
    std::vector<std::vector<int>> grid;

public:
    Solver() {}
    ~Solver() {}
    void solve() {
        std::cin >> n;
        grid.resize(n, std::vector<int>(n));
        for (auto& v : grid)
            for (auto& i : v) std::cin >> i;
        std::vector<std::vector<ll>> dp(n, std::vector<ll>(n, 0));
        dp[0][0] = 1ll;
        for (int row : std::ranges::iota_view(0, n)) {
            for (int col : std::ranges::iota_view(0, n)) {
                int dist = grid[row][col];
                if (dist == 0) continue;
                if (row + dist < n) dp[row + dist][col] += dp[row][col];
                if (col + dist < n) dp[row][col + dist] += dp[row][col];
            }
        }
        std::print("{}\n", dp[n - 1][n - 1]);
    }
};

int main() {
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}