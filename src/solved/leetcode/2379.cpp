#include <string>
#include <algorithm>

class Solution {
public:
    int minimumRecolors(std::string blocks, int k) {
        int n = static_cast<int>(blocks.length());
        int min = 10000;
        for (int i = 0; i <= n - k; i++) {
            int cnt = 0;
            for (int j = i; j < i + k; j++) {
                if (blocks[j] == 'W') cnt++;
            }
            min = std::min(min, cnt);
        }
        return min;
    }
};