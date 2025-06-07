/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
#include <functional>
#include <queue>
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
    bool isPossible(std::vector<int32_t>& target) {
        int64_t sum{0};
        for (auto const& val : target) {
            pq.push(as<int64_t>(val));
            sum += as<int64_t>(val);
        }
        while (!pq.empty() && pq.top() > 1) {
            auto top{pq.top()};
            pq.pop();
            auto rest{sum - top};
            if (rest == 0 || rest >= top) {
                return false;
            }
            auto new_top(top % rest);
            if (new_top == 0) {
                new_top = rest;
            }
            pq.push(new_top);
            sum = rest + new_top;
        }
        return true;
    }

private:
    std::priority_queue<int64_t, std::vector<int64_t>, std::less<>> pq;
};
