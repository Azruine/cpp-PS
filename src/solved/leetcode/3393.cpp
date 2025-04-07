#include <bits/stdc++.h>
#define MOD 1'000'000'007
class Solution {
private:
    std::vector<std::vector<std::array<int, 16>>> dp;

public:
    int countPathsWithXorValue(std::vector<std::vector<int>> &grid, int k) {
        int n = static_cast<int>(grid.size());
        int m = static_cast<int>(grid[0].size());
        dp.assign(n, std::vector<std::array<int, 16>>(m, {0}));
        dp[0][0][grid[0][0]] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < 16; k++) {
                    if (i < n - 1) {
                        dp[i + 1][j][k ^ grid[i + 1][j]] = (dp[i + 1][j][k ^ grid[i + 1][j]] + dp[i][j][k]) % MOD;
                    }
                    if (j < m - 1) {
                        dp[i][j + 1][k ^ grid[i][j + 1]] = (dp[i][j + 1][k ^ grid[i][j + 1]] + dp[i][j][k]) % MOD;
                    }
                }
            }
        }
        return dp.back().back()[k];
    }
};