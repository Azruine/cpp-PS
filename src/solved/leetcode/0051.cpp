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

#include <string>
#include <vector>

class Solution {
    void backtracking(std::vector<std::vector<std::string>>& ret,
                      std::vector<std::optional<size_t>>& rows,
                      std::vector<bool>& cols, std::vector<bool>& dia1,
                      std::vector<bool>& dia2, size_t depth, size_t n) {
        if (n == depth) {
            std::vector<std::string> board(n, std::string(n, '.'));
            for (size_t row = 0; row < n; row++) {
                board[row][rows[row].value()] = 'Q';
            }
            ret.push_back(std::move(board));
            return;
        }
        for (size_t col = 0; col < n; col++) {
            size_t d1 = depth + col;
            size_t d2 = depth + n - col - 1;
            if (cols[col] || dia1[d1] || dia2[d2]) {
                continue;
            }
            rows[depth] = col;
            cols[col] = dia1[d1] = dia2[d2] = true;
            backtracking(ret, rows, cols, dia1, dia2, depth + 1, n);
            rows[depth] = std::nullopt;
            cols[col] = dia1[d1] = dia2[d2] = false;
        }
    }

public:
    std::vector<std::vector<std::string>> solveNQueens(int32_t n) {
        std::vector<std::optional<size_t>> rows(n, std::nullopt);
        std::vector<bool> cols(n, false);
        std::vector<bool> dia1((n << 1) - 1, false);
        std::vector<bool> dia2((n << 1) - 1, false);
        std::vector<std::vector<std::string>> ret;
        backtracking(ret, rows, cols, dia1, dia2, 0, n);
        return ret;
    }
};
