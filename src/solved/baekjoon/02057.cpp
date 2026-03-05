/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <utility>

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
    constexpr static size_t MAX = 21;
    constexpr static std::array<uint64_t, MAX> fact = []() {
        std::array<uint64_t, 21> fact = {{}};
        fact[0] = 1;
        for (uint64_t i = 1; i < MAX; i++) {
            fact[i] = fact[i - 1] * i;
        }
        return fact;
    }();

public:
    void solve() {
        uint64_t n = 0;
        cin >> n;
        bool used = false;
        for (auto i = MAX - 1; i < MAX; i--) {
            if (fact[i] <= n) {
                n -= fact[i];
                used = true;
            }
        }
        cout << (n == 0 && used ? "YES" : "NO");
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
