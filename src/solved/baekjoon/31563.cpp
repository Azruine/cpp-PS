/*==== Copyright 2025 Azruine ====*/

#include <cassert>
#include <iostream>
#include <print>
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
}  // namespace

class Solver {
private:
    std::vector<int32_t> data;
    std::vector<int64_t> prefix;
    int32_t n{0};
    size_t q{0};
    int32_t offset{0};
    int64_t query(size_t left, size_t right) {
        int64_t ret{0};
        left = (left + as<size_t>(offset)) % as<size_t>(n);
        right = (right + as<size_t>(offset)) % as<size_t>(n);
        if (left <= right) {
            ret = prefix[right + 1] - prefix[left];
        } else {
            ret = (prefix.back() - prefix[left]) +
                  (prefix[right + 1] - prefix[0]);
        }
        return ret;
    }
    void move_offset(int32_t value) {
        offset += value;
        if (offset < 0) {
            offset += n;
        } else if (offset >= n) {
            offset %= n;
        }
    }

public:
    void solve() {
        cin >> n >> q;
        data.resize(as<size_t>(n));
        prefix.assign(as<size_t>(n + 1), 0);
        for (auto i : std::views::iota(size_t{0}, as<size_t>(n))) {
            cin >> data[i];
            prefix[i + 1] = data[i] + prefix[i];
        }
        size_t type{0};
        int32_t temp{0};
        size_t left{0};
        size_t right{0};
        while (q--) {
            cin >> type;
            if (type == 1) {
                cin >> temp;
                move_offset(-temp);
            } else if (type == 2) {
                cin >> temp;
                move_offset(temp);
            } else if (type == 3) {
                cin >> left >> right;
                left--;
                right--;
                std::print("{}\n", query(left, right));
            }
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
