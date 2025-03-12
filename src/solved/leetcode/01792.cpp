#include <bits/stdc++.h>

class Solution {
public:
    double maxAverageRatio(std::vector<std::vector<int>>& classes,
                           int extraStudents) {
        auto cmp = [](std::pair<int, int>& a, std::pair<int, int>& b) {
            double diff1 = (double)(a.first + 1) / (a.second + 1) - (double)a.first / a.second;
            double diff2 = (double)(b.first + 1) / (b.second + 1) - (double)b.first / b.second;
            return diff1 > diff2;
        };
        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>, decltype(cmp)>
            pq(cmp);
        for (auto& c : classes) {
            pq.push({c[0], c[1]});
        }
        while (extraStudents--) {
            auto [pass, total] = pq.top();
            pq.pop();
            pq.push({pass + 1, total + 1});
        }
        double res = 0;
        while (!pq.empty()) {
            auto [pass, total] = pq.top();
            pq.pop();
            res += (double)pass / total;
        }
        return res / classes.size();
    }
};