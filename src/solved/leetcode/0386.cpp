/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
public:
    std::vector<int32_t> lexicalOrder(int32_t n) {
        std::vector<int32_t> result;
        std::vector<int32_t> stk;
        for (int32_t i = std::min(9, n); i >= 1; i--) {
            stk.push_back(i);
        }
        while (!stk.empty()) {
            int32_t top = stk.back();
            stk.pop_back();
            result.push_back(top);
            for (int32_t i = 9; i >= 0; i--) {
                int32_t next = top * 10 + i;
                if (next <= n) {
                    stk.push_back(next);
                }
            }
        }

        return result;
    }
};
