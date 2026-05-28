/*==== Copyright 2025 Azruine ====*/

#include <ranges>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
struct Range {
    template <typename Sentinel>
    constexpr auto operator()(Sentinel sentinel) const noexcept {
        return std::views::iota(static_cast<Sentinel>(0), sentinel);
    }
    template <typename Start, typename Sentinel>
    constexpr auto operator()(Start start, Sentinel sentinel) const noexcept {
        return std::views::iota(start, sentinel);
    }
    template <typename Start, typename Sentinel, typename Step>
    constexpr auto operator()(Start start, Sentinel sentinel,
                              Step step) const noexcept {
        return std::views::iota(start, sentinel) | std::views::stride(step);
    }
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
constexpr Range _iota{};
#pragma GCC diagnostic pop
}  // namespace

#include <array>
#include <string>
#include <vector>

struct Node {
    std::array<int, 26> next;
    int best = -1;

    Node() { next.fill(-1); }
};
class Solution {
    bool is_better(std::vector<std::string> const& words, int32_t lhs,
                   int32_t rhs) {
        if (rhs == -1) {
            return true;
        }
        if (words[lhs].size() != words[rhs].size()) {
            return words[lhs].size() < words[rhs].size();
        }
        return lhs < rhs;
    }

public:
    std::vector<int> stringIndices(
        std::vector<std::string> const& wordsContainer,
        std::vector<std::string> const& wordsQuery) {
        std::vector<Node> trie;
        std::vector<int32_t> ret(wordsQuery.size(), 0);
        trie.emplace_back();
        size_t min_len_idx = 0;
        for (size_t i = 1; i < wordsContainer.size(); i++) {
            if (is_better(wordsContainer, i, min_len_idx)) {
                min_len_idx = i;
            }
        }
        trie[0].best = min_len_idx;

        for (size_t i = 0; i < wordsContainer.size(); i++) {
            int32_t cur = 0;
            auto const& word = wordsContainer[i];
            size_t n = word.size();
            for (size_t pos = n - 1; pos < n; pos--) {
                int32_t chr = word[pos] - 'a';
                if (trie[cur].next[chr] == -1) {
                    trie[cur].next[chr] = trie.size();
                    trie.emplace_back();
                }
                cur = trie[cur].next[chr];

                if (is_better(wordsContainer, i, trie[cur].best)) {
                    trie[cur].best = i;
                }
            }
        }

        for (size_t i = 0; i < wordsQuery.size(); i++) {
            int32_t cur = 0;
            int32_t ans = trie[0].best;
            auto const& query = wordsQuery[i];
            size_t n = query.size();
            for (size_t pos = n - 1; pos < n; pos--) {
                int32_t chr = query[pos] - 'a';
                if (trie[cur].next[chr] == -1) {
                    break;
                }
                cur = trie[cur].next[chr];
                ans = trie[cur].best;
            }
            ret[i] = ans;
        }
        return ret;
    }
};
