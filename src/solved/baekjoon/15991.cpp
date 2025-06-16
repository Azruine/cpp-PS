/*==== Copyright 2025 Azruine ====*/

#include <iostream>
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
        cin >> t;
        while (t--) {
            cin >> n;
            query.push_back(n);
        }
        dp.resize(100'001, 0);
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 2;
        dp[4] = 3;
        dp[5] = 3;
        for (size_t i{6}; i <= 100'000; i++) {
            dp[i] = (dp[i - 2] + dp[i - 4] + dp[i - 6]) % MOD;
        }
        for (auto& q : query) {
            cout << dp[q] << '\n';
        }
    }

private:
    size_t t{0}, n{0};
    std::vector<size_t> query;
    std::vector<int64_t> dp;
    constexpr static int64_t MOD{1'000'000'009};
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
