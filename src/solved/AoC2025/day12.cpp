/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <type_traits>
#include <utility>

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

template <typename T>
class iota_iterator {
    T current_;
    T step_;

public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    explicit constexpr iota_iterator(T current, T step = T{1}) noexcept
        : current_(current), step_(step) {}

    constexpr T operator*() const noexcept { return current_; }
    constexpr const T* operator->() const noexcept { return &current_; }

    constexpr iota_iterator& operator++() noexcept {
        current_ += step_;
        return *this;
    }
    constexpr iota_iterator operator++(int) noexcept {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    constexpr iota_iterator& operator--() noexcept {
        current_ -= step_;
        return *this;
    }
    constexpr iota_iterator operator--(int) noexcept {
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    constexpr iota_iterator& operator+=(difference_type n) noexcept {
        current_ += step_ * static_cast<T>(n);
        return *this;
    }
    constexpr iota_iterator& operator-=(difference_type n) noexcept {
        current_ -= step_ * static_cast<T>(n);
        return *this;
    }

    constexpr iota_iterator operator+(difference_type n) const noexcept {
        return iota_iterator(current_ + (step_ * static_cast<T>(n)), step_);
    }
    constexpr iota_iterator operator-(difference_type n) const noexcept {
        return iota_iterator(current_ - (step_ * static_cast<T>(n)), step_);
    }

    constexpr difference_type operator-(
        const iota_iterator& other) const noexcept {
        return static_cast<difference_type>((current_ - other.current_) /
                                            step_);
    }

    constexpr T operator[](difference_type n) const noexcept {
        return current_ + (step_ * static_cast<T>(n));
    }

    constexpr auto operator<=>(const iota_iterator& other) const noexcept {
        return step_ > 0 ? (current_ <=> other.current_)
                         : (other.current_ <=> current_);
    }

    constexpr bool operator==(const iota_iterator& other) const noexcept {
        return current_ == other.current_;
    }
};

template <typename T>
class iota_view {
    T start_, end_, step_;

public:
    using iterator = iota_iterator<T>;
    using const_iterator = iterator;
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    constexpr iota_view(T start, T end, T step = T{1}) noexcept
        : start_(start), end_(end), step_(step) {
        if (step_ < 0 && start_ > end_) {
            auto diff = start_ - end_;
            auto steps = diff / (-step_);
            if (diff % (-step_) != 0) {
                steps++;
            }
            end_ = start_ - (steps * (-step_));
        } else if (step_ > 0 && start_ > end_) {
            start_ = end_;
        }
    }

    constexpr iterator begin() const noexcept {
        return iterator(start_, step_);
    }

    constexpr iterator end() const noexcept { return iterator(end_, step_); }

    constexpr bool empty() const noexcept {
        return (step_ > 0) ? (start_ >= end_) : (start_ <= end_);
    }

    constexpr size_type size() const noexcept {
        if (empty()) {
            return 0;
        }
        if (step_ > 0) {
            return static_cast<size_type>((end_ - start_ + step_ - 1) / step_);
        }
        return static_cast<size_type>((start_ - end_ + (-step_) - 1) /
                                      (-step_));
    }
};

struct Range {
    template <typename Sentinel>
    constexpr auto operator()(Sentinel sentinel) const noexcept {
        using T = std::common_type_t<int, Sentinel>;
        return iota_view<T>(T{0}, static_cast<T>(sentinel));
    }

    template <typename Start, typename Sentinel>
    constexpr auto operator()(Start start, Sentinel sentinel) const noexcept {
        using T = std::common_type_t<Start, Sentinel>;
        return iota_view<T>(static_cast<T>(start), static_cast<T>(sentinel));
    }

    template <typename Start, typename Sentinel, typename Step>
    constexpr auto operator()(Start start, Sentinel sentinel,
                              Step step) const noexcept {
        using T = std::common_type_t<Start, Sentinel, Step>;
        return iota_view<T>(static_cast<T>(start), static_cast<T>(sentinel),
                            static_cast<T>(step));
    }
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
constexpr Range iota{};
#pragma GCC diagnostic pop
}  // namespace

#include <algorithm>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class DLX {
public:
    std::vector<int> L, R, U, D, C, S;
    std::vector<int> rowId;
    int size, first;
    void init(int n_first, int n_second) {
        first = n_first;
        int nCols = n_first + n_second;
        size = nCols + 1;
        L.resize(size);
        R.resize(size);
        U.resize(size);
        D.resize(size);
        C.resize(size);
        S.assign(size, 0);
        for (int i = 0; i <= n_first; i++) {
            L[i] = i - 1;
            R[i] = i + 1;
            U[i] = D[i] = i;
            C[i] = i;
        }
        L[0] = n_first;
        R[n_first] = 0;
        for (int i = n_first + 1; i <= nCols; i++) {
            L[i] = R[i] = i;
            U[i] = D[i] = i;
            C[i] = i;
        }
    }
    void addRow(int row, std::vector<int> const& cols) {
        if (cols.empty()) {
            return;
        }
        int start = size;
        for (int col : cols) {
            L.push_back(size - 1);
            R.push_back(size + 1);
            U.push_back(U[col]);
            D.push_back(col);
            C.push_back(col);
            rowId.push_back(row);

            D[U[col]] = size;
            U[col] = size;
            S[col]++;
            size++;
        }
        R[size - 1] = start;
        L[start] = size - 1;
    }
    void cover(int col) {
        L[R[col]] = L[col];
        R[L[col]] = R[col];
        for (int i = D[col]; i != col; i = D[i]) {
            for (int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                S[C[j]]--;
            }
        }
    }
    void uncover(int col) {
        for (int i = U[col]; i != col; i = U[i]) {
            for (int j = L[i]; j != i; j = L[j]) {
                S[C[j]]++;
                U[D[j]] = j;
                D[U[j]] = j;
            }
        }
        L[R[col]] = col;
        R[L[col]] = col;
    }
    bool solve() {
        if (R[0] == 0) {
            return true;
        }
        int col = R[0];
        for (int i = R[0]; i != 0; i = R[i]) {
            if (S[i] < S[col]) {
                col = i;
            }
        }
        if (S[col] == 0) {
            return false;
        }
        cover(col);
        for (int row = D[col]; row != col; row = D[row]) {
            for (int j = R[row]; j != row; j = R[j]) {
                cover(C[j]);
            }
            if (solve()) {
                return true;
            }
            for (int j = L[row]; j != row; j = L[j]) {
                uncover(C[j]);
            }
        }
        uncover(col);
        return false;
    }
};

class Solver {
    using Gift = std::vector<std::pair<int32_t, int32_t>>;
    struct Tile {
        int32_t id = 0;
        std::vector<Gift> variants;
    };
    struct Set {
        int32_t width, height;
        std::vector<int32_t> cnt;
    };
    std::vector<Tile> gifts;
    std::vector<Set> sets;
    Gift normalize(Gift gift) {
        if (gift.empty()) {
            return gift;
        }
        std::ranges::sort(gift);
        int minR = gift[0].first, minC = gift[0].second;
        for (auto& pair : gift) {
            minC = std::min(minC, pair.second);
        }
        for (auto& pair : gift) {
            pair.first -= minR;
            pair.second -= minC;
        }
        std::ranges::sort(gift);
        return gift;
    }
    Gift rotate_cw(const Gift& gift) {
        Gift res;
        for (auto [r, c] : gift) {
            res.emplace_back(c, -r);
        }
        return normalize(res);
    }
    Gift flip(const Gift& gift) {
        Gift res;
        for (auto [r, c] : gift) {
            res.emplace_back(r, -c);
        }
        return normalize(res);
    }
    std::vector<Gift> get_all_variants(Gift const& base) {
        std::set<Gift> seen;
        std::vector<Gift> result;

        Gift cur = normalize(base);
        for (int flipped = 0; flipped < 2; flipped++) {
            for (int rotated = 0; rotated < 4; rotated++) {
                if (seen.find(cur) == seen.end()) {
                    seen.insert(cur);
                    result.push_back(cur);
                }
                cur = rotate_cw(cur);
            }
            cur = flip(cur);
        }
        return result;
    }
    void read() {
        std::vector<std::string> lines;
        std::string str;
        while (std::getline(std::cin, str)) {
            if (!str.empty()) {
                lines.push_back(str);
            }
        }

        for (size_t i = 0; i < lines.size();) {
            auto const& line = lines[i];
            if (line.find('x') != std::string::npos) {
                Set problem;
                int32_t pos = line.find('x');
                problem.width = std::stoi(line.substr(0, pos));
                int32_t colonPos = line.find(':');
                problem.height =
                    std::stoi(line.substr(pos + 1, colonPos - pos - 1));
                std::stringstream sstr(line.substr(colonPos + 1));
                int32_t cnt = 0;
                while (sstr >> cnt) {
                    problem.cnt.push_back(cnt);
                }
                sets.push_back(problem);
                i++;
            } else if (line.find(':') != std::string::npos) {
                int32_t id = std::stoi(line.substr(0, line.find(':')));
                Gift base;
                for (int row = 0; row < 3; row++) {
                    const auto& row_line = lines[i + 1 + row];
                    for (int col = 0;
                         col < 3 && col < as<int32_t>(row_line.size()); col++) {
                        if (row_line[col] == '#') {
                            base.emplace_back(row, col);
                        }
                    }
                }
                Tile tile;
                tile.id = id;
                tile.variants = get_all_variants(base);
                gifts.push_back(std::move(tile));
                i += 4;
            } else {
                i++;
            }
        }
    }
    bool is_fit(size_t idx) {
        auto& problem = sets[idx];
        int32_t cells = 0, pieces = 0;
        auto size = problem.width * problem.height;
        for (auto i = 0U; i < problem.cnt.size(); i++) {
            cells += problem.cnt[i] * gifts[i].variants[0].size();
            pieces += problem.cnt[i];
        }
        if (cells > size) {
            return false;
        }
        // first col: [1, pieces] - each tiles - must use
        // second col: [pieces + 1, pieces + size] - each cell - most once
        DLX dlx;
        dlx.init(pieces, size);
        size_t piece_idx = 0;
        for (auto i = 0U; i < problem.cnt.size(); i++) {
            for (auto instance = 0; instance < problem.cnt[i]; instance++) {
                auto piece_col = piece_idx + 1;
                for (auto const& shape : gifts[i].variants) {
                    int32_t max_row = 0, max_col = 0;
                    for (auto [r, c] : shape) {
                        max_row = std::max(r, max_row);
                        max_col = std::max(c, max_col);
                    }
                    for (auto row = 0; row + max_row < problem.height; row++) {
                        for (auto col = 0; col + max_col < problem.width;
                             col++) {
                            std::vector<int32_t> cols;
                            cols.push_back(piece_col);
                            for (auto [dr, dc] : shape) {
                                auto next_row = row + dr, next_col = col + dc;
                                cols.push_back(pieces + 1 +
                                               next_row * problem.width +
                                               next_col);
                            }
                            dlx.addRow(piece_idx, cols);
                        }
                    }
                }
                piece_idx++;
            }
        }
        return dlx.solve();
    }
    int32_t part_1() {
        int32_t ret = 0;
        auto n = sets.size();
        for (auto i : iota(n)) {
            ret += is_fit(i);
            std::cerr << i << '\n';
        }
        return ret;
    }

public:
    void solve() {
        read();
        cout << part_1() << '\n';
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
