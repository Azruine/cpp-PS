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

#include <algorithm>
#include <vector>

class Solution {
    bool is_good(std::vector<std::vector<int32_t>>& edges, size_t idx) {
        size_t n = edges.size();
        std::vector<std::vector<size_t>> children(n);
        std::vector<int32_t> indegree(n);
        for (size_t i = 0; i < n; i++) {
            if (i == idx) {
                continue;
            }
            children[edges[i][0] - 1].emplace_back(edges[i][1] - 1);
            indegree[edges[i][1] - 1] += 1;
            if (indegree[edges[i][1] - 1] > 1) {
                return false;
            }
        }
        std::vector<bool> visited(n, false);
        std::vector<size_t> stk;
        size_t root = n;
        for (size_t i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                if (root != n) {
                    return false;
                }
                root = i;
            }
        }
        if (root == n) {
            return false;
        }
        stk.reserve(n);
        stk.emplace_back(root);
        visited[root] = true;
        while (!stk.empty()) {
            auto cur = stk.back();
            stk.pop_back();
            for (auto next : children[cur]) {
                if (visited[next]) {
                    return false;
                }
                visited[next] = true;
                stk.emplace_back(next);
            }
        }
        return std::ranges::count(visited, false) == 0;
    }

public:
    std::vector<int32_t> findRedundantDirectedConnection(
        std::vector<std::vector<int32_t>>& edges) {
        size_t n = edges.size();
        for (size_t i = n; i > 0; i--) {
            if (is_good(edges, i - 1)) {
                return edges[i - 1];
            }
        }
        std::unreachable();
    }
};
