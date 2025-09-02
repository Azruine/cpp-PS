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

#include <algorithm>
#include <vector>

struct Point {
    int32_t x = 0, y = 0;
    bool operator<(Point const& rhs) const noexcept {
        if (this->x == rhs.x) {
            return this->y > rhs.y;
        }
        return this->x < rhs.x;
    }
    bool operator==(Point const& rhs) const noexcept {
        return this->x == rhs.x && this->y == rhs.y;
    }
};

class Solution {
public:
    int numberOfPairs(std::vector<std::vector<int32_t>>& points_) {
        int32_t ans = 0;
        std::vector<Point> points;
        auto n = points_.size();
        points.reserve(n);
        for (auto const& point : points_) {
            points.push_back(Point{.x = point[0], .y = point[1]});
        }
        std::ranges::sort(points, std::less<>{});
        for (auto i : _iota(n)) {
            for (auto j : _iota(i + 1, n)) {
                bool flag = true;
                // ensure top left
                auto& lhs = points[i];
                auto& rhs = points[j];
                if ((lhs.x <= rhs.x && lhs.y >= rhs.y) ||
                    (lhs.x >= rhs.x && lhs.y <= rhs.y)) {
                    for (auto k : _iota(n)) {
                        if (k == i || k == j) {
                            continue;
                        }
                        auto& comp = points[k];
                        if ((lhs.x <= comp.x && comp.x <= rhs.x &&
                             lhs.y >= comp.y && comp.y >= rhs.y) ||
                            (lhs.x >= comp.x && comp.x >= rhs.x &&
                             lhs.y <= comp.y && comp.y <= rhs.y)) {
                            flag = false;
                            break;
                        }
                    }
                } else {
                    flag = false;
                }
                if (flag) {
                    ans += 1;
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    std::vector<std::vector<int32_t>> points{{1, 1}, {2, 2}, {3, 3}};
    sol.numberOfPairs(points);
    return 0;
}
