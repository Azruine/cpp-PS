#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    int n;
    std::vector<std::vector<int>> parents;

public:
    Solver()
    {
        std::cin >> n;
        parents.resize(n + 1);
        for (int i = 1; i <= n; i++)
        {
            int x, y;
            std::cin >> x >> y;
            parents[x].push_back(i);
            if (x != y)
                parents[y].push_back(i);
        }
    }
    ~Solver() {}
    void solve()
    {
#define MIN_DEPTH 10
#define MAX_DEPTH 100
        // first is node index, second is depth, third is whether the node is reachable or not
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(MAX_DEPTH, -1));
        dp[1][0] = 1;
        for (int x = 2; x <= n; x++)
        {
            dp[x][0] = 0;
        }
        std::function<int(int, int)> getDp = [&](int node, int depth) -> int
        {
            if (depth < 0)
                return 0;
            if (depth >= MAX_DEPTH)
                return 0;
            if (dp[node][depth] != -1)
                return dp[node][depth];
            for (auto parent : parents[node])
            {
                if (getDp(parent, depth - 1) == 1)
                {
                    return dp[node][depth] = 1;
                }
            }
            return dp[node][depth] = 0;
        };
        for (int i = MIN_DEPTH; i < MAX_DEPTH; i++)
        {
            if (getDp(1, i) != 1)
            {
                std::cout << i;
                return;
            }
        }
        std::cout << -1;
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}