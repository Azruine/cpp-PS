#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                    \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

/**
 * @brief check whether the jth point is under the line that connects the ith and kth points
 * @param i the index of the ith point
 * @param h_i the height of the ith point
 * @return true if the jth point is under the line that connects the ith and kth points, otherwise false
 */
bool getLoc(int i, int j, int k, ll h_i, ll h_j, ll h_k)
{
    return (h_j - h_i) * (k - i) < (h_k - h_i) * (j - i);
}

class Solver
{
private:
    int n;
    std::vector<int> height;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n;
        height.resize(n);
        for (auto &i : height)
            std::cin >> i;
        
        std::vector<int> watch(n, 0);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    continue;
                // if abs(i - j) == 1, add 1 to watch[i]
                if (std::abs(i - j) == 1)
                {
                    watch[i]++;
                    continue;
                }
                // if abs(i - j) >= 2, check all heights in (i, j) and add 1 to watch[i] if all points are under the line that connects the ith and jth points
                bool isWatch = true;
                int start = std::min(i, j);
                int end = std::max(i, j);
                for (int k = start + 1; k < end; k++)
                {
                    if (!getLoc(start, k, end, height[start], height[k], height[end]))
                    {
                        isWatch = false;
                        break;
                    }
                }
                if (isWatch)
                    watch[i]++;
            }
        }
        std::cout << *std::max_element(watch.begin(), watch.end());
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}