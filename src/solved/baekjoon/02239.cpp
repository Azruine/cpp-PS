/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <bit>
#include <iostream>
#include <ranges>
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
constexpr Range iota{};
#pragma GCC diagnostic pop

constexpr uint32_t BOARD = 9;
constexpr uint32_t BLOCK = 3;
}  // namespace

class Solver {
    constexpr static uint32_t MASK = 0B0000'0011'1111'1110;

    std::vector<std::pair<uint32_t, uint32_t>> empty_cells;

    std::array<uint32_t, as<size_t>(BOARD) * BOARD> board = {};
    std::array<uint32_t, BOARD> row_mask = {};
    std::array<uint32_t, BOARD> col_mask = {};
    std::array<uint32_t, BOARD> block_mask = {};

    static uint32_t get_block(uint32_t row, uint32_t col) {
        return ((row / BLOCK) * BLOCK) + (col / BLOCK);
    }

    bool dfs(size_t idx) {
        if (idx == empty_cells.size()) {
            return true;
        }
        auto [row, col] = empty_cells[idx];
        auto block = get_block(row, col);
        auto used = row_mask[row] | col_mask[col] | block_mask[block];
        auto available = (~used) & MASK;
        while (available) {
            auto bit = available & (~available + 1);
            available -= bit;
            auto value = as<uint32_t>(std::countr_zero(bit));

            board[(row * BOARD) + col] = value;
            row_mask[row] |= bit;
            col_mask[col] |= bit;
            block_mask[block] |= bit;

            if (dfs(idx + 1)) {
                return true;
            }

            board[(row * BOARD) + col] = 0;
            row_mask[row] ^= bit;
            col_mask[col] ^= bit;
            block_mask[block] ^= bit;
        }
        return false;
    }

    void read() {
        char temp = '\0';
        for (auto& i : board) {
            cin >> temp;
            i = as<uint32_t>(temp) - '0';
        }
    }
    void setMask() {
        std::ranges::fill(row_mask, 0);
        std::ranges::fill(col_mask, 0);
        std::ranges::fill(block_mask, 0);
        for (auto row : iota(BOARD)) {
            for (auto col : iota(BOARD)) {
                if (board[(row * BOARD) + col] != 0) {
                    auto bit = 1U << board[(row * BOARD) + col];
                    row_mask[row] |= bit;
                    col_mask[col] |= bit;
                    block_mask[get_block(row, col)] |= bit;
                } else {
                    empty_cells.emplace_back(row, col);
                }
            }
        }
    }
    void print() {
        for (auto i : iota(BOARD * BOARD)) {
            cout << board[i];
            if (i % BOARD == BOARD - 1) {
                cout << '\n';
            }
        }
    }

public:
    void solve() {
        read();
        setMask();
        dfs(0);
        print();
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
