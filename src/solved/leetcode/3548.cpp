#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
public:
    bool canPartitionGrid(std::vector<std::vector<int>>& grid) {
        std::vector<int64_t> hori, ver;
        auto n = grid.size(), m = grid[0].size();
        hori.resize(n, 0), ver.resize(m, 0);
        std::vector<std::unordered_map<int64_t, int32_t>> hori_hash(n),
            ver_hash(m);
        std::unordered_map<int64_t, int32_t> hori_hash_acc, ver_hash_acc;
        std::unordered_map<int64_t, int32_t> hori_hash_sum, ver_hash_sum;
        int64_t hori_sum = 0L, ver_sum = 0L, hori_acc = 0L, ver_acc = 0L;
        for (auto j = 0UL; j < m; j++) {
            for (auto i = 0UL; i < n; i++) {
                ver[j] += grid[i][j];
                hori[i] += grid[i][j];

                hori_sum += grid[i][j];
                ver_sum += grid[i][j];

                hori_hash[i][grid[i][j]] += 1;
                ver_hash[j][grid[i][j]] += 1;

                hori_hash_sum[grid[i][j]] += 1;
                ver_hash_sum[grid[i][j]] += 1;
            }
        }
        // 위쪽이 acc, 아래쪽이 sum
        for (auto i = 0UL; i < n; i++) {
            if (hori_sum == hori_acc) {
                return true;
            }
            auto val = hori_acc - hori_sum;

            if (m != 1) {  // 위쪽 특수 검색 + 아래쪽 일반 검색
                if (i == 1UL) {
                    if (val == grid[0][0] || val == grid[0][m - 1]) {
                        return true;
                    }
                    if (i != n - 1 && hori_hash_sum[-val] != 0) {
                        return true;
                    }
                }
                // 위쪽 일반 검색 + 아래쪽 특수 검색
                if (i == n - 1) {
                    if (val == -grid[n - 1][0] || val == -grid[n - 1][m - 1]) {
                        return true;
                    }
                    if (i != 1 && hori_hash_acc[val] != 0) {
                        return true;
                    }
                }
                // 위아래 전부 일반 검색
                if (i != 1UL && i != n - 1) {
                    if (hori_hash_acc[val] != 0) {
                        return true;
                    }
                    if (hori_hash_sum[-val] != 0) {
                        return true;
                    }
                }
            } else {
                // 무조건 위아래 전부 특수 검색
                if (grid[0][0] == val) {
                    return true;
                }
                if (i - 1 < n && grid[i - 1][0] == val) {
                    return true;
                }
                if (grid[n - 1][0] == -val) {
                    return true;
                }
                if (i < n && grid[i][0] == -val) {
                    return true;
                }
            }
            // 위쪽에서 빼고, 아래쪽에서 더하고
            hori_sum -= hori[i], hori_acc += hori[i];
            for (auto j = 0UL; j < m; j++) {
                hori_hash_sum[grid[i][j]] -= 1;
                hori_hash_acc[grid[i][j]] += 1;
            }
        }
        // 위쪽이 acc, 아래쪽이 sum
        for (auto j = 0UL; j < m; j++) {
            if (ver_sum == ver_acc) {
                return true;
            }
            auto val = ver_acc - ver_sum;
            if (n != 1) {
                // 위쪽 특수 검색 + 아래쪽 일반 검색
                if (j == 1UL) {
                    if (val == grid[0][0] || val == grid[n - 1][0]) {
                        return true;
                    }
                    if (j != m - 1 && ver_hash_sum[-val] != 0) {
                        return true;
                    }
                }
                // 위쪽 일반 검색 + 아래쪽 특수 검색
                if (j == m - 1) {
                    if (val == -grid[0][m - 1] || val == -grid[n - 1][m - 1]) {
                        return true;
                    }
                    if (j != 1 && ver_hash_acc[val] != 0) {
                        return true;
                    }
                }
                // 위아래 전부 일반 검색
                if (j != 1UL && j != m - 1) {
                    if (ver_hash_acc[val] != 0) {
                        return true;
                    }
                    if (ver_hash_sum[-val] != 0) {
                        return true;
                    }
                }
            } else {
                // 무조건 위아래 전부 특수 검색
                if (grid[0][0] == val) {
                    return true;
                }
                if (j - 1 < m && grid[0][j - 1] == val) {
                    return true;
                }
                if (grid[0][m - 1] == -val) {
                    return true;
                }
                if (j < m && grid[0][j] == -val) {
                    return true;
                }
            }
            // 위쪽에서 빼고, 아래쪽에서 더하고
            ver_sum -= ver[j], ver_acc += ver[j];
            for (auto i = 0UL; i < n; i++) {
                ver_hash_sum[grid[i][j]] -= 1;
                ver_hash_acc[grid[i][j]] += 1;
            }
        }
        return false;
    }
};
