#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                          \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

using point = std::pair<int, int>;

std::istream &operator>>(std::istream &is, point &p)
{
    is >> p.first >> p.second;
    return is;
}

inline ll getEuclideanDistance(point &a, point &b)
{
    return ((ll)a.first - b.first) * ((ll)a.first - b.first) + ((ll)a.second - b.second) * ((ll)a.second - b.second);
}

class Solver
{
private:
    int n;
    std::vector<point> points;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n;
        points.resize(n);
        for (auto &p : points)
            std::cin >> p;
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                for (int k = j + 1; k < n; k++)
                {
                    ll side_1 = getEuclideanDistance(points[i], points[j]);
                    ll side_2 = getEuclideanDistance(points[j], points[k]);
                    ll side_3 = getEuclideanDistance(points[k], points[i]);
                    if (side_1 + side_2 == side_3 || side_2 + side_3 == side_1 || side_3 + side_1 == side_2)
                    {
                        res++;
                    }
                }
            }
        }
        std::cout << res;
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}