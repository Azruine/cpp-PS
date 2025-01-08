#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> priorities, int location) {
    std::vector<int> rem(10, 0);
    for (auto &p : priorities)
        rem[p]++;
    std::queue<std::pair<int, int>> q;
    for (int i = 0; i < static_cast<int>(priorities.size()); i++)
        q.push({i, priorities[i]});
    int cnt = 0;
    while (!q.empty())
    {
        auto [curPos, curPriority] = q.front();
        q.pop();
        bool flag = true;
        for (int i = curPriority + 1; i < 10; i++)
            if (rem[i] > 0)
                flag = false;
        if (!flag)
            q.push({curPos, curPriority});
        else
        {
            cnt++;
            rem[curPriority]--;
            if (location == curPos)
                return cnt;
        }
    }
    return -1;
}