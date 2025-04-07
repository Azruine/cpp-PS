#include <bits/stdc++.h>

class Solution {
public:
    bool checkValidCuts(int n, std::vector<std::vector<int>>& rectangles) {
        // x axis
        std::sort(rectangles.begin(), rectangles.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {
                      return (a[0] == b[0] ? a[2] < b[2] : a[0] < b[0]);
                  });
        std::vector<std::pair<int, int>> x;
        int start = -1, end = -1;
        for (auto& v : rectangles) {
            if (start == -1 && end == -1) {
                start = v[0], end = v[2];
                continue;
            }
            if (end > v[0])
                end = std::max(v[2], end);
            else {
                x.emplace_back(start, end);
                start = v[0], end = v[2];
            }
        }
        x.emplace_back(start, end);
        if (x.size() > 2) return true;
        // y axis
        std::sort(rectangles.begin(), rectangles.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {
                      return (a[1] == b[1] ? a[3] < b[3] : a[1] < b[1]);
                  });
        std::vector<std::pair<int, int>> y;
        start = -1, end = -1;
        for (auto& v : rectangles) {
            if (start == -1 && end == -1) {
                start = v[1], end = v[3];
                continue;
            }
            if (end > v[1])
                end = std::max(v[3], end);
            else {
                y.emplace_back(start, end);
                start = v[1], end = v[3];
            }
        }
        y.emplace_back(start, end);
        if (y.size() > 2) return true;
        return false;
    }
};