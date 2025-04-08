#include <algorithm>
#include <vector>

using std::vector;

class Solution {
public:
    vector<int> arr;
    bool isFree(vector<int>& vec, int start) {
        std::fill(arr.begin(), arr.end(), 0);
        for (int i = start; i < vec.size(); i++) {
            if (arr[vec[i]]) return false;
            arr[vec[i]] += 1;
        }
        return true;
    }
    int minimumOperations(vector<int>& nums) {
        arr.assign(110, 0);
        int n = nums.size();
        int cnt = 0;
        for (; cnt < n; cnt += 3) {
            if (isFree(nums, cnt)) break;
        }
        return cnt / 3;
    }
};