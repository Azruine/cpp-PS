/*==== Copyright 2025 Azruine ====*/

#include <queue>
#include <string>
#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
using alpha = std::pair<char, size_t>;
auto const cmp = [](alpha const& lhs, alpha const& rhs) {
    if (lhs.first != rhs.first) {
        return lhs.first > rhs.first;
    }
    return lhs.second < rhs.second;
};
using alpha_heap =
    std::priority_queue<alpha, std::vector<alpha>, decltype(cmp)>;
}  // namespace

class Solution {
public:
    std::string clearStars(std::string s) {
        removed.assign(s.size(), false);

        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] != '*') {
                heap.emplace(s[i], i);
            } else {
                while (!heap.empty() && removed[heap.top().second]) {
                    heap.pop();
                }
                if (!heap.empty()) {
                    removed[heap.top().second] = true;
                    heap.pop();
                }
            }
        }
        std::string result;
        for (size_t i = 0; i < s.size(); ++i)
            if (s[i] != '*' && !removed[i]) {
                result += s[i];
            }
        return result;
    }

private:
    alpha_heap heap;
    std::vector<bool> removed;
};
