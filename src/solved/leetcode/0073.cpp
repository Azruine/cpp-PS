/*==== Copyright 2025 Azruine ====*/

#include <bitset>
#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
public:
    void setZeroes(std::vector<std::vector<int32_t>>& matrix) {
        std::bitset<200> rows{0x0};
        std::bitset<200> cols{0x0};
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                if (matrix[i][j] == 0) {
                    rows.set(i);
                    cols.set(j);
                }
            }
        }
        for (size_t i = 0; i < matrix.size(); ++i) {
            if (rows.test(i)) {
                set_row(matrix, i);
            }
        }
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            if (cols.test(j)) {
                set_col(matrix, j);
            }
        }
    }

private:
    void set_row(std::vector<std::vector<int32_t>>& matrix, size_t row) {
        for (auto& col : matrix[row]) {
            col = 0;
        }
    }
    void set_col(std::vector<std::vector<int32_t>>& matrix, size_t col) {
        for (auto& row : matrix) {
            row[col] = 0;
        }
    }
};
