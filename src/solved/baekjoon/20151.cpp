/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <set>
#include <type_traits>
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

template <typename T>
struct Geometry_Basic {
    static constexpr long double EPS = 1e-12;
    static uint16_t mask;
    struct custom_ld {
        // NOLINTNEXTLINE
        long double value{0.0L};

        custom_ld() = default;
        explicit custom_ld(long double val) : value(val) {}

        auto operator<=>(custom_ld const& rhs) const {
            long double diff = value - rhs.value;
            if (std::abs(diff) <= EPS) {
                return std::strong_ordering::equal;
            }
            return (diff < 0) ? std::strong_ordering::less
                              : std::strong_ordering::greater;
        }
        bool operator==(custom_ld const& rhs) const {
            return std::abs(value - rhs.value) <= EPS;
        }
    };

    using type =
        std::conditional_t<std::is_integral_v<T>, __int128_t, custom_ld>;

    class Polygon;

    enum LineIntersectType : uint8_t {
        NO_INTERSECT = 0,
        PARALLEL = 1,
        SAME_LINE = 2,
        COLLINEAR_DISJOINT = 3,
        COLLINEAR_TOUCH = 4,
        COLLINEAR_OVERLAPPING = 5,
        TOUCH_AT_END = 6,
        TOUCH_AT_MIDDLE = 7,
        INTERSECT = 8,
    };

    enum PolygonIntersectType : uint8_t {
        NO_OVERLAP = 0,
        POINT_TOUCH = 1,
        LINE_TOUCH = 2,
        PARTIAL_OVERLAP = 3,
        FULL_OVERLAP = 4,
    };

    struct Point {
        // NOLINTNEXTLINE
        T x{0}, y{0};
        bool operator==(Point const& rhs) const {
            return x == rhs.x && y == rhs.y;
        }
        friend std::istream& operator>>(std::istream& is, Point& ptr) {
            is >> ptr.x >> ptr.y;
            return is;
        }
        friend std::ostream& operator<<(std::ostream& os, Point const& ptr) {
            os << ptr.x << ' ' << ptr.y;
            return os;
        }
        Point& operator-=(Point const& rhs) {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }
        Point& operator+=(Point const& rhs) {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }
        friend Point operator-(Point lhs, Point const& rhs) {
            lhs -= rhs;
            return lhs;
        }

        friend Point operator+(Point lhs, Point const& rhs) {
            lhs += rhs;
            return lhs;
        }

        void rotate(Point const& center, long double angle) {
            long double cos_angle = std::cos(angle);
            long double sin_angle = std::sin(angle);
            T new_x = as<T>((cos_angle * (x - center.x)) -
                            (sin_angle * (y - center.y)) + center.x);
            T new_y = as<T>((sin_angle * (x - center.x)) +
                            (cos_angle * (y - center.y)) + center.y);
            x = new_x;
            y = new_y;
        }
    };

    struct Line {
        // NOLINTNEXTLINE
        Point start, end;

        void rotate(Point const& center, long double angle) {
            start.rotate(center, angle);
            end.rotate(center, angle);
        }

        friend std::istream& operator>>(std::istream& is, Line& line) {
            is >> line.start >> line.end;
            return is;
        }
        friend std::ostream& operator<<(std::ostream& os, Line const& line) {
            os << line.start << ' ' << line.end;
            return os;
        }
    };

    struct TaggedLine : Line {
        TaggedLine() = delete;
        TaggedLine(Line const& line,
                   std::reference_wrapper<Polygon const> parent_poly)
            : Line(line), parent(parent_poly) {}
        // NOLINTNEXTLINE
        std::reference_wrapper<Polygon const> parent;
    };

    struct Event {
        Event() = delete;
        Event(T x_coord, bool is_left_event,
              std::reference_wrapper<Line const> line_)
            : x(x_coord), is_left(is_left_event), line(line_) {}
        // NOLINTBEGIN
        T x{0};
        bool is_left{false};
        std::reference_wrapper<Line const> line;
        // NOLINTEND

        bool operator<(Event const& rhs) const {
            if (x != rhs.x) {
                return x < rhs.x;
            }
            return is_left < rhs.is_left;
        }
    };

    struct CompareByY {
        // NOLINTNEXTLINE
        long double const& cur_sweep_x;
        CompareByY() = delete;
        explicit CompareByY(long double const& cur_sweep_x_)
            : cur_sweep_x(cur_sweep_x_) {}

        bool operator()(Line const& line1, Line const& line2) const {
            long double y1 = interpolate_y(line1, cur_sweep_x);
            long double y2 = interpolate_y(line2, cur_sweep_x);
            if (y1 != y2) {
                return y1 < y2;
            }
            return &line1 < &line2;
        }
    };

    class Polygon {
    public:
        Polygon() = default;
        explicit Polygon(size_t sz) : n(sz), points(sz) {}

        void resize(size_t new_n) {
            n = new_n;
            points.resize(new_n);
        }

        size_t size() const { return n; }

        Point& operator[](size_t i) { return points[i]; }
        Point const& operator[](size_t i) const { return points[i]; }

        friend std::istream& operator>>(std::istream& is, Polygon& poly) {
            for (auto& point : poly.points) {
                is >> point;
            }
            return is;
        }
        friend std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
            for (auto const& point : poly.points) {
                os << point << '\n';
            }
            return os;
        }

        std::vector<Line> get_lines() const {
            std::vector<Line> lines;
            for (size_t i = 0; i < n; ++i) {
                Line line;
                line.start = points[i];
                line.end = points[(i + 1) % n];
                lines.push_back(std::move(line));
            }
            return lines;
        }

        std::vector<TaggedLine> get_tagged_lines() const {
            std::vector<TaggedLine> lines;
            lines.reserve(n);
            for (size_t i{0}; i < n; i++) {
                TaggedLine Tline{Line{points[i], points[(i + 1) % n]},
                                 std::cref(*this)};
                lines.push_back(std::move(Tline));
            }
            return lines;
        }

        void rotate(Point const& center, long double angle) {
            for (auto& point : points) {
                point.rotate(center, angle);
            }
        }

    private:
        size_t n{0};
        std::vector<Point> points;
    };

    static long double interpolate_y(Line const& line, long double x) {
        if (line.start.x == line.end.x) {
            return as<long double>(line.start.y);
        }
        long double slope = as<long double>(line.end.y - line.start.y) /
                            as<long double>(line.end.x - line.start.x);
        return (slope * (x - line.start.x)) + line.start.y;
    }

    static int32_t ccw(Point const& ptr1, Point const& ptr2,
                       Point const& ptr3) {
        auto ret{0};
        type area = as<type>((ptr2.x - ptr1.x) * (ptr3.y - ptr1.y)) -
                    as<type>((ptr2.y - ptr1.y) * (ptr3.x - ptr1.x));
        if (area > 0) {
            ret = +1;
        } else if (area < 0) {
            ret = -1;
        } else {
            ret = 0;
        }
        return ret;
    }

    static bool is_parallel_slope(Point const& ptr1, Point const& ptr2) {
        return as<type>(ptr1.x) * ptr2.y == as<type>(ptr1.y) * ptr2.x;
    }

    static bool is_same_line(Line const& line1, Line const& line2) {
        return (line1.start == line2.start && line1.end == line2.end) ||
               (line1.start == line2.end && line1.end == line2.start);
    }

    static std::array<T, 4> reflect_points(Line const& line1,
                                           Line const& line2) {
        // reflect points to axis
        auto refl = (line1.start.x == line1.end.x)
                        ? std::array<T, 4>{line1.start.y, line1.end.y,
                                           line2.start.y, line2.end.y}
                        : std::array<T, 4>{line1.start.x, line1.end.x,
                                           line2.start.x, line2.end.x};
        // sort reflected points
        if (refl[0] > refl[1]) {
            std::swap(refl[0], refl[1]);
        }
        if (refl[2] > refl[3]) {
            std::swap(refl[2], refl[3]);
        }
        return refl;
    }

    static LineIntersectType line_intersect(Line const& line1,
                                            Line const& line2) {
        if (is_same_line(line1, line2)) {
            return SAME_LINE;
        }
        auto ptrs = std::array<Point, 4>{line1.start, line1.end, line2.start,
                                         line2.end};
        auto ccw_result = std::array<int32_t, 4>{
            ccw(ptrs[0], ptrs[1], ptrs[2]), ccw(ptrs[0], ptrs[1], ptrs[3]),
            ccw(ptrs[2], ptrs[3], ptrs[0]), ccw(ptrs[2], ptrs[3], ptrs[1])};
        // find slopes
        Point slope1 = line1.end - line1.start;
        Point slope2 = line2.end - line2.start;

        if (is_parallel_slope(slope1, slope2)) {
            // if ccw is not zero, lines are parallel
            if (ccw_result[0] != 0) {
                return PARALLEL;
            }
            // reflect points to axis
            auto refl = reflect_points(line1, line2);
            // Case 1. line overlap in infinite points
            // c or d included in (a, b) || a or b included in (c, d)
            if ((refl[2] > refl[0] && refl[2] < refl[1]) ||
                (refl[3] > refl[0] && refl[3] < refl[1]) ||
                (refl[0] > refl[2] && refl[0] < refl[3]) ||
                (refl[1] > refl[2] && refl[1] < refl[3])) {
                return COLLINEAR_OVERLAPPING;
            }
            // Case 2. c or d equal to a or b - Touch at end
            if (refl[0] == refl[2] || refl[0] == refl[3] ||
                refl[1] == refl[2] || refl[1] == refl[3]) {
                return TOUCH_AT_END;
            }
            // Case 3. No intersection
            return COLLINEAR_DISJOINT;
        }
        // Different slopes
        if (line1.start == line2.start || line1.start == line2.end ||
            line1.end == line2.start || line1.end == line2.end) {
            return TOUCH_AT_END;
        }
        type det =
            (as<type>(slope1.x) * slope2.y) - (as<type>(slope1.y) * slope2.x);
        type dx = as<type>(line2.start.x - line1.start.x);
        type dy = as<type>(line2.start.y - line1.start.y);
        type t_ = (dx * slope2.y) - (dy * slope2.x);
        type u_ = (dx * slope1.y) - (dy * slope1.x);

        if (det < 0) {
            det = -det;
            t_ = -t_;
            u_ = -u_;
        }
        if (t_ > 0 && t_ < det && u_ > 0 && u_ < det) {
            // Case 1. Lines intersect at a point
            return INTERSECT;
        }
        if (((t_ == 0 || t_ == det) && (u_ >= 0 && u_ <= det)) ||
            ((u_ == 0 || u_ == det) && (t_ >= 0 && t_ <= det))) {
            // Case 2. Lines touch at middle
            return TOUCH_AT_MIDDLE;
        }
        // Case 3. No intersection
        return NO_INTERSECT;
    }

    static bool line_intersect_wrapper(Line const& line1, Line const& line2) {
        return mask & (1 << line_intersect(line1, line2));
    }

    static bool event_sweep(auto& active_lines, Event& event,
                            long double& cur_sweep_x) {
        auto& line_ref = event.line.get();
        auto x = as<long double>(event.x);
        if (!event.is_left) {
            cur_sweep_x = x - 1;
            auto it = active_lines.find(std::cref(line_ref));
            if (it != active_lines.end()) {
                auto next_it = std::next(it);
                if (it != active_lines.begin() &&
                    next_it != active_lines.end()) {
                    auto prev_it = std::prev(it);
                    if (line_intersect_wrapper((*next_it).get(),
                                               (*prev_it).get())) {
                        cur_sweep_x = x;
                        return true;
                    }
                }
                active_lines.erase(it);
            }
            cur_sweep_x = x;
        } else {
            cur_sweep_x = x + 1;
            auto [it, inserted] = active_lines.insert(std::cref(line_ref));
            if (inserted) {
                auto next_it = std::next(it);
                if (next_it != active_lines.end() &&
                    line_intersect_wrapper((*next_it).get(), line_ref)) {
                    cur_sweep_x = x;
                    return true;
                }
                if (it != active_lines.begin()) {
                    auto prev_it = std::prev(it);
                    if (line_intersect_wrapper((*prev_it).get(), line_ref)) {
                        cur_sweep_x = x;
                        return true;
                    }
                }
            }
            cur_sweep_x = x;
        }
        return false;
    }

    static bool find_line_intersect(std::vector<Line> const& lines) {
        long double cur_sweep_x{0};
        size_t n{lines.size()};
        std::vector<Event> events;
        events.reserve(2 * n);

        for (size_t i{0}; i < n; ++i) {
            auto x1 = lines[i].start.x;
            auto x2 = lines[i].end.x;
            if (x1 <= x2) {
                events.emplace_back(x1, true, std::cref(lines[i]));
                events.emplace_back(x2, false, std::cref(lines[i]));
            } else {
                events.emplace_back(x2, true, std::cref(lines[i]));
                events.emplace_back(x1, false, std::cref(lines[i]));
            }
        }
        std::sort(events.begin(), events.end());

        CompareByY compare_by_y(cur_sweep_x);
        std::set<std::reference_wrapper<Line const>, CompareByY> active_lines(
            compare_by_y);
        for (auto& event : events) {
            if (event_sweep(active_lines, event, cur_sweep_x)) {
                return true;
            }
        }
        return false;
    }
};
template <typename T>
uint16_t Geometry_Basic<T>::mask;

class Solver {
    using Geometry = Geometry_Basic<int64_t>;

public:
    void solve() {
        cin >> n;
        lines.resize(n);
        for (auto& line : lines) {
            cin >> line;
        }
        Geometry::mask =
            (1 << Geometry::LineIntersectType::SAME_LINE) |
            (1 << Geometry::LineIntersectType::COLLINEAR_OVERLAPPING) |
            (1 << Geometry::LineIntersectType::TOUCH_AT_MIDDLE) |
            (1 << Geometry::LineIntersectType::INTERSECT);

        cout << Geometry::find_line_intersect(lines);
    }

private:
    size_t n{0};
    std::vector<Geometry::Line> lines;
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
