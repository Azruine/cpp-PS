#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                          \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    int n;
    std::vector<std::vector<int>> distance;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n;
        distance.assign(n << 3, std::vector<int>(n << 3, -1));
        distance[1][0] = 0;
        // first is cost, second is screen string length, thrid is clipboard string length
        std::queue<std::array<int, 3>> q;
        q.push({0, 1, 0});
        while (!q.empty())
        {
            auto [curCost, curScreen, curClipboard] = q.front();
            q.pop();
            if (curScreen == n)
            {
                std::cout << curCost;
                return;
            }
            // 1. paste: screen += clipboard
            if (distance[curScreen + curClipboard][curClipboard] == -1)
            {
                distance[curScreen + curClipboard][curClipboard] = curCost + 1;
                q.push({curCost + 1, curScreen + curClipboard, curClipboard});
            }
            // 2. copy: clipboard = screen
            if (curScreen != curClipboard && distance[curScreen][curScreen] == -1)
            {
                distance[curScreen][curScreen] = curCost + 1;
                q.push({curCost + 1, curScreen, curScreen});
            }
            // 3. delete: screen--;
            if (curScreen - 1 >= 0 && distance[curScreen - 1][curClipboard] == -1)
            {
                distance[curScreen - 1][curClipboard] = curCost + 1;
                q.push({curCost + 1, curScreen - 1, curClipboard});
            }
        }
        std::cout << "Something bad happened";
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}