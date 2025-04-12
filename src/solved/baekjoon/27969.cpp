#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <print>
#include <string>
#include <vector>

using ll = int64_t;
using ull = uint64_t;
using ld = long double;

using std::cin, std::cout;

namespace {
inline void fastio() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

template <typename To, typename From>
inline To as(From tar) {
    return static_cast<To>(tar);
}
}  // namespace

class Solver {
private:
    static int const ASON_SIZE = 8;
    static int const STR_SIZE = 12;
    static int const CHAR_SIZE = 1;
    static int const INT_SIZE = 8;

    int ans = 0;
    std::string str;
    std::vector<std::string> stk;

public:
    void solve() {
        while (cin >> str) {
            // start ASON
            if (str == "[") {
                stk.push_back(str);
                continue;
            }

            // end ASON
            if (str == "]") {
                stk.pop_back();
                ans += ASON_SIZE;
                continue;
            }

            // integer
            if (std::all_of(str.begin(), str.end(), [](char chr) { return std::isdigit(chr); })) {
                ans += INT_SIZE;
                continue;
            }

            // string
            if (std::all_of(str.begin(), str.end(), [](char chr) { return std::isalpha(chr); })) {
                ans += STR_SIZE;
                ans += as<int32_t>(str.size()) * CHAR_SIZE;
                continue;
            }

            // at this point, something is wrong
            std::cerr << "Something is wrong\n";
        }
        assert(stk.empty());
        std::print("{}", ans);
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
