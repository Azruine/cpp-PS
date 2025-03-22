#include <algorithm>
#include <vector>

class UnionFind {
public:
    std::vector<std::pair<int, int>> uniqueRoot;
    void init(int n) {
        data.reserve(n);
        for (int i = 0; i < n; i++) data.emplace_back(i);
    }
    int find(int x) { return (x == data[x] ? x : data[x] = find(data[x])); }
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x != y) x > y ? data[x] = y : data[y] = x;
    }
    void count() {
        for (int i = 0; i < data.size(); i++) find(i);
        std::vector<int> root = data;
        std::sort(root.begin(), root.end());
        int r = root.front(), cnt = 1;
        for (int i = 1; i < root.size(); i++) {
            if (root[i] == r)
                cnt++;
            else {
                uniqueRoot.emplace_back(std::make_pair(r, cnt));
                r = root[i], cnt = 1;
            };
        }
        uniqueRoot.emplace_back(std::make_pair(r, cnt));
    }
    int getVertexCnt(int root) {
        for (auto& v : uniqueRoot) {
            if (v.first == root) return v.second;
        }
        return -1;
    }

private:
    std::vector<int> data;
};

class Solution {
public:
    int countCompleteComponents(int n, std::vector<std::vector<int>>& edges) {
        uf.init(n);
        for (auto& e : edges) uf.merge(e[0], e[1]);
        uf.count();
        int cnt = 0;
        for (auto& v : uf.uniqueRoot) {
            if (isComplete(v, edges)) cnt++;
        }
        return cnt;
    }

    bool isComplete(std::pair<int, int>& root,
                    std::vector<std::vector<int>>& edges) {
        int cnt = 0, v = root.second;
        for (auto& e : edges)
            if (uf.find(e[0]) == root.first || uf.find(e[1]) == root.first)
                cnt++;
        return (v == 1 || v * (v - 1) == cnt * 2);
    }

private:
    UnionFind uf;
};
int main() {
    int n = 4;
    std::vector<std::vector<int>> edges = {{2, 0}, {3, 1}, {3, 2}};
    Solution sol;
    sol.countCompleteComponents(n, edges);
    return 0;
}