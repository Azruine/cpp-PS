#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include <queue>

using namespace std;

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    std::vector<std::vector<int>> children(n, std::vector<int>(0));
    for (auto &p : edge)
    {
        int s = p[0] - 1, e = p[1] - 1;
        children[s].emplace_back(e);
        children[e].emplace_back(s);
    }
    std::queue<std::pair<int, int>> q;
    q.push({0, 0});
    std::vector<bool> visited(n, false);
    std::vector<int> distance(n, INT_MAX);
    visited[0] = true;
    while (!q.empty())
    {
        auto [curNode, curDist] = q.front();
        q.pop();
        for (auto &child : children[curNode])
        {
            if (visited[child] == true)
                continue;
            q.push({child, curDist + 1});
            distance[child] = curDist + 1;
            visited[child] = true;
        }
    }
    int max = INT_MIN, cnt = 0;
    for (int i = 1; i < n; i++)
    {
        if (distance[i] == INT_MAX)
            continue;
        if (distance[i] == max)
            cnt++;
        else if (distance[i] > max)
        {
            cnt = 1;
            max = distance[i];
        }
    }
    return cnt;
}