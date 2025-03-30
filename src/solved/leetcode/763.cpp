#include <array>
#include <string>
#include <vector>

class Solution {
public:
    std::array<int, 26> index;
    int getFartherst(std::string const& s, char const c) {
        if (index[c - 'a'] != -1) return index[c];
        int l = s.length();
        for (int i = l - 1; i >= 0; i--)
            if (s[i] == c) return index[c - 'a'] = i;
        return -1;
    }

    std::vector<int> partitionLabels(std::string s) {
        index.fill(-1);
        std::vector<int> ans;
        int l = s.length();
        int start = 0;
        while (start < l) {
            int end = getFartherst(s, s[start]);
            int j = start + 1;
            while (j < end) end = std::max(end, getFartherst(s, s[j++]));
            ans.push_back(end - start + 1);
            start = end + 1;
        }

        return ans;
    }
};