#include <vector>

class Solution {
public:
    int numberOfAlternatingGroups(std::vector<int>& colors, int k) {
        int n = colors.size();
        int ans = 0;
        int maxLen = 1;
        int l = 0, r = k - 1;
        int curColor = colors[r];
        for (int cur = r - 1; cur >= l; cur--) {
            if (colors[cur] != curColor) {
                curColor = colors[cur];
                maxLen++;
            } else
                break;
        }
        curColor = colors[r];
        for (int i = r; i < r + n; i++) {
            if (maxLen == k) ans++;
            if (colors[(i + 1) % n] == curColor)
                maxLen = 1;
            else if (maxLen < k)
                maxLen++;
            curColor = colors[(i + 1) % n];
        }
        return ans;
    }
};