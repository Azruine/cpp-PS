#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver {
private:
    int n;
    std::vector<int> target;

public:
    Solver() {}
    ~Solver() {}
    void solve() {
        std::cin >> n;
        target.resize(n);
        for (auto &i : target) std::cin >> i, i--;
        int idx = -1, max = -1;
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            int cur = i;
            std::vector<bool> visited(n, false);
            while (!visited[cur]) {
                visited[cur] = true;
                cur = target[cur];
                cnt++;
            }
            if (cnt > max) {
                max = cnt;
                idx = i;
            }
        }
        std::cout << idx + 1;
    }
};

int main() {
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}