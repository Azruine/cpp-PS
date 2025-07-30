/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <ranges>
#include <string>
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
struct Range {
    template <typename Sentinel>
    constexpr auto operator()(Sentinel sentinel) const noexcept {
        return std::views::iota(static_cast<Sentinel>(0), sentinel);
    }
    template <typename Start, typename Sentinel>
    constexpr auto operator()(Start start, Sentinel sentinel) const noexcept {
        return std::views::iota(start, sentinel);
    }
    template <typename Start, typename Sentinel, typename Step>
    constexpr auto operator()(Start start, Sentinel sentinel,
                              Step step) const noexcept {
        return std::views::iota(start, sentinel) | std::views::stride(step);
    }
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
constexpr Range iota{};
#pragma GCC diagnostic pop
}  // namespace

class Solver {
    size_t len1 = 0, len2 = 0;
    std::vector<int32_t> acc1, acc2;
    std::vector<int32_t> suffix_min, prefix_min;
    std::string str1, str2;
    void read() {
        cin >> str1 >> str2;
        len1 = str1.size();
        len2 = str2.size();
    }
    void fill(std::string const& str, std::vector<int32_t>& acc,
              size_t const& len) {
        acc.resize(len + 1, 0);
        for (auto i : iota(1UL, len + 1)) {
            acc[i] = acc[i - 1] + (str[i - 1] == '(' ? 1 : -1);
        }
    }
    void fill_suffix() {
        suffix_min.resize(len1 + 2, INT32_MAX);
        for (auto i : iota(0UL, len1 + 1) | std::views::reverse) {
            suffix_min[i] = std::min(suffix_min[i + 1], acc1[i]);
        }
    }
    void fill_prefix() {
        prefix_min.resize(len1 + 2, INT32_MAX);
        for (auto i : iota(0UL, len1 + 1)) {
            prefix_min[i + 1] = std::min(prefix_min[i], acc1[i]);
        }
    }

public:
    void solve() {
        read();
        fill(str1, acc1, len1);
        fill(str2, acc2, len2);
        fill_suffix();
        fill_prefix();

        auto min = *std::min_element(acc2.begin() + 1, acc2.end());
        auto last = acc2.back();
        int final = last + acc1.back();
        if (final != 0) {
            cout << 0;
            return;
        }
        for (auto i : iota(1UL, len1)) {
            if (prefix_min[i + 1] >= 0 && acc1[i] >= -min &&
                suffix_min[i + 1] >= -last) {
                cout << 1;
                return;
            }
        }
        cout << 0;
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
