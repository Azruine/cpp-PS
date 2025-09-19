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

#include <array>
#include <cstdint>
#include <regex>
#include <string>

class Spreadsheet {
    constexpr static size_t ROW = 1'010;
    constexpr static size_t COL = 26;
    std::array<std::array<int32_t, COL>, ROW> _board = {};

public:
    Spreadsheet(int _) {}

    void setCell(std::string cell, int value) {
        size_t col = as<size_t>(cell[0] - 'A');
        size_t row = stoul(cell.substr(1));
        _board[row][col] = value;
    }

    void resetCell(std::string cell) {
        size_t col = as<size_t>(cell[0] - 'A');
        size_t row = stoul(cell.substr(1));
        _board[row][col] = 0;
    }
    int getValue(std::string formula) {
        constexpr static size_t VAL1_START = 1;
        size_t val1_len = 1;
        while (formula[VAL1_START + val1_len] != '+') {
            val1_len++;
        }
        int32_t val1 = 0;
        int32_t val2 = 0;
        if (std::isalpha(formula[1])) {
            size_t col = as<size_t>(formula[1] - 'A');
            size_t row = stoul(formula.substr(VAL1_START + 1, val1_len));
            val1 = _board[row][col];
        } else {
            val1 = stoi(formula.substr(VAL1_START, val1_len));
        }
        if (std::isalpha(formula[VAL1_START + val1_len + 1])) {
            size_t col = as<size_t>(formula[VAL1_START + val1_len + 1] - 'A');
            size_t row = stoul(formula.substr(VAL1_START + val1_len + 2));
            val2 = _board[row][col];
        } else {
            val2 = stoi(formula.substr(VAL1_START + val1_len + 1));
        }
        return val1 + val2;
    }
};
