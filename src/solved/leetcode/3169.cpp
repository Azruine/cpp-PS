#include <algorithm>
#include <vector>

class Solution {
public:
    int countDays(int days, std::vector<std::vector<int>> &meetings) {
        std::sort(meetings.begin(), meetings.end(),
                  [](const std::vector<int> &a, const std::vector<int> &b) {
                      for (int i = 0; i < a.size(); i++) {
                          if (a[i] == b[i]) continue;
                          return a[i] < b[i];
                      }
                      return true;
                  });
        std::vector<std::pair<int, int>> x;
        int start = -1, end = -1;
        for (auto &m : meetings) {
            if (start == -1 && end == -1) {
                start = m[0], end = m[1];
                continue;
            }
            if (end >= m[0])
                end = std::max(m[1], end);
            else {
                x.emplace_back(start, end);
                start = m[0], end = m[1];
            }
        }
        if (start != -1 && end != -1) x.emplace_back(start, end);
        int ans = days;
        std::for_each(x.begin(), x.end(), [&ans](std::pair<int, int> &m) {
            ans -= m.second - m.first + 1;
        });
        return std::max(0, ans);
    }
};

int main() {
    int d = 57;
    std::vector<std::vector<int>> m = {{3, 49},  {23, 44}, {21, 56}, {26, 55},
                                       {23, 52}, {2, 9},   {1, 48},  {3, 31}};
    Solution sol;
    sol.countDays(d, m);
    return 0;
}