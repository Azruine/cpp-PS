/*==== Copyright 2025 Azruine ====*/

#include <limits>
#include <string>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
public:
    int maxDiff(int num) {
        auto n = std::to_string(num).length();
        int max = std::numeric_limits<int>::min();
        int min = std::numeric_limits<int>::max();
        for (char x = '0'; x <= '9'; x++) {
            for (char y = '0'; y <= '9'; y++) {
                std::string temp = std::to_string(num);
                if (temp.front() == x && y == '0') {
                    continue;
                }
                for (auto& chr : temp) {
                    if (chr == x) {
                        chr = y;
                    }
                }

                auto val = std::stoi(temp);
                if (val == 0) {
                    continue;
                }
                max = std::max(max, val);
                min = std::min(min, val);
            }
        }
        return max - min;
    }
};
