#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                    \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    int n, m;
    std::vector<std::unordered_map<int, int>> adj;

public:
    Solver() {}
    ~Solver() {}
    void
    solve()
    {
        std::cin >> n >> m;
        adj.assign(n + 1, std::unordered_map<int, int>());
        while (m--)
        {
            int s, e, w;
            std::cin >> s >> e >> w;
            if (adj[s].contains(e))
                adj[s][e] = std::min(adj[s][e], w);
            else
                adj[s][e] = w;
        }
        int start, end;
        std::cin >> start >> end;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        std::vector<int> cost(n + 1, INT_MAX);
        pq.push({0, start});
        while (!pq.empty())
        {
            auto [curCost, curNode] = pq.top();
            pq.pop();
            if (cost[curNode] < curCost || adj[curNode].empty())
                continue;
            if (curNode == end)
                break;
            std::for_each(adj[curNode].begin(), adj[curNode].end(), [&](auto &nextData)
                          {
                auto [nextNode, nextCost] = nextData;
                if (cost[nextNode] > curCost + nextCost)
                {
                    cost[nextNode] = curCost + nextCost;
                    pq.push({cost[nextNode], nextNode});
                } });
        }
        std::print("{}", cost[end] == INT_MAX ? -1 : cost[end]);
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}