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
    int t, n;
    std::vector<int> data;
    std::vector<int> prefix;
    std::vector<std::vector<int>> dp;

public:
    Solver() {}
    ~Solver() {}
    void solve() {
        std::cin >> t;
        while (std::cin >> n) {
            data.clear();
            prefix.clear();
            dp.clear();
            prefix.resize(n);
            data.resize(n);
            dp.assign(n, std::vector<int>(n, -1));
            for (int i = 0; i < n; i++) {
                std::cin >> data[i];
                prefix[i] = data[i] + (i ? prefix[i - 1] : 0);
                dp[i][i] = 0;
            }
            std::function<int(int, int)> getDP = [&](int i, int j) -> int {
                if (i > j) std::swap(i, j);
                if (dp[i][j] != -1) return dp[i][j];
                int ret = INT_MAX;
                for (int k = i; k < j; k++) {
                    ret = std::min(getDP(i, k) + getDP(k + 1, j) + prefix[j] - (i ? prefix[i - 1] : 0), ret);
                }
                return dp[i][j] = ret;
            };
            std::cout << getDP(0, n - 1) << '\n';
        }
    }
};

int main() {
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}