#include <algorithm>
#include <ranges>
#include <vector>

using std::vector;
using std::views::iota;

class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = static_cast<int>(questions.size());
        vector<long long> dp(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) {
            int& score = questions[i][0];
            int& power = questions[i][1];

            int next_index = i + power + 1;
            if (next_index <= n) {
                dp[i] = std::max(dp[i], score + dp[next_index]);
            } else {
                dp[i] = std::max(dp[i], static_cast<long long>(score));
            }
            dp[i] = std::max(dp[i], dp[i + 1]);
        }
        return dp[0];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> q = {{3, 2}, {4, 3}, {4, 4}, {2, 5}};
    return sol.mostPoints(q);
}