/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <iostream>
#include <ranges>
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
template <typename T>
constexpr auto rng(T const& start, T const& sentinel, T const& step = 1) {
    return std::ranges::views::iota(start, sentinel) |
           std::ranges::views::stride(step);
}
}  // namespace

class Solver {
public:
    void solve() {
        cin >> n;
        arr.resize(n);
        for (auto& x : arr) {
            cin >> x;
        }
        lis.reserve(n);
        prev.resize(n, n);
        for (auto i : rng<size_t>(0, n)) {
            auto it = std::ranges::lower_bound(
                lis, arr[i],
                [&](size_t idx, int32_t val) { return arr[idx] < val; });
            auto pos = as<size_t>(std::distance(lis.begin(), it));

            if (pos == lis.size()) {
                lis.push_back(i);
            } else {
                lis[pos] = i;
            }

            if (pos > 0) {
                prev[i] = lis[pos - 1];
            }
        }
        res.reserve(lis.size());
        for (auto i = lis.back(); i != n; i = prev[i]) {
            res.push_back(arr[i]);
        }
        std::ranges::reverse(res);
        cout << res.size() << '\n';
    }

private:
    size_t n = 0;
    std::vector<int32_t> arr;
    std::vector<size_t> lis;
    std::vector<size_t> prev;
    std::vector<int32_t> res;
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
