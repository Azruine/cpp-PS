/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <print>
#include <queue>
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

class Solver {
public:
    void solve() {
        cin >> t;
        while (t--) {
            read();
            print();
        }
    }

private:
    int32_t t{0}, size{0}, temp{0};
    std::priority_queue<int32_t> max_heap;
    std::priority_queue<int32_t, std::vector<int32_t>, std::greater<int32_t>>
        min_heap;
    std::vector<int32_t> res;
    void read() {
        cin >> size;
        max_heap = std::priority_queue<int32_t>();
        min_heap = std::priority_queue<int32_t, std::vector<int32_t>,
                                       std::greater<int32_t>>();
        res.clear();
        res.reserve(as<size_t>((size + 1) / 2));
        while (size--) {
            cin >> temp;
            if (max_heap.empty() || temp <= max_heap.top()) {
                max_heap.push(temp);
            } else {
                min_heap.push(temp);
            }
            balance();
            if ((size & 1) == 0) {
                res.push_back(max_heap.top());
            }
        }
    }
    void balance() {
        if (max_heap.size() > min_heap.size() + 1) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        } else if (min_heap.size() > max_heap.size()) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }
    void print() {
        std::print("{}\n", res.size());
        size_t cnt{0};
        for (auto const& i : res) {
            std::print("{}{}", i, (++cnt == 10) ? "\n" : " ");
            cnt %= 10;
        }
        std::println();
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
