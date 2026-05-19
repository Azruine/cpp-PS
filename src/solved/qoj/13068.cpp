/*==== Copyright 2025 Azruine ====*/

#include <iostream>
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

#include <algorithm>
#include <set>
#include <vector>

// inclusive
using interval = std::pair<int32_t, int32_t>;

struct Vertex {
    std::vector<int32_t> arcs;
    int32_t count = 0;
    int32_t link = -1;
};

class Solver {
    int32_t n = 0;
    std::vector<interval> input;
    std::vector<int32_t> end_points;
    std::vector<Vertex> vertices;

    bool read() {
        input.clear();
        end_points.clear();
        vertices.clear();
        if (!(cin >> n)) {
            return false;
        }
        input.resize(n);
        for (auto& [start, end] : input) {
            cin >> start >> end;
        }
        return true;
    }

    void compress() {
        std::set<int32_t> end_set;
        for (auto& [start, end] : input) {
            end_set.insert(start);
            end_set.insert(end + 1);
        }
        end_points.assign(end_set.begin(), end_set.end());
        n = end_points.size() - 1;
        auto idx = [&](int32_t x) {
            return std::ranges::lower_bound(end_points, x) - end_points.begin();
        };

        vertices.assign(n + 1, {});

        std::set<interval> visited;
        for (auto& [start, end] : input) {
            auto left = idx(start);
            auto right = idx(end + 1);
            if (visited.insert({left, right}).second) {
                vertices[right].arcs.emplace_back(left);
            }
        }
    }

    void reduce(int32_t u, int32_t v) {
        int32_t min_tip = v;
        int32_t min_idx = -1;

        for (auto i = 0; i < as<int32_t>(vertices[v].arcs.size()); i++) {
            auto& arc = vertices[v].arcs[i];
            if (arc >= u && arc < min_tip) {
                min_tip = arc;
                min_idx = i;
            }
        }
        if (min_idx == -1) {
            return;
        }

        auto size = vertices[v].arcs.size();
        vertices[v].arcs[min_idx] = vertices[v].arcs[size - 1];
        vertices[v].arcs.pop_back();
        int32_t w = min_tip;

        for (int32_t i = v - 1; w > u && i >= 0; i--) {
            int32_t new_min = w;
            int32_t target = -1;
            for (int32_t j = 0; j < as<int32_t>(vertices[i].arcs.size()); j++) {
                auto& arc = vertices[i].arcs[j];
                if (arc >= u && arc < new_min) {
                    new_min = arc;
                    target = j;
                }
            }
            if (new_min < w) {
                vertices[i].arcs[target] = w;
                w = new_min;
            }
        }
    }

    void process_vertex(int32_t v) {
        while (true) {
            auto [u, found] = find_min_bad(v);
            if (!found) {
                break;
            }
            reduce(u, v);
        }
    }

    void cleanup_counts(int32_t head) {
        while (head != -1) {
            int32_t next = vertices[head].link;
            vertices[head].count = 0;
            vertices[head].link = -1;
            head = next;
        }
    }

    std::pair<int32_t, bool> find_min_bad(int32_t v) {
        int32_t cover = 0, potential = 0, clean = -1;
        int32_t t = v - 1, u = v;
        bool good = false;

        for (u = v; u > t; u--) {
            cover -= vertices[u].count;
            for (auto& w : vertices[u].arcs) {
                if (vertices[w].count == 0) {
                    vertices[w].link = clean;
                    clean = w;
                }
                vertices[w].count += 1;
                if (w >= t) {
                    cover += 1;
                } else {
                    potential += 1;
                }
            }
            if (cover + potential < 2) {
                good = true;
                break;
            }
            while (cover < 2) {
                t -= 1;
                cover += vertices[t].count;
                potential -= vertices[t].count;
            }
        }
        cleanup_counts(clean);
        return {u, !good};
    }

    std::vector<interval> construct() {
        std::vector<interval> ret;
        for (int32_t v = 1; v <= n; v++) {
            for (auto& w : vertices[v].arcs) {
                ret.emplace_back(end_points[w], end_points[v] - 1);
            }
        }
        return ret;
    }

    void print() {
        auto res = construct();
        cout << res.size() << '\n';
        for (auto const& [start, end] : res) {
            cout << start << ' ' << end << '\n';
        }
    }

public:
    void solve() {
        while (read()) {
            compress();
            for (int32_t v = 1; v <= n; v++) {
                process_vertex(v);
            }
            print();
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
