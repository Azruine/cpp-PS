/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <utility>
#include <vector>

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

class UnionFind {
public:
    void init(size_t n) {
        this->size = n;
        data.resize(n);
        for (size_t i = 0; i < n; i++) {
            data[i] = i;
        }
    }
    size_t find(size_t idx) {
        return (idx == data[idx]) ? idx : (data[idx] = find(data[idx]));
    }
    void merge(size_t a, size_t b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (a > b) {
                std::swap(a, b);
            }
            data[b] = a;
        }
    }
    std::pair<size_t, size_t> getTwoRoots() {
        size_t first{0};
        size_t second{0};
        for (size_t i = 0; i < size; i++) {
            if (data[i] == i) {
                if (first == 0) {
                    first = i;
                } else if (second == 0) {
                    second = i;
                } else {
                    break;
                }
            }
        }
        return {first, second};
    }

private:
    size_t size{0};
    std::vector<size_t> data;
};

class Solver {
public:
    void solve() {
        cin >> n;
        uf.init(n);
        size_t a{0};
        size_t b{0};
        while (cin >> a >> b) {
            uf.merge(a - 1, b - 1);
        }
        for (auto const& [root1, root2] : {uf.getTwoRoots()}) {
            cout << root1 + 1 << ' ' << root2 + 1 << '\n';
        }
    }

private:
    size_t n{0};
    UnionFind uf;
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
