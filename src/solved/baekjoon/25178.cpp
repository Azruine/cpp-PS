/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
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
constexpr size_t ALPHA{26};
}  // namespace

class Solver {
public:
    void solve() {
        cin >> str1 >> str1 >> str2;
        for (auto& chr : str1) {
            count_1.at(as<size_t>(chr - 'a'))++;
        }
        for (auto& chr : str2) {
            count_2.at(as<size_t>(chr - 'a'))++;
        }
        bool flag = true;
        for (size_t i = 0; i < ALPHA; ++i) {
            if (count_1.at(i) != count_2.at(i)) {
                flag = false;
                break;
            }
        }
        if (str1.front() != str2.front() || str1.back() != str2.back()) {
            flag = false;
        }
        remove_vowels(str1);
        remove_vowels(str2);
        if (str1 != str2) {
            flag = false;
        }
        cout << (flag ? "YES" : "NO");
    }

private:
    std::string str1;
    std::string str2;
    std::array<size_t, ALPHA> count_1{};
    std::array<size_t, ALPHA> count_2{};
    // clang-format off
    static void remove_vowels(std::string& str) {
        str.erase(std::remove_if(str.begin(), str.end(), [](char chr) {
            return chr == 'a' || chr == 'e' || chr == 'i' || chr == 'o' || chr == 'u';
        }), str.end());
    }
    // clang-format on
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
