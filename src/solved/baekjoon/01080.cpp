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
    int row, col;
    std::vector<std::vector<bool>> cur;
    std::vector<std::vector<bool>> target;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> row >> col;
        cur.resize(row, std::vector<bool>(col));
        target.resize(row, std::vector<bool>(col));
        char x;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                std::cin >> x;
                cur[i][j] = x - '0';
            }
        }
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                std::cin >> x;
                target[i][j] = x - '0';
            }
        }
        int cnt = 0;
        for (int i = 0; i < row - 2; i++)
        {
            for (int j = 0; j < col - 2; j++)
            {
                if (cur[i][j] != target[i][j])
                {
                    cnt++;
                    for (int k = 0; k < 3; k++)
                    {
                        for (int l = 0; l < 3; l++)
                        {
                            cur[i + k][j + l] = 1 - cur[i + k][j + l];
                        }
                    }
                }
            }
        }
        if (cur == target)
        {
            std::cout << cnt << '\n';
        }
        else
        {
            std::cout << -1 << '\n';
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