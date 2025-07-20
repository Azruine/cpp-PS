/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <utility>

using std::cin, std::cout;

namespace {
inline void fastio() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solver {
public:
    void solve() {
        cin >> t;
        while (t--) {
            read();
            bfs();
            print();
        }
    }

private:
    size_t t = 0, start = 0, end = 0;
    constexpr static int32_t MAX = 10'000;
    constexpr static std::array<char, 4> operations = {'D', 'S', 'L', 'R'};

    std::array<bool, MAX> visited = {};
    std::array<size_t, MAX> parent = {};
    std::array<char, MAX> operation = {};

    void read() { cin >> start >> end; }

    bool bfs() {
        visited.fill(false);
        parent.fill(std::numeric_limits<size_t>::max());
        operation.fill('\0');
        std::queue<size_t> que;
        que.push(start);
        visited[start] = true;
        while (!que.empty()) {
            auto cur = que.front();
            que.pop();
            if (cur == end) {
                return true;
            }
            for (auto cmd : operations) {
                size_t next = 0;
                switch (cmd) {
                    case 'D':
                        next = (cur * 2) % MAX;
                        break;
                    case 'S':
                        next = (cur + MAX - 1) % MAX;
                        break;
                    case 'L':
                        next = (cur % 1000) * 10 + cur / 1000;
                        break;
                    case 'R':
                        next = (cur % 10) * 1000 + cur / 10;
                        break;
                }
                if (!visited[next]) {
                    visited[next] = true;
                    parent[next] = cur;
                    operation[next] = cmd;
                    que.push(next);
                }
            }
        }
        return false;
    }

    void print() {
        std::string path;
        size_t cur = end;
        while (cur != start) {
            path += operation[cur];
            cur = parent[cur];
        }
        std::ranges::reverse(path);
        cout << path << '\n';
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
