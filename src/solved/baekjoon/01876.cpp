/*==== Copyright 2025 Azruine ====*/

#include <cmath>
#include <iostream>
#include <numbers>
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
public:
    void solve() {
        cin >> n;
        while (n--) {
            read();
            double tan = std::tan(theta * radians);
            double lower = (-dist * std::sqrt((tan * tan) + 1.0) + tan * t) / X_dist;
            double upper = (dist * std::sqrt((tan * tan) + 1.0) + tan * t) / X_dist;
            if (std::ceil(lower) <= std::floor(upper)) {
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        }
    }

private:
    size_t n = 0;
    constexpr static double pi = std::numbers::pi;
    constexpr static double radians = pi / 180.0;
    constexpr static double dist = 16.0;
    constexpr static double X_dist = 85.0;
    double t = 0, theta = 0;
    void read() {
        cin >> t >> theta;
        t *= 100;
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
