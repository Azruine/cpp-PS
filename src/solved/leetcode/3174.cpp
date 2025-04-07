class Solution
{
public:
    std::string clearDigits(std::string s)
    {
        std::deque<char> dq;
        for (auto &c : s)
        {
            if (isalpha(c))
                dq.push_back(c);
            else if (isdigit(c) && !s.empty())
                dq.pop_back();
        }
        std::string ans = "";
        while (!dq.empty())
        {
            ans += dq.front();
            dq.pop_front();
        }
        return ans;
    }
};