#include <iostream>
#include <utility>
#include <vector>

using std::cin, std::cout;

namespace {
inline void fastio() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}
template <typename To, typename From>
To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solver {
public:
    void solve() {
        cin >> n >> m;
        if (n <= m) {
            std::cout << n;
            return;
        }
        rides.resize(as<size_t>(m));
        for (auto& ride : rides) {
            cin >> ride;
        }
        int64_t left{0};
        int64_t right{60'000'000'100};
        while (left < right) {
            int64_t mid{(left + right) / 2};
            if (max_cap(mid) + m >= n) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        int64_t cnt = max_cap(left - 1) + m;
        for (size_t i = 0; i < as<size_t>(m); i++) {
            if (left % rides[i] == 0) {
                cnt++;
            }
            if (cnt == n) {
                std::cout << i + 1;
                return;
            }
        }
    }
    int64_t max_cap(int64_t time) {
        if (time <= 0) {
            return 0;
        }
        int64_t res{0};
        for (auto const& ride : rides) {
            res += time / ride;
        }
        return res;
    }

private:
    int32_t n{0};
    int32_t m{0};
    std::vector<int32_t> rides;
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
