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
        read();
        cout << get_result();
    }

private:
    size_t n{0};
    int32_t target{0};
    std::vector<int32_t> nums;
    void read() {
        cin >> n >> target;
        nums.resize(n);
        for (auto& num : nums) {
            cin >> num;
        }
    }
    size_t get_result() const {
        size_t ret{0};
        for (size_t i{0}; i < (1U << n); i++) {
            int32_t sum{0};
            bool is_valid{false};
            for (size_t j{0}; j < n; j++) {
                if (i & (1 << j)) {
                    sum += nums[j];
                    is_valid = true;
                }
            }
            if (is_valid && sum == target) {
                ret++;
            }
        }
        return ret;
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
