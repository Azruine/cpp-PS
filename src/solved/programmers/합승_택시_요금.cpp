#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    s--, a--, b--;
    int answer = INT_MAX;
    std::vector<std::vector<int>> cost(n, std::vector<int>(n, INT_MAX));
    for (auto &v : fares)
    {
        int s = v[0], e = v[1], d = v[2];
        cost[s - 1][e - 1] = d;
        cost[e - 1][s - 1] = d;
    }
    std::vector<int> distFromS(n, INT_MAX);
    std::vector<int> distFromA(n, INT_MAX);
    std::vector<int> distFromB(n, INT_MAX);
    auto fillDist = [&](std::vector<int> &dist, int start) -> void
    {
        dist[start] = 0;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.push({0, start});
        while (!pq.empty())
        {
            auto [curDist, curNode] = pq.top();
            pq.pop();
            if (dist[curNode] < curDist)
                continue;
            for (int next = 0; next < n; next++)
            {
                if (cost[curNode][next] == INT_MAX)
                    continue;
                int newDist = curDist + cost[curNode][next];
                if (newDist < dist[next])
                {
                    dist[next] = newDist;
                    pq.push({newDist, next});
                }
            }
        }
    };
    fillDist(distFromS, s);
    fillDist(distFromA, a);
    fillDist(distFromB, b);
    std::vector<int> resDist(n, 0);
    for (int i = 0; i < n; i++)
    {
        resDist[i] = distFromS[i] + distFromA[i] + distFromB[i];
    }
    answer = *std::min_element(resDist.begin(), resDist.end());
    return answer;
}