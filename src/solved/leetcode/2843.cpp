#include <numeric>
#include <ranges>
#include <string>

namespace {
template <typename To, typename From>
inline To as(From value) {
    return static_cast<To>(value);
}

}  // namespace

class Solution {
public:
    static bool isSymmetric(std::string& str) {
        int len = as<int>(str.length());
        if (len % 2) {
            return false;
        }
        int front = std::accumulate(str.begin(), str.begin() + len / 2, 0);
        int back = std::accumulate(str.begin() + len / 2, str.end(), 0);
        return front == back;
    }
    int countSymmetricIntegers(int low, int high) {
        int cnt = 0;
        for (int i : std::views::iota(low, high + 1)) {
            std::string str = std::to_string(i);
            if (isSymmetric(str)) {
                cnt++;
            }
        }
        return cnt;
    }
};