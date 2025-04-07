#include <unordered_map>
#include <vector>

class UnionFind {
public:
    void init(int n) {
        data.resize(n);
        for (int i = 0; i < n; i++) data[i] = i;
    }
    int find(int x) { return (data[x] == x ? x : data[x] = find(data[x])); }
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x != y) (x > y ? data[x] = y : data[y] = x);
    }

private:
    std::vector<int> data;
};

class Solution {
private:
    UnionFind uf;

public:
    std::vector<int> minimumCost(int n, std::vector<std::vector<int>> &edges,
                                 std::vector<std::vector<int>> &query) {
        uf.init(n);
        std::unordered_map<int, int> m;
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            uf.merge(u, v);
        }
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (u > v) std::swap(u, v);
            if (!m.contains(uf.find(u))) {
                m[uf.find(u)] = w;
            } else {
                m[uf.find(u)] &= w;
            }
        }
        std::vector<int> ans;
        for (auto &q : query) {
            int u = q[0], v = q[1];
            if (u > v) std::swap(u, v);
            if (uf.find(u) != uf.find(v))
                ans.emplace_back(-1);
            else
                ans.emplace_back(m[uf.find(u)]);
        }
        return ans;
    }
};