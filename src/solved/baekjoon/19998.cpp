/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <optional>
#include <ranges>
#include <span>
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

constexpr size_t BOARD = 9;
constexpr size_t CONSTRAINT = 4;
constexpr size_t BLOCK = 3;
}  // namespace

struct DancingNode {
    size_t left = 0, right = 0, up = 0, down = 0;
    size_t column = 0;
    size_t size = 0;

    std::optional<size_t> row, col, num;
};

class DancingLinks {
    size_t header_idx = 0;
    std::vector<DancingNode> nodes;
    std::vector<size_t> sol_stack;
    std::vector<size_t> fixed_rows;
    std::span<size_t> m_board;

    size_t add_node() {
        nodes.emplace_back();
        return nodes.size() - 1;
    }

    bool search(size_t k) {
        if (nodes[header_idx].right == header_idx) {
            return true;
        }

        size_t col = select_column();
        if (nodes[col].size == 0) {
            return false;
        }

        cover(col);

        for (size_t row = nodes[col].down; row != col; row = nodes[row].down) {
            sol_stack.push_back(row);

            for (size_t j = nodes[row].right; j != row; j = nodes[j].right) {
                cover(nodes[j].column);
            }

            if (search(k + 1)) {
                return true;
            }

            sol_stack.pop_back();
            for (size_t j = nodes[row].left; j != row; j = nodes[j].left) {
                uncover(nodes[j].column);
            }
        }

        uncover(col);
        return false;
    }

    size_t select_column() {
        size_t best = nodes[header_idx].right;
        size_t min_size = nodes[best].size;

        for (size_t col = nodes[header_idx].right; col != header_idx;
             col = nodes[col].right) {
            if (nodes[col].size < min_size) {
                best = col;
                min_size = nodes[col].size;
            }
        }
        return best;
    }
    __attribute__((always_inline)) void cover(size_t col_idx) {
        auto& cur = nodes[col_idx];
        nodes[cur.right].left = cur.left;
        nodes[cur.left].right = cur.right;

        for (size_t i = cur.down; i != col_idx; i = nodes[i].down) {
            for (size_t j = nodes[i].right; j != i; j = nodes[j].right) {
                nodes[nodes[j].down].up = nodes[j].up;
                nodes[nodes[j].up].down = nodes[j].down;
                nodes[nodes[j].column].size -= 1;
            }
        }
    }
    __attribute__((always_inline)) void uncover(size_t col_idx) {
        auto& cur = nodes[col_idx];
        for (size_t i = cur.up; i != col_idx; i = nodes[i].up) {
            for (size_t j = nodes[i].left; j != i; j = nodes[j].left) {
                nodes[nodes[j].column].size += 1;
                nodes[nodes[j].down].up = j;
                nodes[nodes[j].up].down = j;
            }
        }

        nodes[cur.right].left = col_idx;
        nodes[cur.left].right = col_idx;
    }

    void init(std::span<size_t>& board) {
        m_board = board;
        nodes.clear();
        nodes.reserve(1 + (BOARD * BOARD * CONSTRAINT) +
                      (BOARD * BOARD * BOARD));
        sol_stack.clear();
        sol_stack.reserve(BOARD * BOARD);
        fixed_rows.clear();

        header_idx = add_node();
        nodes[header_idx].left = header_idx;
        nodes[header_idx].right = header_idx;

        size_t prev_col = header_idx;
        for (auto _ : iota(BOARD * BOARD * CONSTRAINT)) {
            size_t new_col = add_node();
            nodes[new_col].column = new_col;
            nodes[new_col].up = new_col;
            nodes[new_col].down = new_col;

            nodes[new_col].left = prev_col;
            nodes[new_col].right = header_idx;
            nodes[prev_col].right = new_col;
            nodes[header_idx].left = new_col;

            prev_col = new_col;
        }
    }

    void build() {
        for (size_t row : iota(BOARD)) {
            for (size_t col : iota(BOARD)) {
                size_t value = m_board[(row * BOARD) + col];
                if (value != 0) {
                    size_t row_start = nodes.size();
                    add_row(row, col, value);
                    fixed_rows.push_back(row_start);
                } else {
                    for (size_t cand : iota(1U, BOARD + 1)) {
                        add_row(row, col, cand);
                    }
                }
            }
        }

        for (size_t fixed_row_start : fixed_rows) {
            sol_stack.push_back(fixed_row_start);

            for (size_t j = fixed_row_start;; j = nodes[j].right) {
                cover(nodes[j].column);
                if (nodes[j].right == fixed_row_start) {
                    break;
                }
            }
        }
    }

    void add_row(size_t row, size_t col, size_t value) {
        size_t cell_col = 1 + (row * BOARD) + col;
        size_t row_col = 1 + (BOARD * BOARD) + (row * BOARD) + (value - 1);
        size_t col_col = 1 + (BOARD * BOARD * 2) + (col * BOARD) + (value - 1);
        size_t block = ((row / BLOCK) * BLOCK) + (col / BLOCK);
        size_t block_col = 1 + (BOARD * BOARD * (CONSTRAINT - 1)) +
                           (block * BOARD) + (value - 1);

        std::array<size_t, 4> constraints = {cell_col, row_col, col_col,
                                             block_col};

        size_t first = SIZE_MAX;
        size_t prev = SIZE_MAX;
        for (auto col_idx : constraints) {
            size_t idx = add_node();
            nodes[idx].column = col_idx;
            nodes[idx].row = row;
            nodes[idx].col = col;
            nodes[idx].num = value;

            nodes[col_idx].size += 1;

            nodes[idx].down = col_idx;
            nodes[idx].up = nodes[col_idx].up;
            nodes[nodes[col_idx].up].down = idx;
            nodes[col_idx].up = idx;

            if (prev == SIZE_MAX) {
                first = idx;
                prev = idx;
                nodes[idx].left = idx;
                nodes[idx].right = idx;
            } else {
                nodes[idx].left = prev;
                nodes[idx].right = first;
                nodes[prev].right = idx;
                nodes[first].left = idx;
                prev = idx;
            }
        }
    }

public:
    bool solve(std::span<size_t> board) {
        init(board);
        build();

        if (search(fixed_rows.size())) {
            for (size_t idx : sol_stack) {
                auto& node = nodes[idx];
                if (node.row.has_value() && node.col.has_value() &&
                    node.num.has_value()) {
                    m_board[(node.row.value() * BOARD) + node.col.value()] =
                        node.num.value();
                }
            }
            return true;
        }
        return false;
    }
};

class Solver {
    DancingLinks dlx;
    std::array<size_t, BOARD * BOARD> board = {};

public:
    void solve() {
        for (auto& i : board) {
            cin >> i;
        }

        if (dlx.solve(board)) {
            for (auto i : iota(BOARD * BOARD)) {
                cout << board.at(i) << " \n"[i % BOARD == BOARD - 1];
            }
        } else {
            cout << "BAD\n";
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
