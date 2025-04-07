#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class SegTreeMax {
private:
    int height;
    int size;
    std::vector<int> tree;
    std::vector<int> delay;

public:
    SegTreeMax() {}
    ~SegTreeMax() {}
    void init(int n) {
        height = sizeof(int) * 8 - __builtin_clz(n);
        size = n;
        tree.resize(2 * n, 0);
        delay.resize(n, 0);
    }
    void buildAll() {
        for (int i = size - 1; i > 0; i--) {
            tree[i] = std::max(tree[i << 1], tree[i << 1 | 1]);
        }
    }
    void setLeaf(std::vector<int>& nums) {
        for (int i = 0; i < size; i++) {
            tree[size + i] = nums[i];
        }
    }
    void apply(int pos, int value) {
        tree[pos] += value;
        if (pos < size) delay[pos] += value;
    }
    void build(int pos) {
        while (pos > 1) {
            pos >>= 1;
            tree[pos] =
                std::max(tree[pos << 1], tree[pos << 1 | 1]) + delay[pos];
        }
    }
    void push(int pos) {
        for (int s = height; s > 0; s--) {
            int i = pos >> s;
            if (delay[i] != 0) {
                apply(i << 1, delay[i]);
                apply(i << 1 | 1, delay[i]);
                delay[i] = 0;
            }
        }
    }
    void increase(int l, int r, int value) {
        l += size, r += size;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, value);
            if (r & 1) apply(--r, value);
        }
        build(l0);
        build(r0 - 1);
    }
    int query(int l, int r) {
        l += size, r += size;
        push(l);
        push(r - 1);
        int res = INT_MIN;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = std::max(res, tree[l++]);
            if (r & 1) res = std::max(res, tree[--r]);
        }
        return res;
    }
};

class Solution {
public:
    int minZeroArray(std::vector<int>& nums,
                     std::vector<std::vector<int>>& queries) {
        int n = nums.size();
        SegTreeMax st;
        st.init(n);
        st.setLeaf(nums);
        st.buildAll();

        int cnt = 0;
        for (auto& q : queries) {
            if (st.query(0, n) <= 0) return cnt;
            int l = q[0], r = q[1] + 1, k = -q[2];
            st.increase(l, r, k);
            cnt++;
        }
        return (st.query(0, n) <= 0) ? cnt : -1;
    }
};

int main() {
    Solution sol;
    std::vector<int> nums = {2, 10, 8, 4, 1};
    std::vector<std::vector<int>> queries = {
        {0, 1, 2}, {3, 3, 1}, {1, 3, 1}, {0, 3, 5}, {2, 4, 3},
        {0, 0, 5}, {0, 4, 3}, {0, 1, 2}, {2, 3, 4}, {1, 4, 1},
        {0, 2, 1}, {1, 2, 2}, {1, 1, 3}, {1, 3, 5}, {0, 3, 5}};
    std::cout << sol.minZeroArray(nums, queries) << std::endl;
    return 0;
}