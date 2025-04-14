/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <print>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

using ll = int64_t;
using ull = uint64_t;
using ld = long double;
using point = std::pair<int, int>;

using std::cin, std::cout;

namespace {
inline void fastio() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
template <typename To, typename From>
constexpr To as(From from) {
    return static_cast<To>(std::forward<From>(from));
}
inline int get_taxi_distance(point const& point1, point const& point2) {
    return (std::abs(point1.first - point2.first) +
            std::abs(point1.second - point2.second));
}
}  // namespace

class Solver {
private:
    inline static std::unordered_map<char, point> const keyboard = {
        {'q', {0, 0}}, {'w', {0, 1}}, {'e', {0, 2}}, {'r', {0, 3}},
        {'t', {0, 4}}, {'y', {0, 5}}, {'u', {0, 6}}, {'i', {0, 7}},
        {'o', {0, 8}}, {'p', {0, 9}}, {'a', {1, 0}}, {'s', {1, 1}},
        {'d', {1, 2}}, {'f', {1, 3}}, {'g', {1, 4}}, {'h', {1, 5}},
        {'j', {1, 6}}, {'k', {1, 7}}, {'l', {1, 8}}, {'z', {2, 0}},
        {'x', {2, 1}}, {'c', {2, 2}}, {'v', {2, 3}}, {'b', {2, 4}},
        {'n', {2, 5}}, {'m', {2, 6}}};
    inline static std::unordered_set<char> const left = {
        'q', 'w', 'e', 'r', 't', 'a', 's', 'd', 'f', 'g', 'z', 'x', 'c', 'v'};

public:
    void solve() {
        char left_char{'\0'};
        char right_char{'\0'};
        cin >> left_char >> right_char;
        std::string target;
        cin >> target;
        auto time = as<int32_t>(target.length());
        for (auto& chr : target) {
            if (left.contains(chr)) {
                time +=
                    get_taxi_distance(keyboard.at(chr), keyboard.at(left_char));
                left_char = chr;
            } else {
                time += get_taxi_distance(keyboard.at(chr),
                                          keyboard.at(right_char));
                right_char = chr;
            }
        }
        std::print("{}", time);
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
