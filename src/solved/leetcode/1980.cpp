#include <bits/stdc++.h>
class Solution {
public:
    std::string findDifferentBinaryString(std::vector<std::string>& nums) {
        std::string ans = "";
        int n = nums.front().length();
        for (int i = 0; i < n; i++) {
            ans += (nums[i][i] == '0' ? '1' : '0');
        }
        return ans;
    }
};