/*==== Copyright 2025 Azruine ====*/

#include <iostream>
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
}  // namespace

#include <string>
#include <vector>

class Solver {
    std::string str1, str2;
    std::vector<int32_t> forward(size_t a_l, size_t a_r, size_t b_l,
                                 size_t b_r) {
        size_t m = b_r - b_l;
        std::vector<int32_t> dp(m + 1, 0);
        for (size_t i = a_l; i < a_r; i++) {
            int32_t dia = 0;
            for (size_t j = 0; j < m; j++) {
                int32_t old = dp[j + 1];
                if (str1[i] == str2[b_l + j]) {
                    dp[j + 1] = dia + 1;
                } else {
                    dp[j + 1] = std::max(dp[j + 1], dp[j]);
                }
                dia = old;
            }
        }
        return dp;
    }
    std::vector<int32_t> backward(size_t a_l, size_t a_r, size_t b_l,
                                  size_t b_r) {
        size_t m = b_r - b_l;
        std::vector<int32_t> dp(m + 1, 0);
        for (size_t i = a_r - 1; i >= a_l && i < a_r; i--) {
            int32_t dia = 0;
            for (size_t j = m - 1; j < m; j--) {
                int32_t old = dp[j];
                if (str1[i] == str2[b_l + j]) {
                    dp[j] = dia + 1;
                } else {
                    dp[j] = std::max(dp[j + 1], dp[j]);
                }
                dia = old;
            }
        }
        return dp;
    }
    size_t find_split(size_t a_mid, size_t a_r, size_t b_l, size_t b_r,
                      std::vector<int32_t> const& front) {
        size_t m = b_r - b_l;
        std::vector<int32_t> dp(m + 1, 0);
        size_t split = 0;
        int32_t best = front[0];

        for (size_t i = a_r; i-- > a_mid;) {
            int32_t dia = 0;
            for (size_t j = m; j-- > 0;) {
                int32_t old = dp[j];
                if (str1[i] == str2[b_l + j]) {
                    dp[j] = dia + 1;
                } else {
                    dp[j] = std::max(dp[j], dp[j + 1]);
                }
                dia = old;
            }
        }
        for (size_t k = 0; k <= m; k++) {
            int32_t cur = front[k] + dp[k];
            if (cur > best) {
                best = cur;
                split = k;
            }
        }
        return split;
    }
    void build_lcs(size_t a_l, size_t a_r, size_t b_l, size_t b_r,
                   std::string& lcs) {
        if (a_l == a_r || b_l == b_r) {
            return;
        }
        if (a_r == a_l + 1) {
            for (size_t i = b_l; i < b_r; i++) {
                if (str1[a_l] == str2[i]) {
                    lcs.push_back(str1[a_l]);
                    return;
                }
            }
            return;
        }
        size_t a_mid = (a_l + a_r) / 2;
        size_t split = 0;
        {
            auto front = forward(a_l, a_mid, b_l, b_r);
            split = find_split(a_mid, a_r, b_l, b_r, front);
        }
        build_lcs(a_l, a_mid, b_l, b_l + split, lcs);
        build_lcs(a_mid, a_r, b_l + split, b_r, lcs);
    }

public:
    void solve() {
        cin >> str1 >> str2;
        std::string lcs;
        build_lcs(0, str1.size(), 0, str2.size(), lcs);
        cout << lcs.size() << '\n';
        cout << lcs;
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
