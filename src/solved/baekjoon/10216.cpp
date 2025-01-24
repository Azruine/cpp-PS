#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                    \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

struct Circle
{
    int x, y, r;
    Circle() : x(0), y(0), r(0) {}
    Circle(int x, int y, int r) : x(x), y(y), r(r) {}

    bool isConnect(const Circle &c)
    {
        int dx = x - c.x;
        int dy = y - c.y;
        int d = r + c.r;
        return dx * dx + dy * dy <= d * d;
    }
};
std::istream &operator>>(std::istream &is, Circle &c)
{
    is >> c.x >> c.y >> c.r;
    return is;
}

class Solver
{
private:
    int t, n;
    std::vector<Circle> circles;
    std::vector<std::vector<int>> adj;
    std::vector<bool> visited;

public:
    Solver() { std::cin >> t; }
    ~Solver() {}
    void solve()
    {
        while (t--)
        {
            circles.clear();
            adj.clear();
            visited.clear();

            std::cin >> n;
            circles.resize(n);
            adj.resize(n);
            visited.assign(n, false);

            for (auto &c : circles)
                std::cin >> c;

            for (int i = 0; i < n; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    if (circles[i].isConnect(circles[j]))
                    {
                        adj[i].push_back(j);
                        adj[j].push_back(i);
                    }
                }
            }

            std::cout << bfs() << '\n';
        }
    }

    int bfs()
    {
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            if (visited[i])
                continue;

            res++;
            std::queue<int> q;
            q.push(i);
            visited[i] = true;
            while (!q.empty())
            {
                int cur = q.front();
                q.pop();
                for (auto &next : adj[cur])
                {
                    if (!visited[next])
                    {
                        visited[next] = true;
                        q.push(next);
                    }
                }
            }
        }
        return res;
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}