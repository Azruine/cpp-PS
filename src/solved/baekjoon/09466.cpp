#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    int t, n;
    std::vector<int> graph;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> t;
        while (std::cin >> n)
        {
            graph.resize(n);
            for (int i = 0; i < n; i++)
            {
                int u;
                std::cin >> u;
                graph[i] = u - 1;
            }

            int cnt = 0;

            std::vector<bool> visited(n, false);
            std::vector<bool> inStack(n, false);
            for (int i = 0; i < n; i++)
            {
                if (visited[i])
                    continue;
                std::vector<int> st;
                int curNode = i;
                while (true)
                {
                    visited[curNode] = true;
                    inStack[curNode] = true;
                    st.push_back(curNode);
                    int nextNode = graph[curNode];

                    if (!visited[nextNode])
                        curNode = nextNode;
                    else
                    {
                        if (inStack[i])
                        {
                            auto it = std::find(st.begin(), st.end(), nextNode);
                            cnt += st.end() - it;
                        }
                        break;
                    }
                }
                for (auto &i : st)
                    inStack[i] = false;
            }
            std::cout << n - cnt << '\n';
        }
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}