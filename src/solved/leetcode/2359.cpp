/*==== Copyright 2025 Azruine ====*/

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
    int closestMeetingNode(std::vector<int32_t>& edges, int32_t node1,
                           int32_t node2) {
        std::vector<std::pair<size_t, int32_t>> stk;
        stk.emplace_back(node1, 0);
        std::vector<int32_t> dist1(edges.size(), -1);
        std::vector<int32_t> dist2(edges.size(), -1);
        while (!stk.empty()) {
            auto [node, dist] = stk.back();
            stk.pop_back();
            if (dist1[node] != -1) {
                continue;
            }
            dist1[node] = dist;
            if (edges[node] != -1) {
                stk.emplace_back(edges[node], dist + 1);
            }
        }
        stk.emplace_back(node2, 0);
        while (!stk.empty()) {
            auto [node, dist] = stk.back();
            stk.pop_back();
            if (dist2[node] != -1) {
                continue;
            }
            dist2[node] = dist;
            if (edges[node] != -1) {
                stk.emplace_back(edges[node], dist + 1);
            }
        }
        int32_t min_dist{INT32_MAX};
        int32_t ans{-1};
        for (size_t i = 0; i < edges.size(); ++i) {
            if (dist1[i] != -1 && dist2[i] != -1) {
                int32_t max_dist = std::max(dist1[i], dist2[i]);
                if (max_dist < min_dist) {
                    min_dist = max_dist;
                    ans = as<int32_t>(i);
                } else if (max_dist == min_dist && ans > as<int32_t>(i)) {
                    ans = as<int32_t>(i);
                }
            }
        }
        return ans;
    }
};
