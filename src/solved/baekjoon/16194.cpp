#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

struct HashPair {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

class Solver {
private:
    int n;
    std::vector<int> cost;

public:
    Solver() {}
    ~Solver() {}
    void solve() {
        std::cin >> n;
        cost.resize(n + 1);
        cost[0] = 0;
        for (int i = 1; i <= n; i++) std::cin >> cost[i];
        std::vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        dp[1] = cost[1];
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                dp[i] = std::min(dp[i], dp[i - j] + cost[j]);
            }
        }
        std::cout << dp[n];
        return;
    }
};

int main() {
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}