/*==== Copyright 2025 Azruine ====*/

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>
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
    std::vector<std::string> subjects = {"kor", "eng", "math"};
    std::vector<std::string> fruits = {"apple", "pear", "orange"};
    std::vector<std::string> colors = {"red", "blue", "green"};
    std::unordered_map<std::string, int32_t> counts;

    int32_t query(std::string const& subject, std::string const& fruit,
                  std::string const& color) {
        int32_t ret{0};
        const auto& subList =
            (subject == "-") ? subjects : std::vector<std::string>{subject};
        const auto& fruitList =
            (fruit == "-") ? fruits : std::vector<std::string>{fruit};
        const auto& colorList =
            (color == "-") ? colors : std::vector<std::string>{color};

        for (const auto& sub : subList) {
            for (const auto& fru : fruitList) {
                for (const auto& col : colorList) {
                    ret += counts[sub + fru + col];
                }
            }
        }
        return ret;
    }

public:
    void solve() {
        int32_t n{0};
        int32_t m{0};
        cin >> n >> m;
        std::string subject;
        std::string fruit;
        std::string color;
        while (n--) {
            cin >> subject >> fruit >> color;
            counts[subject + fruit + color]++;
        }
        while (m--) {
            cin >> subject >> fruit >> color;
            cout << query(subject, fruit, color) << '\n';
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
