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
#include <bit>
#include <cstdint>
#include <vector>

class Tree {
    int32_t n = 0;
    int32_t log = 0;
    std::vector<int32_t> parents;
    std::vector<int32_t> depths;

public:
    int32_t parent(int32_t level, int32_t node) const {
        return parents[(level * n) + node];
    }
    int32_t& parent(int32_t level, int32_t node) {
        return parents[(level * n) + node];
    }
    int32_t depth(int32_t node) const { return depths[node]; }
    int32_t max_depth() const { return std::ranges::max(depths); }

    void build(std::vector<std::vector<int32_t>> const& adj) {
        n = adj.size();
        log = std::bit_width(as<uint32_t>(n));
        depths.resize(n, 0);
        parents.resize(n * log, 0);
        std::vector<int32_t> stk;
        stk.reserve(n);
        std::vector<bool> visited(n, false);
        visited[0] = true;
        parent(0, 0) = 0;
        stk.emplace_back(0);

        while (!stk.empty()) {
            int32_t cur = stk.back();
            stk.pop_back();

            for (auto const& next : adj[cur]) {
                if (visited[next]) {
                    continue;
                }
                visited[next] = true;
                parent(0, next) = cur;
                depths[next] = depths[cur] + 1;
                stk.emplace_back(next);
            }
        }

        for (int32_t level = 1; level < log; level++) {
            for (int32_t node = 0; node < n; node++) {
                int32_t mid = parent(level - 1, node);
                parent(level, node) = parent(level - 1, mid);
            }
        }
    }

    int32_t lca(int32_t a, int32_t b) const {
        if (depths[a] < depths[b]) {
            std::swap(a, b);
        }
        int32_t diff = depths[a] - depths[b];

        for (int32_t level = 0; level < log; level++) {
            if (diff & (1 << level)) {
                a = parent(level, a);
            }
        }

        if (a == b) {
            return a;
        }

        for (int32_t level = log - 1; level >= 0; level--) {
            if (parent(level, a) != parent(level, b)) {
                a = parent(level, a);
                b = parent(level, b);
            }
        }
        return parent(0, a);
    }
};

class Solution {
    constexpr static int32_t MOD = 1'000'000'007;
    Tree tree;
    static int32_t pow(int32_t base, int32_t exp) {
        int64_t ret = 1;
        int64_t base64 = base % MOD;
        while (exp > 0) {
            if (exp & 1) {
                ret *= base64;
                ret %= MOD;
            }
            base64 *= base64;
            base64 %= MOD;
            exp >>= 1;
        }
        return as<int32_t>(ret);
    }

public:
    std::vector<int32_t> assignEdgeWeights(
        std::vector<std::vector<int32_t>>& edges,
        std::vector<std::vector<int32_t>>& queries) {
        size_t n = edges.size() + 1;
        std::vector<std::vector<int32_t>> adj;

        adj.resize(n);
        for (auto&& edge : edges) {
            adj[edge[0] - 1].emplace_back(edge[1] - 1);
            adj[edge[1] - 1].emplace_back(edge[0] - 1);
        }
        tree.build(adj);
        std::vector<int32_t> ret;
        ret.reserve(queries.size());
        for (auto query : queries) {
            int32_t a = query[0];
            int32_t b = query[1];
            if (a == b) {
                ret.emplace_back(0);
            } else {
                int32_t lca = tree.lca(a, b);
                int32_t dist =
                    tree.depth(a) + tree.depth(b) - (tree.depth(lca) * 2);
                ret.emplace_back(pow(2, dist - 1));
            }
        }
        return ret;
    }
    int32_t assignEdgeWeights(std::vector<std::vector<int32_t>>& edges) {
        size_t n = edges.size() + 1;
        std::vector<std::vector<int32_t>> adj;

        adj.resize(n);
        for (auto&& edge : edges) {
            adj[edge[0] - 1].emplace_back(edge[1] - 1);
            adj[edge[1] - 1].emplace_back(edge[0] - 1);
        }
        tree.build(adj);
        return pow(2, tree.max_depth() - 1);
    }
};
