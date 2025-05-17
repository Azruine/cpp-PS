/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <print>
#include <ranges>
#include <string>
#include <unordered_set>
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

class Solver {
private:
    size_t n{0};
    size_t m{0};
    std::unordered_set<std::string> keywords;

public:
    void solve() {
        cin >> n >> m;
        std::string key;
        std::string temp;
        while (n--) {
            cin >> key;
            keywords.insert(key);
        }
        cin.ignore();
        while (m--) {
            std::getline(cin, temp);
            for (auto&& part : temp | std::views::split(',')) {
                keywords.erase(std::string(part.begin(), part.end()));
            }
            std::println("{}", keywords.size());
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
