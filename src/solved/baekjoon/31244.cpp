/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cstddef>
#include <cstdint>
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
        std::string reverse{string.rbegin(), string.rend()};
        std::string concatenated{reverse + '#' + string};
        auto pi = build_prefix_function(concatenated);
        auto max_length = pi.back();
        std::string residue = string.substr(0, string.size() - max_length);
        std::ranges::reverse(residue);
        cout << string << residue;
    }

private:
    std::string string;
    void read() {
        char temp{0};
        while (cin >> temp && temp != '\n') {
            string.push_back(temp);
        }
    }
    std::vector<size_t> build_suffix(std::string const& str) {
        size_t n{str.size()};
        size_t k{1};
        std::vector<size_t> suffix(n, 0);
        std::vector<size_t> rank(n, 0);
        std::vector<size_t> temp(n, 0);
        for (size_t i{0}; i < n; i++) {
            suffix[i] = i;
            rank[i] = as<size_t>(str[i]);
        }

        auto cmp = [&](size_t a, size_t b) {
            if (rank[a] != rank[b]) {
                return rank[a] < rank[b];
            }
            return (a + k < n && b + k < n) ? rank[a + k] < rank[b + k] : a > b;
        };

        while (true) {
            std::ranges::sort(suffix, cmp);
            temp[as<size_t>(suffix[0])] = 0;
            for (size_t i{1}; i < n; i++) {
                temp[as<size_t>(suffix[i])] = temp[as<size_t>(suffix[i - 1])];
                if (cmp(suffix[i - 1], suffix[i])) {
                    temp[as<size_t>(suffix[i])] += 1;
                }
            }
            rank.swap(temp);
            if (rank[suffix[n - 1]] == n - 1) {
                break;
            }
            k <<= 1;
        }

        return suffix;
    }

    std::vector<size_t> build_lcp(std::string const& str,
                                  std::vector<size_t> const& suffix) {
        size_t n{str.size()};
        std::vector<size_t> rank(n, 0);
        std::vector<size_t> lcp(n, 0);

        for (size_t i{0}; i < n; i++) {
            rank[suffix[i]] = i;
        }

        size_t common_length{0};
        for (size_t i{0}; i < n; i++) {
            if (rank[i] > 0) {
                size_t j{suffix[rank[i] - 1]};
                while (i + common_length < n && j + common_length < n &&
                       str[i + common_length] == str[j + common_length]) {
                    common_length += 1;
                }
                lcp[rank[i] - 1] = common_length;
                if (common_length > 0) {
                    common_length -= 1;
                }
            }
        }
        return lcp;
    }

    std::vector<size_t> build_prefix_function(std::string const& str) {
        size_t n{str.size()};
        std::vector<size_t> prefix(n, 0);
        for (size_t i{1}; i < n; i++) {
            size_t j{prefix[i - 1]};
            while (j > 0 && str[i] != str[j]) {
                j = prefix[j - 1];
            }
            if (str[i] == str[j]) {
                j += 1;
            }
            prefix[i] = j;
        }
        return prefix;
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
