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
    int maxRes, minRes;
    std::vector<int> num;
    std::vector<int> ops;

public:
    Solver()
    {
        std::cin >> n;
        maxRes = INT_MIN, minRes = INT_MAX;
        num.assign(n, 0);
        ops.assign(4, 0);
        for (auto &i : num)
            std::cin >> i;
        for (auto &i : ops)
            std::cin >> i;
    }
    ~Solver() {}
    int cal(int op, int lhs, int rhs)
    {
        switch (op)
        {
        case (0):
            return lhs + rhs;
            break;
        case (1):
            return lhs - rhs;
            break;
        case (2):
            return lhs * rhs;
            break;
        case (3):
            return lhs / rhs;
            break;
        default:
            exit(-1);
        }
    }
    void backtracking(std::vector<int> &ops, int res, int idx = 0)
    {
        if (idx == static_cast<int>(num.size()))
        {
            maxRes = std::max(maxRes, res);
            minRes = std::min(minRes, res);
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            if (ops[i] == 0)
                continue;
            ops[i]--;
            backtracking(ops, cal(i, res, num[idx]), idx + 1);
            ops[i]++;
        }
        return;
    }
    void solve()
    {
        backtracking(ops, num[0], 1);
        std::print("{}\n{}", maxRes, minRes);
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}