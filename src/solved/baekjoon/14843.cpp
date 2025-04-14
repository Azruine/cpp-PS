/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <print>
#include <utility>
#include <vector>

using ll = int64_t;
using ull = uint64_t;
using ld = long double;

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
private:
    static constexpr int32_t HUNDRED = 100;
    static constexpr int32_t GOD = 15;
    int32_t n{0}, a{0}, t{0}, m{0}, p{0};
    double s{0};
    std::vector<double> scores;

public:
    void solve() {
        cin >> n;
        ld score{0};
        while (n--) {
            cin >> s >> a >> t >> m;
            score += (s * (a + 1) * (t + m)) / (4 * a * t);
        }
        cin >> p;
        scores.resize(as<size_t>(p));
        int32_t rank = 1;
        for (auto& score_ : scores) {
            cin >> score_;
            if (score_ >= score) {
                rank++;
            }
        }
        if (rank * HUNDRED <= (p + 1) * GOD) {
            std::print("The total score of Younghoon \"The God\" is {0:.2f}.",
                       score);
        } else {
            std::print("The total score of Younghoon is {0:.2f}.", score);
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
