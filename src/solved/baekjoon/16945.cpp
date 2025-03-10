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
    std::vector<std::array<std::array<int, 3>, 3>> magic;
    std::array<std::array<int, 3>, 3> grid;
    void getMagic() {
        std::array<std::array<int, 3>, 3> grid;
        std::array<int, 9> perm;
        for (int i = 0; i < 9; i++) {
            perm[i] = i + 1;
        }
        do {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    grid[i][j] = perm[i * 3 + j];
                }
            }
            if (isMagic(grid)) {
                magic.push_back(grid);
            }
        } while (std::next_permutation(perm.begin(), perm.end()));
    }
    bool isMagic(std::array<std::array<int, 3>, 3> &grid) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += grid[i][0];
        }
        for (int i = 0; i < 3; i++) {
            int rowSum = 0;
            for (int j = 0; j < 3; j++) {
                rowSum += grid[i][j];
            }
            if (rowSum != sum) {
                return false;
            }
        }
        for (int i = 0; i < 3; i++) {
            int colSum = 0;
            for (int j = 0; j < 3; j++) {
                colSum += grid[j][i];
            }
            if (colSum != sum) {
                return false;
            }
        }
        int diagSum = 0;
        for (int i = 0; i < 3; i++) {
            diagSum += grid[i][i];
        }
        if (diagSum != sum) {
            return false;
        }
        diagSum = 0;
        for (int i = 0; i < 3; i++) {
            diagSum += grid[i][2 - i];
        }
        if (diagSum != sum) {
            return false;
        }
        return true;
    }

public:
    Solver() {}
    ~Solver() {}
    void solve() {
        getMagic();
        for (auto &v : grid)
            for (auto &i : v) std::cin >> i;
        int minCost = INT_MAX;
        for (auto &m : magic) {
            int cost = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cost += std::abs(m[i][j] - grid[i][j]);
                }
            }
            minCost = std::min(minCost, cost);
        }
        std::cout << minCost;
    }
};

int main() {
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}