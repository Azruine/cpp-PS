#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

inline int min(int a, int b, int c)
{
    return std::min(a, std::min(b, c));
}

class Solver
{
#define MAX INT_MAX

private:
    int n;
    std::vector<std::pair<int, int>> arr;
    int getMinDistance()
    {
        for (int i = 2; i < n + 1; i++)
        {
            int minDistance = MAX;
            int candidate[3] = {MAX, MAX, MAX};
            if (i % 3 == 0)
            {
                candidate[0] = arr[i / 3].first + 1;
            }
            if (i % 2 == 0)
            {
                candidate[1] = arr[i / 2].first + 1;
            }
            candidate[2] = arr[i - 1].first + 1;
            arr[i].first = min(candidate[0], candidate[1], candidate[2]);
            if (arr[i].first == candidate[0])
            {
                arr[i].second = i / 3;
            }
            else if (arr[i].first == candidate[1])
            {
                arr[i].second = i / 2;
            }
            else
            {
                arr[i].second = i - 1;
            }
        }
        return arr[n].first;
    }
    std::vector<int> getPath(bool reverse = true)
    {
        std::vector<int> path;
        int idx = n;
        while (idx != 0)
        {
            path.push_back(idx);
            idx = arr[idx].second;
        }
        if (reverse)
        {
            std::reverse(path.begin(), path.end());
        }
        return path;
    }

public:
    Solver()
    {
        std::cin >> n;
        arr.assign(n + 1, {0, 0});
        arr[1] = {0, 0};
    }
    ~Solver() {}
    void solve()
    {
        std::cout << getMinDistance() << '\n';
        std::vector<int> path = getPath(false);
        std::for_each(path.begin(), path.end(), [](int x)
                      { std::cout << x << " "; });
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}