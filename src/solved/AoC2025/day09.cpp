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
#include <vector>

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

    static type abs(type value) { return value < 0 ? -value : value; }

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

        long double angle() const {
            return std::atan2(as<long double>(y), as<long double>(x));
        }

        long double angle(Point const& other) const {
            auto dot_product = dot(other);
            auto cross_product = cross(other);
            return std::atan2(as<long double>(cross_product),
                              as<long double>(dot_product));
        }

        long double length() const {
            return std::sqrt((as<long double>(x) * x) +
                             (as<long double>(y) * y));
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

        type dot(Point const& other) const {
            return (as<type>(x) * as<type>(other.x)) +
                   (as<type>(y) * as<type>(other.y));
        }
        type cross(Point const& other) const {
            return (as<type>(x) * as<type>(other.y)) -
                   (as<type>(y) * as<type>(other.x));
        }
    };

    struct Line {
        // NOLINTNEXTLINE
        Point start, end;

        void rotate(Point const& center, long double angle) {
            start.rotate(center, angle);
            end.rotate(center, angle);
        }

        void move(Point const& offset) {
            start += offset;
            end += offset;
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
        explicit Polygon(std::vector<Point> const& pts)
            : n(pts.size()), points(pts) {}

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

        void move(Point const& offset) {
            for (auto& point : points) {
                point += offset;
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

    static long double interpolate_x(Line const& line, long double y) {
        if (line.start.y == line.end.y) {
            return as<long double>(line.start.x);
        }
        long double slope = as<long double>(line.end.x - line.start.x) /
                            as<long double>(line.end.y - line.start.y);
        return (slope * (y - line.start.y)) + line.start.x;
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

    static bool is_on_line(Point const& ptr, Line const& line,
                           bool strict = false) {
        Point vector1 = line.end - line.start;
        Point vector2 = ptr - line.start;
        if (vector1.x == 0 && vector1.y == 0) {
            return ptr == line.start;
        }
        auto cross_product = vector1.cross(vector2);
        if (abs(cross_product) > as<type>(EPS)) {
            return false;
        }
        auto dot_product = vector1.dot(vector2);
        return strict ? dot_product > 0 && dot_product < vector1.dot(vector1)
                      : dot_product >= 0 && dot_product <= vector1.dot(vector1);
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

    static bool poly_point_inside(Polygon const& poly, Point const& ptr,
                                  bool strict = true) {
        auto lines = poly.get_lines();
        size_t n = lines.size();
        int32_t count{0};
        for (size_t i{0}; i < n; ++i) {
            auto const& line = lines[i];
            if (is_on_line(ptr, line, false)) {
                return !strict;
            }
            if ((line.start.x > ptr.x) != (line.end.x > ptr.x)) {
                auto interpolate = interpolate_y(line, as<long double>(ptr.x));
                if (interpolate > as<long double>(ptr.y)) {
                    count++;
                }
            }
        }
        return count & 1;
    }

    static Polygon graham_scan(std::vector<Point> const& points) {
        if (points.size() < 3) {
            throw std::invalid_argument(
                "Graham scan requires at least 3 points to form a polygon.");
        }
        std::vector<Point> hull;
        hull.reserve(points.size());
        auto min_point = *std::min_element(
            points.begin(), points.end(),
            [](Point const& lhs, Point const& rhs) {
                return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x);
            });
        hull.push_back(min_point);
        auto compare_angle = [&min_point](Point const& lhs, Point const& rhs) {
            long double angle_lhs = min_point.angle(lhs);
            long double angle_rhs = min_point.angle(rhs);
            if (std::abs(angle_lhs - angle_rhs) > EPS) {
                return angle_lhs < angle_rhs;
            }
            return lhs.length() < rhs.length();
        };
        std::vector<Point> sorted_points = points;
        std::sort(sorted_points.begin(), sorted_points.end(), compare_angle);
        for (auto const& point : sorted_points) {
            while (hull.size() >= 2 &&
                   ccw(hull[hull.size() - 2], hull.back(), point) <= 0) {
                hull.pop_back();
            }
            hull.push_back(point);
        }
        if (hull.size() > 1 && hull.back() == hull.front()) {
            hull.pop_back();
        }
        return Polygon(hull);
    }
};
template <typename T>
uint16_t Geometry_Basic<T>::mask;

class Solver {
    using geo = Geometry_Basic<int64_t>;
    geo::Polygon poly;
    int64_t r = 0, c = 0;
    size_t n = 0;
    std::vector<std::pair<int64_t, int64_t>> ptrs;
    std::vector<geo::Point> ptrs_geo;
    void read() {
        char temp = 0;
        while (cin >> r >> temp >> c) {
            ptrs.emplace_back(r, c);
            ptrs_geo.emplace_back(r, c);
        }
        n = ptrs.size();
        poly = geo::Polygon(ptrs_geo);
    }
    int64_t area(std::pair<int64_t, int64_t> const& lhs,
                 std::pair<int64_t, int64_t> const& rhs) {
        auto row = std::abs(lhs.first - rhs.first) + 1;
        auto col = std::abs(lhs.second - rhs.second) + 1;
        return row * col;
    }
    int64_t part_1() {
        int64_t ret = 0;
        for (auto i : iota(n)) {
            for (auto j : iota(i + 1, n)) {
                ret = std::max(ret, area(ptrs[i], ptrs[j]));
            }
        }
        return ret;
    }
    bool is_rect_inside_poly(int64_t row1, int64_t col1, int64_t row2,
                             int64_t col2) {
        if (row1 > row2) {
            std::swap(row1, row2);
        }
        if (col1 > col2) {
            std::swap(col1, col2);
        }
        std::vector<geo::Point> corners = {
            {row1, col1}, {row1, col2}, {row2, col2}, {row2, col1}};
        auto rect = geo::Polygon(corners);
        auto rect_lines = rect.get_lines();
        auto static poly_lines =
            poly.get_lines();  // static for performance reason, polygon will
                               // not change during whole run
        // are all points of rect inside of polygon?
        for (auto const& ptr : corners) {
            if (!geo::poly_point_inside(poly, ptr, false)) {
                return false;
            }
        }
        // is there any strict intersect between polygon and rect?
        for (auto const& rect_line : rect_lines) {
            for (auto const& poly_line : poly_lines) {
                if (geo::line_intersect(rect_line, poly_line) ==
                    geo::INTERSECT) {
                    return false;
                }
            }
        }
        // are all points of polygon outside of rect, strictly?
        for (auto const& ptr : ptrs_geo) {
            if (geo::poly_point_inside(rect, ptr, true)) {
                return false;
            }
        }
        return true;
    }
    int64_t part_2() {
        int64_t ret = 0;
        for (auto i : iota(n)) {
            for (auto j : iota(i + 1, n)) {
                if (is_rect_inside_poly(ptrs[i].first, ptrs[i].second,
                                        ptrs[j].first, ptrs[j].second)) {
                    ret = std::max(ret, area(ptrs[i], ptrs[j]));
                }
            }
        }
        return ret;
    }

public:
    void solve() {
        read();
        cout << part_1() << '\n';
        cout << part_2();
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
