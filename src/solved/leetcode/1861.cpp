/*==== Copyright 2025 Azruine ====*/

#include <ranges>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
struct Range {
    template <typename Sentinel>
    constexpr auto operator()(Sentinel sentinel) const noexcept {
        return std::views::iota(static_cast<Sentinel>(0), sentinel);
    }
    template <typename Start, typename Sentinel>
    constexpr auto operator()(Start start, Sentinel sentinel) const noexcept {
        return std::views::iota(start, sentinel);
    }
    template <typename Start, typename Sentinel, typename Step>
    constexpr auto operator()(Start start, Sentinel sentinel,
                              Step step) const noexcept {
        return std::views::iota(start, sentinel) | std::views::stride(step);
    }
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
constexpr Range _iota{};
#pragma GCC diagnostic pop
}  // namespace

#include <vector>

class Solution {
public:
    std::vector<std::vector<char>> rotateTheBox(
        std::vector<std::vector<char>>& boxGrid) {
        std::vector<std::vector<char>> ret;
        size_t row = boxGrid.size();
        size_t col = boxGrid[0].size();
        for (size_t i : _iota(row)) {
            int32_t cnt = 0;
            for (size_t j : _iota(col)) {
                if (boxGrid[i][j] == '#') {
                    cnt += 1;
                    boxGrid[i][j] = '.';
                }
                if (boxGrid[i][j] == '*') {
                    // [j - cnt, j)
                    for (size_t fill = j - cnt; fill < j; fill++) {
                        boxGrid[i][fill] = '#';
                    }
                    cnt = 0;
                }
                if (j == col - 1) {
                    // [j - cnt + 1, j]
                    for (size_t fill = j - cnt + 1; fill <= j; fill++) {
                        boxGrid[i][fill] = '#';
                    }
                    cnt = 0;
                }
            }
        }
        ret.resize(col, std::vector<char>(row));
        for (size_t i : _iota(row)) {
            for (size_t j : _iota(col)) {
                ret[j][row - 1 - i] = boxGrid[i][j];
            }
        }
        return ret;
    }
};

int main() {
    Solution sol;
    std::vector<std::vector<char>> grid = {{'#', '.', '#'}};
    sol.rotateTheBox(grid);
    return grid[0][0] & 1;
}
