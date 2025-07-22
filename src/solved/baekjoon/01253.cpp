/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <unordered_set>
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
struct Rng {
    template <typename Start, typename End, typename Step = Start>
    constexpr auto operator()(Start start, End end,
                              Step step = 1) const noexcept {
        return std::views::iota(start, end) | std::views::stride(step);
    }
};

constexpr Rng rng{};
template <std::ranges::contiguous_range R>
    requires std::ranges::sized_range<R>
std::istream& operator>>(std::istream& is, R& container) {
    for (auto& elem : container) {
        is >> elem;
    }
    return is;
}
}  // namespace

class Solver {
public:
    void solve() {
        cin >> n;
        arr.resize(n);
        cin >> arr;
        for (auto& elem : arr) {
            freq[elem]++;
        }
        std::ranges::sort(arr);
        for (auto i : rng(0U, n)) {
            for (auto j : rng(i + 1, n)) {
                int32_t sum = arr[i] + arr[j];
                auto threshold = 1UL + (arr[i] == sum) + (arr[j] == sum);
                if (!freq.contains(sum) || freq[sum] < threshold) {
                    continue;
                }
                unique_sum.insert(sum);
            }
        }
        cout << std::ranges::fold_left(
            unique_sum, 0UL,
            [this](auto acc, int32_t sum) { return freq[sum] + acc; });
    }

private:
    size_t n = 0;
    std::vector<int32_t> arr;
    std::unordered_map<int32_t, size_t> freq;
    std::unordered_set<int32_t> unique_sum;
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
