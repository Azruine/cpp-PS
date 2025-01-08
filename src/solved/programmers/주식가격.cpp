#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Seg
{
private:
    std::vector<int> data;
    int size;

public:
    Seg(){}
    Seg(int n)
    {
        size = n;
        data.assign(size << 1, INT_MAX);
    }
    void init(std::vector<int> v)
    {
        std::copy(v.begin(), v.end(), data.begin() + size);
    }
    void build()
    {
        for (int i = size - 1; i > 0; i--)
            data[i] = std::min(data[i << 1], data[i << 1 | 1]);
    }
    int query(int l, int r)
    {
        int res = INT_MAX;
        for (l += size, r += size; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = std::min(res, data[l++]);
            if (r & 1)
                res = std::min(res, data[--r]);
        }
        return res;
    }
};

vector<int> solution(vector<int> prices) {
    vector<int> answer;
    int n = static_cast<int>(prices.size());
    Seg seg = Seg(n);
    seg.init(prices);
    seg.build();
    for (int i = 0; i < n; i++)
    {
        int l = i + 1, r = n;
        while (l < r)
        {
            int mid = (l + r) >> 1;
            int midQuery = seg.query(i + 1, mid + 1);
            if (midQuery < prices[i])
                r = mid;
            else
                l = mid + 1;
        }
        answer.push_back((l == n ? l - i - 1 : l - i));
    }
    answer.back() = 0;
    return answer;
}