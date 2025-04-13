/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <print>
#include <ranges>
#include <string>
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
constexpr To as(From from) {
    return static_cast<To>(from);
}
}  // namespace

class Solver {
private:
    size_t static constexpr MAX_STRING = 1'800'100;
    size_t n = 0;
    int temp = 0;
    int calculated_res = 0;
    int min = std::numeric_limits<int32_t>::max();

    std::string ans;
    std::vector<int> data;

public:
    void solve() {
        cin >> n;
        cin >> min;
        ans.reserve(MAX_STRING);
        ans.append(std::format("{}", calculated_res));
        for ([[maybe_unused]] auto i : std::views::iota(size_t{1}, n)) {
            cin >> temp;
            calculated_res = std::max(calculated_res, temp - min);
            min = std::min(min, temp);
            ans.append(std::format(" {}", calculated_res));
        }
        std::print("{}", ans);
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
