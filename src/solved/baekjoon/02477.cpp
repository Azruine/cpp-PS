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
public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        int k, width = 0, height = 0, smallWidth = 0, smallHeight = 0;
        std::cin >> k;
        std::vector<std::pair<int, int>> v;
        int dir, dist;
        int maxWidthIdx = 0, maxHeightIdx = 0;
        while (std::cin >> dir >> dist)
        {
            v.push_back({dist, dir});
            if (dir == 1 || dir == 2)
            {
                width = std::max(width, dist);
                if (width == dist)
                {
                    maxWidthIdx = v.size() - 1;
                }
            }
            else
            {
                height = std::max(height, dist);
                if (height == dist)
                {
                    maxHeightIdx = v.size() - 1;
                }
            }
        }
        smallWidth = v[(maxWidthIdx + 3) % 6].first;
        smallHeight = v[(maxHeightIdx + 3) % 6].first;
        std::cout << (ll)k * ((ll)width * height - (ll)smallWidth * smallHeight) << '\n';
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}