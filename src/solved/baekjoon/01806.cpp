/*==== Copyright 2025 Azruine ====*/

#include <iostream>
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
public:
    void solve() {
        cin >> _n >> _m;
        arr.resize(_n);
        for (auto& i : arr) {
            cin >> i;
        }
        size_t left = 0, right = 0;
        size_t min_len = _n + 1;
        size_t cur = 0;
        while (right < _n) {
            while (right < _n && cur < _m) {
                cur += arr[right++];
            }
            while (left < right && cur >= _m) {
                min_len = std::min(min_len, right - left);
                cur -= arr[left++];
            }
        }
        cout << (min_len == _n + 1 ? 0 : min_len) << '\n';
    }

private:
    size_t _n = 0, _m = 0;
    std::vector<size_t> arr;
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
