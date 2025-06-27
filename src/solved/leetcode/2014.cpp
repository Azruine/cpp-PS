/*==== Copyright 2025 Azruine ====*/

#include <array>
#include <cstdint>
#include <string>
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
    std::string longestSubsequenceRepeatedK(std::string const& str, int32_t k) {
        for (auto const& chr : str) {
            freq.at(as<size_t>(chr - 'a'))++;
        }
        std::vector<char> candidate{};
        for (size_t i = 0; i < ALPHA; i++) {
            if (freq.at(i) >= k) {
                candidate.push_back(as<char>(i + 'a'));
            }
        }
        std::vector<std::string> que;
        que.reserve(ALPHA);
        for (auto chr : candidate) {
            que.push_back({chr});
        }
        std::string ans{};
        while (!que.empty()) {
            auto cur = std::move(que.back());
            que.pop_back();
            if (cur.size() > ans.size() ||
                (cur.size() == ans.size() && cur > ans)) {
                ans = cur;
            }
            for (auto chr : candidate) {
                std::string next = cur + chr;
                if (isRepeated(str, next, k)) {
                    que.push_back(std::move(next));
                }
            }
        }
        return ans;
    }

private:
    constexpr static size_t ALPHA = 26;
    std::array<int32_t, ALPHA> freq{};
    static bool isRepeated(std::string const& str, std::string const& substr,
                           int32_t const& k) {
        size_t pos = 0;
        auto m = substr.length();
        int32_t match_cnt = 0;
        for (auto const& chr : str) {
            if (chr == substr[pos]) {
                pos++;
            }
            if (pos == m) {
                pos = 0;
                match_cnt++;
            }
        }
        return match_cnt >= k;
    }
};
