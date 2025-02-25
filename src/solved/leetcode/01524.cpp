#include <bits/stdc++.h>

class Solution {
public:
    int numOfSubarrays(std::vector<int>& arr) {
        int odd = 0, even = 0, ans = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] & 1) {
                std::swap(odd, even);
                odd++;
            } else {
                even++;
            }
            ans = (ans + odd) % 1'000'000'007;
        }
        return ans;
    }
};