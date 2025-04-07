#include <bits/stdc++.h>

class Solution {
public:
    int lenLongestFibSubseq(std::vector<int> &arr) {
        int n = static_cast<int>(arr.size());
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x = arr[j] - arr[i];
                if (x == arr[i]) continue;
                auto it = std::lower_bound(arr.begin(), arr.end(), x);
                auto idx = it - arr.begin();
                if (idx > i || arr[j] != arr[i] + arr[idx]) continue;
                dp[i][j] = dp[idx][i] + 1;
            }
        }
        int ans = 0;
        for (auto &v : dp)
            for (auto &i : v) ans = std::max(ans, i);
        return (ans == 0 ? 0 : ans + 2);
    }
};