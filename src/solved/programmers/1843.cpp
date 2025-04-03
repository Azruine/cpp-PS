#include <functional>
#include <limits>
// #include <ranges>
#include <string>
#include <vector>
using std::numeric_limits;
using std::vector, std::string;
// using std::views::iota;

std::vector<int> iota(int start, int end) {
    std::vector<int> result;
    for (int i = start; i < end; ++i) {
        result.push_back(i);
    }
    return result;
}

int solution(vector<string> arr) {
    int n = (arr.size() >> 1) + 1;
    // dp[i][j][0] = i ~ j max result
    // dp[i][j][1] = i ~ j min result
    constexpr int MIN = (1 << 30) * -1, MAX = (1 << 30);
    vector<vector<vector<int>>> dp(n,
                                   vector<vector<int>>(n, vector<int>(2, MIN)));
    for (int i : iota(0, n)) dp[i][i][0] = dp[i][i][1] = std::stoi(arr[2 * i]);

    std::function<int(int, int, int)> getDp = [&](int i, int j,
                                                  int k) -> int32_t {
        if (i > j) return k == 0 ? MIN : MAX;
        if (dp[i][j][k] != MIN) return dp[i][j][k];

        int res = (k == 0) ? MIN : MAX;
        if (k == 0) {  // return max
            for (int m : iota(i, j)) {
                int left = getDp(i, m, 0);
                int right = getDp(m + 1, j, 0);
                int rightMin = getDp(m + 1, j, 1);

                if (arr[m * 2 + 1] == "+")
                    res = std::max(res, left + right);
                else if (arr[m * 2 + 1] == "-")
                    res = std::max(res, left - rightMin);
            }
        } else if (k == 1) {  // return min
            for (int m : iota(i, j)) {
                int left = getDp(i, m, 1);
                int right = getDp(m + 1, j, 1);
                int rightMax = getDp(m + 1, j, 0);

                if (arr[m * 2 + 1] == "+")
                    res = std::min(res, left + right);
                else if (arr[m * 2 + 1] == "-")
                    res = std::min(res, left - rightMax);
            }
        }
        return dp[i][j][k] = res;
    };
    getDp(0, n - 1, 0);
    return dp[0][n - 1][0];
}
