#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                          \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    int n;
    std::vector<std::vector<int>> map;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n;
        map.assign(n, std::vector<int>(n, 0));
        std::pair<int, int> professor, student;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cin >> map[i][j];
                if (map[i][j] == 5)
                    professor = {i, j};
                if (map[i][j] == 2)
                    student = {i, j};
            }
        }
        int cnt = 0;
        int startR = std::min(professor.first, student.first);
        int endR = std::max(professor.first, student.first);
        int startC = std::min(professor.second, student.second);
        int endC = std::max(professor.second, student.second);
        for (int i = startR; i <= endR; i++)
        {
            for (int j = startC; j <= endC; j++)
            {
                if (map[i][j] == 1)
                {
                    cnt++;
                }
            }
        }
        int distance = (professor.first - student.first) * (professor.first - student.first) + (professor.second - student.second) * (professor.second - student.second);
        std::cout << (cnt >= 3 && distance >= 25);
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}