/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
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

class MergeSortTree {
private:
    size_t size{0};
    std::vector<std::vector<int32_t>> tree;

public:
    void init(size_t n) {
        size = n;
        tree.assign(2 * n, {});
    }
    void build(std::vector<int32_t> const& nums,
               std::vector<int32_t> const& compressed) {
        for (size_t i = 0; i < size; ++i) {
            tree[size + i].push_back(
                as<int32_t>(std::lower_bound(compressed.begin(),
                                             compressed.end(), nums[i]) -
                            compressed.begin()));
        }
        for (size_t i = size - 1; i > 0; --i) {
            auto& left = tree[i << 1];
            auto& right = tree[i << 1 | 1];
            tree[i].resize(left.size() + right.size());
            std::ranges::merge(left, right, tree[i].begin(), std::less<>());
        }
    }
    int32_t query(size_t left, size_t right, size_t k) {
        left += size;
        right += size;
        int32_t low{0};
        int32_t high{2'000'000};
        while (low < high) {
            int32_t mid = (low + high + 1) / 2;
            size_t count = 0;
            for (size_t i = left; i < right; ++i) {
                count += as<size_t>(
                    std::upper_bound(tree[i].begin(), tree[i].end(), mid) -
                    tree[i].begin());
            }
            if (count >= k) {
                high = mid - 1;
            } else {
                low = mid;
            }
        }
        return low + 1;
    }
};

class Solver {
public:
    void solve() {
        readInput();
        tree.init(n);
        tree.build(nums, compressed);
        processQueries();
    }

private:
    size_t n{0};
    size_t q{0};
    std::vector<int32_t> nums;
    std::vector<int32_t> compressed;
    MergeSortTree tree;
    void readInput() {
        cin >> n >> q;
        nums.resize(n);
        compressed.resize(n);
        for (size_t i = 0; i < n; ++i) {
            cin >> nums[i];
            compressed[i] = nums[i];
        }
        std::ranges::sort(compressed);
        compressed.erase(std::unique(compressed.begin(), compressed.end()),
                         compressed.end());
    }
    void processQueries() {
        static size_t left{0};
        static size_t right{0};
        static size_t k{0};
        for (size_t i = 0; i < q; ++i) {
            cin >> left >> right >> k;
            cout << tree.query(left - 1, right, k) << '\n';
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}

/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
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

class Solver {
    template <typename T>
    using pair = std::pair<T, T>;

public:
    void solve() {
        readInput();
        std::ranges::sort(nums);
        while (q--) {
            query();
        }
    }

private:
    size_t n{0};
    size_t q{0};
    std::vector<pair<int32_t>> nums;
    void readInput() {
        cin >> n >> q;
        nums.resize(n);
        for (size_t i = 0; i < n; ++i) {
            int32_t num{0};
            cin >> num;
            nums[i] = {num, i};
        }
    }
    void query() {
        static int32_t left{0};
        static int32_t right{0};
        static size_t k{0};
        cin >> left >> right >> k;
        size_t cnt{0};
        for (size_t i{0}; i < n; i++) {
            if (nums[i].second >= left - 1 && nums[i].second <= right - 1) {
                cnt++;
            }
            if (cnt == k) {
                cout << nums[i].first << '\n';
                return;
            }
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
