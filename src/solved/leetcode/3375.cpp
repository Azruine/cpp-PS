#include <algorithm>
#include <vector>

using std::vector;

class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());
        nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
        if (nums.front() < k)
            return -1;
        else if (nums.front() == k)
            return nums.size() - 1;
        else
            nums.size();
    }
};