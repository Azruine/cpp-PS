#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                    \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

using point = std::pair<ld, ld>;

std::istream &operator>>(std::istream &is, point &p)
{
    is >> p.first >> p.second;
    return is;
}

ld getArea(point a, point b, point c)
{
    return (ld)0.5 * (a.first * b.second + 
                      b.first * c.second +
                      c.first * a.second -
                      a.second * b.first -
                      b.second * c.first -
                      c.second * a.first);
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
        for (auto &i : points)
            std::cin >> i;
        ld ans = 0;
        for (int i = 0; i < n - 2; i++)
            ans += getArea(points[0], points[i + 1], points[i + 2]);
        
        std::cout << std::fixed << std::setprecision(1) << std::abs(ans) << '\n';
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}