/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <ranges>
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
struct Rng {
    template <typename Start, typename End, typename Step = Start>
    constexpr auto operator()(Start start, End end,
                              Step step = 1) const noexcept {
        return std::views::iota(start, end) | std::views::stride(step);
    }
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
constexpr Rng rng{};
#pragma GCC diagnostic pop
}  // namespace

class Solver {
public:
    void solve() {}

private:
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
