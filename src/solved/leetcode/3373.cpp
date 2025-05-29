/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cstdint>
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
    std::vector<int32_t> maxTargetNodes(
        std::vector<std::vector<int32_t>>& edges1,
        std::vector<std::vector<int32_t>>& edges2) {
        size_t n{edges1.size() + 1};
        size_t m{edges2.size() + 1};

        std::vector<std::vector<int32_t>> graph1(n);
        std::vector<std::vector<int32_t>> graph2(m);
        for (auto& edge : edges1) {
            graph1[as<size_t>(edge[0])].push_back(edge[1]);
            graph1[as<size_t>(edge[1])].push_back(edge[0]);
        }
        for (auto& edge : edges2) {
            graph2[as<size_t>(edge[0])].push_back(edge[1]);
            graph2[as<size_t>(edge[1])].push_back(edge[0]);
        }

        int32_t even_node_1{0};
        int32_t odd_node_2{0};

        std::vector<bool> parity_vector(n, false);
        std::queue<std::pair<int32_t, int32_t>> queue;
        std::vector<bool> visited(n, false);

        queue.emplace(0, 0);
        visited[0] = true;
        parity_vector[0] = true;

        while (!queue.empty()) {
            auto [node, parity] = queue.front();
            queue.pop();
            if (parity == 0) {
                even_node_1 += 1;
                parity_vector[as<size_t>(node)] = true;
            }
            for (auto& neighbor : graph1[as<size_t>(node)]) {
                if (!visited[as<size_t>(neighbor)]) {
                    visited[as<size_t>(neighbor)] = true;
                    queue.emplace(neighbor, parity ^ 1);
                }
            }
        }

        visited.assign(m, false);
        queue.emplace(0, 0);
        visited[0] = true;
        while (!queue.empty()) {
            auto [node, parity] = queue.front();
            queue.pop();
            if (parity == 1) {
                odd_node_2 += 1;
            }
            for (auto& neighbor : graph2[as<size_t>(node)]) {
                if (!visited[as<size_t>(neighbor)]) {
                    visited[as<size_t>(neighbor)] = true;
                    queue.emplace(neighbor, parity ^ 1);
                }
            }
        }

        std::vector<int32_t> result(n, 0);
        int32_t max_nodes_2{std::max(odd_node_2, as<int32_t>(m) - odd_node_2)};
        for (size_t i{0}; i < n; ++i) {
            if (parity_vector[i]) {
                result[i] = even_node_1 + max_nodes_2;
            } else {
                result[i] = as<int32_t>(n) - even_node_1 + max_nodes_2;
            }
        }
        return result;
    }
};
