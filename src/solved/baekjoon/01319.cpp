#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

#define INT_MAX std::numeric_limits<int32_t>::max()

std::istream &operator>>(std::istream &is, std::vector<int> &v)
{
    for (auto &i : v)
        is >> i;
    return is;
}

class Solver
{
private:
    int n;
    std::vector<std::vector<int>> v;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n;
        v.resize(n, std::vector<int>(3));
        for (auto &p : v)
            std::cin >> p;
        std::sort(v.begin(), v.end());
        int total = std::accumulate(v.begin(), v.end(), 0, [](int a, const std::vector<int> &x)
                                    { return a + x[2]; });
        int minValue = INT_MAX;
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int leftSum = 0, rightSum = 0;
                int dx = v[i][0] - v[j][0];
                int dy = v[i][1] - v[j][1];
                std::vector<std::vector<int>> collinear;
                for (int k = 0; k < n; k++)
                {
                    int left = dx * (v[k][1] - v[i][1]);
                    int right = dy * (v[k][0] - v[i][0]);
                    if (left > right)
                        leftSum += v[k][2];
                    else if (left < right)
                        rightSum += v[k][2];
                    else
                        collinear.push_back({dx * (v[k][0] - v[i][0]) + dy * (v[k][1] - v[i][1]), v[k][2]});
                }
                std::sort(collinear.begin(), collinear.end());
                int acc = 0;
                std::for_each(collinear.begin(), collinear.end(), [&](std::vector<int> &v) {
                    acc += v[1];
                    minValue = std::min(minValue, std::abs(total - 2 * (leftSum + acc)));
                });
                if (minValue == INT_MAX)
                    minValue = std::min(minValue, std::abs(leftSum - rightSum));
            }
        }
        std::cout << minValue;
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}