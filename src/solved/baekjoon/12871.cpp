/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <print>
#include <string>

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
}  // namespace

class Solver {
private:
    std::string str_1;
    std::string str_2;

public:
    void solve() {
        cin >> str_1 >> str_2;
        std::print("{:1d}", str_1 + str_2 == str_2 + str_1);
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
