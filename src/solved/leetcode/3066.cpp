class Solution
{
private:
    std::priority_queue<long long, std::vector<long long>, std::greater<long long>> pq;

public:
    int minOperations(vector<int> &nums, int k)
    {
        for (auto &i : nums)
            pq.push(i);
        int ret = 0;
        long long x, y;
        while (pq.top() < k)
        {
            x = pq.top();
            pq.pop();
            y = pq.top();
            pq.pop();
            pq.push(std::min(x, y) * 2 + std::max(x, y));
            ret++;
        }
        return ret;
    }
};