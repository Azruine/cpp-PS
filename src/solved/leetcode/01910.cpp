#include <bits/stdc++.h>

class Solution
{
public:
    std::string removeOccurrences(std::string s, std::string part)
    {
        std::vector<char> st;
        std::vector<char> temp;
        int n = s.length();
        int m = part.length();
        for (int i = 0; i < n; i++)
        {
            char cur = s[i];
            st.push_back(cur);
            if (cur == part.back())
            {
                bool isPart = true;
                for (int j = m - 1; j >= 0; j--)
                {
                    if (st.empty())
                    {
                        isPart = false;
                        break;
                    }
                    char comp = st.back();
                    st.pop_back();
                    temp.push_back(comp);
                    if (comp != part[j])
                    {
                        isPart = false;
                        break;
                    }
                }
                if (isPart == false)
                {
                    while (!temp.empty())
                    {
                        st.push_back(temp.back());
                        temp.pop_back();
                    }
                }
                else
                    temp.clear();
            }
        }
        return std::string(st.begin(), st.end());
    }
};