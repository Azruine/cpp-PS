#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    int n, k;
    std::vector<int> data;
    std::vector<int> count;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n >> k;
        data.resize(n);
        count.assign(n, 0);
        for (int i = 0; i < n; i++)
        {
            std::cin >> data[i];
            if (i)
                count[i] = count[i - 1] + (data[i] & 1);
            else
                count[i] = (data[i] & 1);
        }
        int l = 0, r = 0;
        int cnt = 0, len = 0;
        for (r = 0; r < n; r++)
        {
            if (data[r] & 1)
                cnt++;
            
            while (cnt > k)
            {
                if (data[l++] & 1)
                    cnt--;
            }
            len = std::max(len, r - l + 1 - cnt);
        }
        std::cout << len;
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}