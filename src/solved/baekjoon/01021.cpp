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
    int n, m;
    std::deque<int> dq;
    std::vector<int> index;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n >> m;
        std::ranges::copy(std::ranges::views::iota(1, n + 1), std::back_inserter(dq));
        index.resize(m);
        for (auto &i : index)
            std::cin >> i;
        int ans = 0;
        for (auto &i : index)
        {
            int cnt = 0;
            while (dq.front() != i)
            {
                dq.push_back(dq.front());
                dq.pop_front();
                cnt++;
            }
            ans += std::min(cnt, (int)dq.size() - cnt);
            dq.pop_front();
        }
        std::cout << ans << '\n';
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}