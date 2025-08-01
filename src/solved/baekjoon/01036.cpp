/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <numeric>
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
    using Number = std::vector<int8_t>;
    constexpr static int8_t BASE = 36;
    constexpr static int8_t TEN = 10;
    uint64_t n = 0;
    int32_t k = 0;
    std::vector<Number> nums;
    void read() {
        cin >> n;
        nums.resize(n);
        std::string temp;
        for (auto& num : nums) {
            cin >> temp;
            auto len = temp.size();
            num.resize(len);
            for (auto i : iota(len)) {
                if (temp[i] >= 'A' && temp[i] <= 'Z') {
                    num[len - i - 1] = temp[i] - 'A' + TEN;
                } else {
                    num[len - i - 1] = temp[i] - '0';
                }
            }
        }
        cin >> k;
    }
    bool cmp(Number const& lhs, Number const& rhs) {
        if (lhs.size() != rhs.size()) {
            return lhs.size() < rhs.size();
        }

        for (size_t i = lhs.size() - 1; i < lhs.size(); i--) {
            if (lhs[i] != rhs[i]) {
                return lhs[i] < rhs[i];
            }
        }
        return false;
    }
    std::vector<int8_t> find_max() {
        std::array<Number, BASE> results = {};
        for (int8_t i : iota(BASE)) {
            auto copy = nums;
            for (auto& digit : copy | std::views::join) {
                if (digit == i) {
                    digit = BASE - 1;
                }
            }
            Number sum = {0};
            for (auto const& num : copy) {
                sum = add(sum, num);
            }
            results[as<size_t>(i)] = std::move(sum);
        }
        std::vector<int8_t> idx(BASE);
        std::ranges::iota(idx, 0);
        std::ranges::sort(idx, [&](int8_t lhs, int8_t rhs) {
            return cmp(results[as<size_t>(rhs)], results[as<size_t>(lhs)]);
        });

        std::vector<int8_t> ret;
        for (auto i : iota(k)) {
            ret.push_back(idx[as<size_t>(i)]);
        }
        return ret;
    }
    void swap(Number const& target) {
        for (auto& digit : nums | std::views::join) {
            for (auto const& t_digit : target) {
                if (digit == t_digit) {
                    digit = BASE - 1;
                }
            }
        }
    }
    Number& add(Number& lhs, Number const& rhs) {
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        auto max_len = std::max(lhs_len, rhs_len);
        lhs.resize(max_len + 1);
        int8_t carry = 0;
        for (auto i : iota(max_len)) {
            int8_t sum = carry;
            if (i < lhs_len) {
                sum += lhs[i];
            }
            if (i < rhs_len) {
                sum += rhs[i];
            }
            carry = sum / BASE;
            lhs[i] = sum % BASE;
        }
        if (carry > 0) {
            lhs[max_len] = carry;
        } else {
            lhs.resize(max_len);
        }
        return lhs;
    }
    void print(Number const& vec) {
        for (auto const& digit : std::ranges::reverse_view(vec)) {
            if (digit < TEN) {
                cout << as<char>(digit + '0');
            } else {
                cout << as<char>(digit - TEN + 'A');
            }
        }
        cout << '\n';
    }

public:
    void solve() {
        read();
        swap(find_max());
        auto res = std::ranges::fold_left(
            nums, Number{0},
            [&](Number acc, Number const& num) { return add(acc, num); });
        print(res);
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
