#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::cin, std::cout;

namespace {
inline void fastio() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}
template <typename To, typename From>
To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

struct Node {
    std::string str;
    int32_t depth{0};
    size_t zero_idx{0};
};

class Solver {
public:
    void solve() {
        std::string str;
        char chr{0};
        size_t zero_idx{0};
        for (size_t i{0}; i < NINE; i++) {
            cin >> chr;
            str += chr;
            if (chr == '0') {
                zero_idx = i;
            }
        }
        table[str] = 0;
        std::queue<Node> queue;
        queue.push({str, 0, zero_idx});
        int32_t depth = -1;
        while (!queue.empty()) {
            auto [cur_str, cur_depth, cur_zero] = queue.front();
            queue.pop();
            if (cur_str == goal) {
                depth = cur_depth;
                break;
            }
            for (auto const& next_idx : next[cur_zero]) {
                std::string next_str = cur_str;
                std::swap(next_str[cur_zero], next_str[next_idx]);
                if (table.find(next_str) != table.end()) {
                    continue;
                }
                queue.push({next_str, cur_depth + 1, next_idx});
                table[next_str] = cur_depth + 1;
            }
        }
        cout << depth;
    }

private:
    constexpr static size_t NINE{9};
    std::string goal = "123456780";
    std::unordered_map<std::string, int32_t> table;
    std::vector<std::vector<size_t>> next = {{1, 3},    {0, 2, 4},    {1, 5},
                                             {0, 4, 6}, {1, 3, 5, 7}, {2, 4, 8},
                                             {3, 7},    {4, 6, 8},    {5, 7}};
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
