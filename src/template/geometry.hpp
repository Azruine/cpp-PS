/*==== Copyright 2025 Azruine ====*/
#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <optional>
#include <set>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

namespace geometry {

/*========== Internal Helpers ==========*/

constexpr long double EPSILON = 1e-12L;

template <typename To, typename From>
constexpr To as(From&& from) noexcept {
    return static_cast<To>(std::forward<From>(from));
}

// epsilon-aware long double, used as the wide accumulator type for floating
// point coordinates. Comparisons treat values within EPSILON as equal.
struct EpsilonLongDouble {
    long double value{0.0L};

    EpsilonLongDouble() = default;
    explicit EpsilonLongDouble(long double initial) : value(initial) {}

    auto operator<=>(EpsilonLongDouble const& rhs) const {
        long double const difference = value - rhs.value;
        if (std::abs(difference) <= EPSILON) {
            return std::strong_ordering::equal;
        }
        if (difference < 0) {
            return std::strong_ordering::less;
        }
        return std::strong_ordering::greater;
    }

    bool operator==(EpsilonLongDouble const& rhs) const {
        return std::abs(value - rhs.value) <= EPSILON;
    }

    EpsilonLongDouble operator-() const {
        return EpsilonLongDouble{-value};
    }
    EpsilonLongDouble operator+(EpsilonLongDouble const& rhs) const {
        return EpsilonLongDouble{value + rhs.value};
    }
    EpsilonLongDouble operator-(EpsilonLongDouble const& rhs) const {
        return EpsilonLongDouble{value - rhs.value};
    }
    EpsilonLongDouble operator*(EpsilonLongDouble const& rhs) const {
        return EpsilonLongDouble{value * rhs.value};
    }

    explicit operator long double() const { return value; }
};

// Wide accumulator type chosen per scalar T:
//   integral  -> __int128_t (safe for product of two int64_t)
//   floating  -> EpsilonLongDouble (epsilon-aware comparisons)
template <typename T>
using wide_t =
    std::conditional_t<std::is_integral_v<T>, __int128_t, EpsilonLongDouble>;

template <typename T>
constexpr wide_t<T> wide_abs(wide_t<T> value) {
    return value < wide_t<T>{0} ? -value : value;
}

/*========== Data Type: Point ==========*/

template <typename T>
struct Point {
    T x{0};
    T y{0};

    bool operator==(Point const& rhs) const {
        if constexpr (std::is_floating_point_v<T>) {
            return std::abs(x - rhs.x) <= EPSILON &&
                   std::abs(y - rhs.y) <= EPSILON;
        } else {
            return x == rhs.x && y == rhs.y;
        }
    }

    Point& operator+=(Point const& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Point& operator-=(Point const& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    friend Point operator+(Point lhs, Point const& rhs) {
        lhs += rhs;
        return lhs;
    }
    friend Point operator-(Point lhs, Point const& rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend std::istream& operator>>(std::istream& is, Point& point) {
        is >> point.x >> point.y;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Point const& point) {
        os << point.x << ' ' << point.y;
        return os;
    }

    wide_t<T> dot(Point const& other) const {
        return as<wide_t<T>>(x) * as<wide_t<T>>(other.x) +
               as<wide_t<T>>(y) * as<wide_t<T>>(other.y);
    }

    wide_t<T> cross(Point const& other) const {
        return as<wide_t<T>>(x) * as<wide_t<T>>(other.y) -
               as<wide_t<T>>(y) * as<wide_t<T>>(other.x);
    }

    long double length() const {
        long double const xf = as<long double>(x);
        long double const yf = as<long double>(y);
        return std::sqrt(xf * xf + yf * yf);
    }

    long double angle() const {
        return std::atan2(as<long double>(y), as<long double>(x));
    }

    // angle from this point to other, in (-pi, pi]
    long double angle_to(Point const& other) const {
        Point const offset = other - *this;
        return std::atan2(as<long double>(offset.y),
                          as<long double>(offset.x));
    }

    void rotate(Point const& center, long double radians) {
        long double const cos_angle = std::cos(radians);
        long double const sin_angle = std::sin(radians);
        long double const offset_x = as<long double>(x - center.x);
        long double const offset_y = as<long double>(y - center.y);
        long double const new_x =
            cos_angle * offset_x - sin_angle * offset_y + as<long double>(center.x);
        long double const new_y =
            sin_angle * offset_x + cos_angle * offset_y + as<long double>(center.y);
        x = as<T>(new_x);
        y = as<T>(new_y);
    }
};

/*========== Data Type: Line ==========*/

template <typename T>
struct Line {
    Point<T> start;
    Point<T> end;

    void rotate(Point<T> const& center, long double radians) {
        start.rotate(center, radians);
        end.rotate(center, radians);
    }

    void move(Point<T> const& offset) {
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

/*========== Data Type: Polygon ==========*/

template <typename T>
class Polygon {
public:
    Polygon() = default;
    explicit Polygon(std::size_t vertex_count) : points_(vertex_count) {}
    explicit Polygon(std::vector<Point<T>> points) : points_(std::move(points)) {}

    void resize(std::size_t new_size) {
        points_.resize(new_size);
    }

    std::size_t size() const {
        return points_.size();
    }

    Point<T>& operator[](std::size_t index) {
        return points_[index];
    }
    Point<T> const& operator[](std::size_t index) const {
        return points_[index];
    }

    std::vector<Line<T>> edges() const {
        std::size_t const vertex_count = points_.size();
        std::vector<Line<T>> result;
        result.reserve(vertex_count);
        for (std::size_t index = 0; index < vertex_count; ++index) {
            result.push_back(
                Line<T>{points_[index], points_[(index + 1) % vertex_count]});
        }
        return result;
    }

    void rotate(Point<T> const& center, long double radians) {
        for (auto& point : points_) {
            point.rotate(center, radians);
        }
    }

    void move(Point<T> const& offset) {
        for (auto& point : points_) {
            point += offset;
        }
    }

    friend std::istream& operator>>(std::istream& is, Polygon& polygon) {
        for (auto& point : polygon.points_) {
            is >> point;
        }
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os,
                                     Polygon const& polygon) {
        for (auto const& point : polygon.points_) {
            os << point << '\n';
        }
        return os;
    }

private:
    std::vector<Point<T>> points_;
};

/*========== Predicates ==========*/

// counter-clockwise test for three points:
//   +1  -> counter-clockwise (left turn)
//   -1  -> clockwise (right turn)
//    0  -> collinear
template <typename T>
int32_t ccw(Point<T> const& a, Point<T> const& b, Point<T> const& c) {
    wide_t<T> const signed_area_2x =
        as<wide_t<T>>(b.x - a.x) * as<wide_t<T>>(c.y - a.y) -
        as<wide_t<T>>(b.y - a.y) * as<wide_t<T>>(c.x - a.x);
    if (signed_area_2x > wide_t<T>{0}) {
        return 1;
    }
    if (signed_area_2x < wide_t<T>{0}) {
        return -1;
    }
    return 0;
}

// Whether two direction vectors are parallel (have the same slope).
template <typename T>
bool is_parallel(Point<T> const& a, Point<T> const& b) {
    return as<wide_t<T>>(a.x) * as<wide_t<T>>(b.y) ==
           as<wide_t<T>>(a.y) * as<wide_t<T>>(b.x);
}

// Whether two segments are the same segment (direction-insensitive).
template <typename T>
bool is_same_segment(Line<T> const& a, Line<T> const& b) {
    return (a.start == b.start && a.end == b.end) ||
           (a.start == b.end && a.end == b.start);
}

// Whether point lies on segment. With strict=true, the endpoints are excluded.
template <typename T>
bool is_on_segment(Point<T> const& point, Line<T> const& segment,
                   bool strict = false) {
    Point<T> const direction = segment.end - segment.start;
    Point<T> const offset = point - segment.start;
    if (direction.x == T{0} && direction.y == T{0}) {
        return point == segment.start;
    }
    wide_t<T> const cross_product = direction.cross(offset);
    if (wide_abs<T>(cross_product) > as<wide_t<T>>(EPSILON)) {
        return false;
    }
    wide_t<T> const projection = direction.dot(offset);
    wide_t<T> const length_squared = direction.dot(direction);
    if (strict) {
        return projection > wide_t<T>{0} && projection < length_squared;
    }
    return projection >= wide_t<T>{0} && projection <= length_squared;
}

// Linear interpolation on a segment: given x, returns y on the line.
// For a vertical segment, returns the segment's start y.
template <typename T>
long double interpolate_y(Line<T> const& segment, long double x) {
    if (segment.start.x == segment.end.x) {
        return as<long double>(segment.start.y);
    }
    long double const slope =
        (as<long double>(segment.end.y) - as<long double>(segment.start.y)) /
        (as<long double>(segment.end.x) - as<long double>(segment.start.x));
    return slope * (x - as<long double>(segment.start.x)) +
           as<long double>(segment.start.y);
}

// Given y, returns x on the line. For a horizontal segment, returns start x.
template <typename T>
long double interpolate_x(Line<T> const& segment, long double y) {
    if (segment.start.y == segment.end.y) {
        return as<long double>(segment.start.x);
    }
    long double const inverse_slope =
        (as<long double>(segment.end.x) - as<long double>(segment.start.x)) /
        (as<long double>(segment.end.y) - as<long double>(segment.start.y));
    return inverse_slope * (y - as<long double>(segment.start.y)) +
           as<long double>(segment.start.x);
}

/*========== Line Intersection ==========*/

// Classification of two segments' relationship.
// Base type uint8_t kept so callers can pack into a bitmask:
//     uint16_t mask = (1u << INTERSECT) | (1u << TOUCH_AT_MIDDLE);
enum LineIntersect : uint8_t {
    NO_INTERSECT          = 0,
    PARALLEL              = 1,
    SAME_LINE             = 2,
    COLLINEAR_DISJOINT    = 3,
    COLLINEAR_OVERLAPPING = 4,
    TOUCH_AT_END          = 5,
    TOUCH_AT_MIDDLE       = 6,
    INTERSECT             = 7,
};

namespace detail {

// Project the four endpoints of two collinear segments onto the segments'
// shared axis, returning [a.start, a.end, b.start, b.end] sorted within each
// pair so that a.start <= a.end and b.start <= b.end.
template <typename T>
std::array<T, 4> project_collinear_endpoints(Line<T> const& a,
                                              Line<T> const& b) {
    bool const vertical = (a.start.x == a.end.x);
    std::array<T, 4> projected = vertical
        ? std::array<T, 4>{a.start.y, a.end.y, b.start.y, b.end.y}
        : std::array<T, 4>{a.start.x, a.end.x, b.start.x, b.end.x};
    if (projected[0] > projected[1]) {
        std::swap(projected[0], projected[1]);
    }
    if (projected[2] > projected[3]) {
        std::swap(projected[2], projected[3]);
    }
    return projected;
}

}  // namespace detail

// Classify the relationship between two segments.
template <typename T>
LineIntersect line_intersect(Line<T> const& a, Line<T> const& b) {
    if (is_same_segment(a, b)) {
        return SAME_LINE;
    }

    Point<T> const slope_a = a.end - a.start;
    Point<T> const slope_b = b.end - b.start;

    if (is_parallel(slope_a, slope_b)) {
        // Two parallel segments: either collinear or strictly parallel.
        // Use ccw against a third point to disambiguate.
        if (ccw(a.start, a.end, b.start) != 0) {
            return PARALLEL;
        }
        // Collinear. Project to common axis and inspect interval overlap.
        std::array<T, 4> const projected =
            detail::project_collinear_endpoints(a, b);
        T const a_low  = projected[0];
        T const a_high = projected[1];
        T const b_low  = projected[2];
        T const b_high = projected[3];
        bool const b_overlaps_a_interior =
            (b_low > a_low && b_low < a_high) ||
            (b_high > a_low && b_high < a_high);
        bool const a_overlaps_b_interior =
            (a_low > b_low && a_low < b_high) ||
            (a_high > b_low && a_high < b_high);
        if (b_overlaps_a_interior || a_overlaps_b_interior) {
            return COLLINEAR_OVERLAPPING;
        }
        bool const endpoint_shared =
            a_low == b_low || a_low == b_high ||
            a_high == b_low || a_high == b_high;
        if (endpoint_shared) {
            return TOUCH_AT_END;
        }
        return COLLINEAR_DISJOINT;
    }

    // Different slopes: parameter solve for intersection of the supporting
    // lines, then check whether the parameters land inside [0, 1] for both.
    bool const shares_endpoint =
        a.start == b.start || a.start == b.end ||
        a.end   == b.start || a.end   == b.end;
    if (shares_endpoint) {
        return TOUCH_AT_END;
    }

    using Wide = wide_t<T>;
    Wide determinant =
        as<Wide>(slope_a.x) * as<Wide>(slope_b.y) -
        as<Wide>(slope_a.y) * as<Wide>(slope_b.x);
    Wide const delta_x = as<Wide>(b.start.x - a.start.x);
    Wide const delta_y = as<Wide>(b.start.y - a.start.y);
    Wide t_numerator = delta_x * as<Wide>(slope_b.y) -
                       delta_y * as<Wide>(slope_b.x);
    Wide u_numerator = delta_x * as<Wide>(slope_a.y) -
                       delta_y * as<Wide>(slope_a.x);

    // Normalize sign so that comparisons against [0, determinant] are valid.
    if (determinant < Wide{0}) {
        determinant = -determinant;
        t_numerator = -t_numerator;
        u_numerator = -u_numerator;
    }

    bool const t_strictly_inside =
        t_numerator > Wide{0} && t_numerator < determinant;
    bool const u_strictly_inside =
        u_numerator > Wide{0} && u_numerator < determinant;
    if (t_strictly_inside && u_strictly_inside) {
        return INTERSECT;
    }

    bool const t_at_endpoint =
        t_numerator == Wide{0} || t_numerator == determinant;
    bool const u_at_endpoint =
        u_numerator == Wide{0} || u_numerator == determinant;
    bool const t_within = t_numerator >= Wide{0} && t_numerator <= determinant;
    bool const u_within = u_numerator >= Wide{0} && u_numerator <= determinant;
    bool const touches_midpoint =
        (t_at_endpoint && u_within) || (u_at_endpoint && t_within);
    if (touches_midpoint) {
        return TOUCH_AT_MIDDLE;
    }

    return NO_INTERSECT;
}

/*========== Segment Sweep ==========*/

namespace detail {

template <typename T>
struct SweepEvent {
    enum Kind : uint8_t { LEFT = 0, VERTICAL = 1, RIGHT = 2 };
    T x_coordinate{0};
    Kind kind{LEFT};
    std::size_t segment_index{0};

    SweepEvent() = delete;
    SweepEvent(T x_value, Kind kind_value, std::size_t index)
        : x_coordinate(x_value), kind(kind_value), segment_index(index) {}

    bool operator<(SweepEvent const& rhs) const {
        if (x_coordinate != rhs.x_coordinate) {
            return x_coordinate < rhs.x_coordinate;
        }
        if (kind != rhs.kind) {
            return kind < rhs.kind;
        }
        return segment_index < rhs.segment_index;
    }
};

// Order active segments by their y at the current sweep x. When y ties, fall
// back to index so std::set treats them as distinct entries. The transparent
// overloads allow lower_bound/upper_bound to take a long double y directly,
// which the vertical-event range query relies on.
template <typename T>
struct CompareByY {
    using is_transparent = void;

    std::vector<Line<T>> const& segments;
    long double const& current_sweep_x;

    CompareByY() = delete;
    CompareByY(std::vector<Line<T>> const& segments_ref,
               long double const& sweep_x_ref)
        : segments(segments_ref), current_sweep_x(sweep_x_ref) {}

    long double y_at(std::size_t index) const {
        return interpolate_y(segments[index], current_sweep_x);
    }

    // For two non-vertical segments sharing y at the current sweep x, decide
    // their order at sweep_x + epsilon by comparing slopes. Verticals never
    // enter the active set, so segments here always have x_start != x_end and
    // dx normalized to positive yields a real slope. Uses wide_t for exact
    // comparison on integral T.
    bool slope_less(std::size_t a, std::size_t b) const {
        using W = wide_t<T>;
        Line<T> const& line_a = segments[a];
        Line<T> const& line_b = segments[b];
        W dy_a = static_cast<W>(line_a.end.y) - static_cast<W>(line_a.start.y);
        W dx_a = static_cast<W>(line_a.end.x) - static_cast<W>(line_a.start.x);
        W dy_b = static_cast<W>(line_b.end.y) - static_cast<W>(line_b.start.y);
        W dx_b = static_cast<W>(line_b.end.x) - static_cast<W>(line_b.start.x);
        if (dx_a < W{0}) {
            dy_a = -dy_a;
            dx_a = -dx_a;
        }
        if (dx_b < W{0}) {
            dy_b = -dy_b;
            dx_b = -dx_b;
        }
        return dy_a * dx_b < dy_b * dx_a;
    }

    bool operator()(std::size_t a, std::size_t b) const {
        long double const y_a = y_at(a);
        long double const y_b = y_at(b);
        if (y_a != y_b) {
            return y_a < y_b;
        }
        if (slope_less(a, b)) {
            return true;
        }
        if (slope_less(b, a)) {
            return false;
        }
        return a < b;
    }
    bool operator()(std::size_t a, long double y_value) const {
        return y_at(a) < y_value;
    }
    bool operator()(long double y_value, std::size_t b) const {
        return y_value < y_at(b);
    }
};

// Shared Bentley–Ottmann sweep implementation. The should_compare predicate
// decides whether a pair of indices is allowed to count as a hit; this lets
// callers skip same-group comparisons without changing the sweep itself.
template <typename T, typename ShouldCompare>
bool any_segments_intersect_impl(std::vector<Line<T>> const& segments,
                                  ShouldCompare const& should_compare,
                                  uint16_t hit_mask) {
    auto is_hit = [&](std::size_t a, std::size_t b) {
        if (!should_compare(a, b)) {
            return false;
        }
        return (hit_mask & (1u << line_intersect(segments[a], segments[b]))) !=
               0u;
    };

    // Pre-pass for vertical-vs-vertical overlaps at identical x. The main
    // sweep never inserts verticals into the active set, so the only way to
    // detect them touching another vertical is up front. Sort verticals by
    // (x, y_min); within each x-bucket, sort by y_min and run an adjacency
    // scan: if seg[i].y_max >= seg[i+1].y_min the two y-ranges overlap and
    // is_hit handles the classification. Total cost O(V log V).
    {
        struct VerticalEntry {
            T x_value;
            T y_min;
            T y_max;
            std::size_t segment_index;
        };
        std::vector<VerticalEntry> verticals;
        for (std::size_t index = 0; index < segments.size(); ++index) {
            Line<T> const& segment = segments[index];
            if (segment.start.x == segment.end.x) {
                T const lo = std::min(segment.start.y, segment.end.y);
                T const hi = std::max(segment.start.y, segment.end.y);
                verticals.push_back({segment.start.x, lo, hi, index});
            }
        }
        std::sort(verticals.begin(), verticals.end(),
                  [](VerticalEntry const& a, VerticalEntry const& b) {
                      if (a.x_value != b.x_value) {
                          return a.x_value < b.x_value;
                      }
                      return a.y_min < b.y_min;
                  });
        for (std::size_t cursor = 1; cursor < verticals.size(); ++cursor) {
            VerticalEntry const& prev = verticals[cursor - 1];
            VerticalEntry const& curr = verticals[cursor];
            if (prev.x_value != curr.x_value) {
                continue;
            }
            if (prev.y_max < curr.y_min) {
                continue;
            }
            if (is_hit(prev.segment_index, curr.segment_index)) {
                return true;
            }
        }
    }

    std::size_t const segment_count = segments.size();
    std::vector<SweepEvent<T>> events;
    events.reserve(2 * segment_count);
    for (std::size_t index = 0; index < segment_count; ++index) {
        T const x_start = segments[index].start.x;
        T const x_end = segments[index].end.x;
        if (x_start == x_end) {
            events.emplace_back(x_start, SweepEvent<T>::VERTICAL, index);
        } else if (x_start < x_end) {
            events.emplace_back(x_start, SweepEvent<T>::LEFT, index);
            events.emplace_back(x_end, SweepEvent<T>::RIGHT, index);
        } else {
            events.emplace_back(x_end, SweepEvent<T>::LEFT, index);
            events.emplace_back(x_start, SweepEvent<T>::RIGHT, index);
        }
    }
    std::sort(events.begin(), events.end());

    long double current_sweep_x = 0.0L;
    CompareByY<T> compare_by_y(segments, current_sweep_x);
    using ActiveSet = std::set<std::size_t, CompareByY<T>>;
    ActiveSet active_segments(compare_by_y);

    // Iterator handles cached at LEFT-event insertion so that RIGHT-event
    // erase never calls find(); the comparator's tie-break ordering shifts
    // between insert and erase moments and a find() based on the live
    // comparator can miss the node. Verticals never enter the set, so their
    // slot stays at end().
    std::vector<typename ActiveSet::iterator> handles(segment_count,
                                                       active_segments.end());

    for (auto const& event : events) {
        std::size_t const event_index = event.segment_index;
        long double const event_x = as<long double>(event.x_coordinate);
        current_sweep_x = event_x;

        if (event.kind == SweepEvent<T>::LEFT) {
            auto const [it, inserted] = active_segments.insert(event_index);
            if (!inserted) {
                continue;
            }
            handles[event_index] = it;
            auto const next_it = std::next(it);
            if (next_it != active_segments.end() &&
                is_hit(*next_it, event_index)) {
                return true;
            }
            if (it != active_segments.begin()) {
                auto const prev_it = std::prev(it);
                if (is_hit(*prev_it, event_index)) {
                    return true;
                }
            }
        } else if (event.kind == SweepEvent<T>::VERTICAL) {
            Line<T> const& vertical_segment = segments[event_index];
            T const y_lo = std::min(vertical_segment.start.y,
                                    vertical_segment.end.y);
            T const y_hi = std::max(vertical_segment.start.y,
                                    vertical_segment.end.y);
            long double const y_lo_ld = as<long double>(y_lo);
            long double const y_hi_ld = as<long double>(y_hi);

            auto const lo_it = active_segments.lower_bound(y_lo_ld);
            for (auto it = lo_it; it != active_segments.end(); ++it) {
                long double const candidate_y = compare_by_y.y_at(*it);
                if (candidate_y > y_hi_ld) {
                    break;
                }
                if (is_hit(event_index, *it)) {
                    return true;
                }
            }
        } else {
            auto const it = handles[event_index];
            if (it == active_segments.end()) {
                continue;
            }
            auto const next_it = std::next(it);
            if (it != active_segments.begin() &&
                next_it != active_segments.end()) {
                auto const prev_it = std::prev(it);
                if (is_hit(*next_it, *prev_it)) {
                    return true;
                }
            }
            active_segments.erase(it);
            handles[event_index] = active_segments.end();
        }
    }
    return false;
}

}  // namespace detail

// Default hit mask for any_segments_intersect: counts "real" overlap kinds
// while excluding NO_INTERSECT, PARALLEL, COLLINEAR_DISJOINT, and
// TOUCH_AT_END (so adjacent polygon edges sharing a vertex don't trigger).
constexpr uint16_t HIT_MASK_DEFAULT =
    (1u << SAME_LINE) | (1u << COLLINEAR_OVERLAPPING) |
    (1u << TOUCH_AT_MIDDLE) | (1u << INTERSECT);

// Returns true as soon as any pair of segments produces a line_intersect
// classification that hit_mask considers a hit. O((n + k) log n) where k is
// pairs reported (bounded above by O(n^2) but typically much smaller).
template <typename T>
bool any_segments_intersect(std::vector<Line<T>> const& segments,
                             uint16_t hit_mask = HIT_MASK_DEFAULT) {
    return detail::any_segments_intersect_impl(
        segments,
        [](std::size_t, std::size_t) { return true; },
        hit_mask);
}

// Same as any_segments_intersect, but pairs of segments sharing a group_id
// are skipped. Useful for polygon-vs-polygon checks where you only care
// about cross-group hits (segments from different polygons).
template <typename T>
bool any_segments_intersect_grouped(std::vector<Line<T>> const& segments,
                                     std::vector<int32_t> const& group_ids,
                                     uint16_t hit_mask = HIT_MASK_DEFAULT) {
    if (segments.size() != group_ids.size()) {
        throw std::invalid_argument(
            "any_segments_intersect_grouped: segments and group_ids size mismatch");
    }
    return detail::any_segments_intersect_impl(
        segments,
        [&group_ids](std::size_t a, std::size_t b) {
            return group_ids[a] != group_ids[b];
        },
        hit_mask);
}

/*========== Polygon Algorithms ==========*/

// Signed 2x area via the shoelace formula. Sign indicates orientation:
//   positive -> counter-clockwise vertex order
//   negative -> clockwise vertex order
// Returns 2x the actual area to stay exact for integer T.
template <typename T>
wide_t<T> polygon_signed_area_2x(Polygon<T> const& polygon) {
    using Wide = wide_t<T>;
    Wide sum{0};
    std::size_t const vertex_count = polygon.size();
    for (std::size_t i = 0; i < vertex_count; ++i) {
        std::size_t const j = (i + 1) % vertex_count;
        sum = sum + as<Wide>(polygon[i].x) * as<Wide>(polygon[j].y) -
              as<Wide>(polygon[j].x) * as<Wide>(polygon[i].y);
    }
    return sum;
}

// Absolute 2x area. Caller divides by 2 (or uses doubled value directly).
template <typename T>
wide_t<T> polygon_area_2x(Polygon<T> const& polygon) {
    return wide_abs<T>(polygon_signed_area_2x(polygon));
}

// Whether a query point lies inside the polygon via upward ray casting.
// With strict=true (default), points exactly on the boundary return false.
// With strict=false, boundary points count as inside.
template <typename T>
bool point_in_polygon(Polygon<T> const& polygon, Point<T> const& query,
                      bool strict = true) {
    std::size_t const vertex_count = polygon.size();
    int32_t crossings = 0;
    for (std::size_t i = 0; i < vertex_count; ++i) {
        Line<T> const edge{polygon[i], polygon[(i + 1) % vertex_count]};
        if (is_on_segment(query, edge, false)) {
            return !strict;
        }
        bool const crosses_vertical_ray =
            (edge.start.x > query.x) != (edge.end.x > query.x);
        if (crosses_vertical_ray) {
            long double const y_at_query_x =
                interpolate_y(edge, as<long double>(query.x));
            if (y_at_query_x > as<long double>(query.y)) {
                ++crossings;
            }
        }
    }
    return (crossings & 1) != 0;
}

// Graham scan convex hull. Returns vertices in counter-clockwise order with
// no three consecutive collinear vertices. Throws if fewer than 3 points.
template <typename T>
Polygon<T> convex_hull(std::vector<Point<T>> points) {
    if (points.size() < 3) {
        throw std::invalid_argument(
            "convex_hull requires at least 3 points.");
    }

    // Pivot: bottom-most, then left-most.
    auto pivot_it = std::min_element(
        points.begin(), points.end(),
        [](Point<T> const& a, Point<T> const& b) {
            if (a.y != b.y) {
                return a.y < b.y;
            }
            return a.x < b.x;
        });
    std::iter_swap(points.begin(), pivot_it);
    Point<T> const pivot = points.front();

    // Sort remaining points by polar angle around pivot using a CCW
    // comparator (exact for integer T, no atan2 required).
    std::sort(
        points.begin() + 1, points.end(),
        [&pivot](Point<T> const& a, Point<T> const& b) {
            int32_t const turn = ccw(pivot, a, b);
            if (turn != 0) {
                return turn > 0;
            }
            // Collinear with pivot: the closer one comes first.
            Point<T> const offset_a = a - pivot;
            Point<T> const offset_b = b - pivot;
            return offset_a.dot(offset_a) < offset_b.dot(offset_b);
        });

    std::vector<Point<T>> hull;
    hull.reserve(points.size());
    for (auto const& point : points) {
        while (hull.size() >= 2 &&
               ccw(hull[hull.size() - 2], hull.back(), point) <= 0) {
            hull.pop_back();
        }
        hull.push_back(point);
    }
    if (hull.size() > 1 && hull.back() == hull.front()) {
        hull.pop_back();
    }
    return Polygon<T>(std::move(hull));
}

/*========== Polygon Intersection ==========*/

enum PolygonIntersect : uint8_t {
    NO_OVERLAP      = 0,
    POINT_TOUCH     = 1,
    LINE_TOUCH      = 2,
    PARTIAL_OVERLAP = 3,
    FULL_OVERLAP    = 4,
};

// Classify the relationship of two polygons using a grouped sweep over the
// combined edge set, then containment checks for the no-cross case.
//
// Complexity:
//   typical case (polygons cross) -> O((n + m) log(n + m))
//   worst case (no crossings)     -> O((n + m) log(n + m) + (n + m) * n)
template <typename T>
PolygonIntersect polygon_intersect(Polygon<T> const& a, Polygon<T> const& b) {
    std::vector<Line<T>> combined_edges;
    std::vector<int32_t> group_ids;
    auto edges_a = a.edges();
    auto edges_b = b.edges();
    combined_edges.reserve(edges_a.size() + edges_b.size());
    group_ids.reserve(edges_a.size() + edges_b.size());
    for (auto const& edge : edges_a) {
        combined_edges.push_back(edge);
        group_ids.push_back(0);
    }
    for (auto const& edge : edges_b) {
        combined_edges.push_back(edge);
        group_ids.push_back(1);
    }

    // Strong intersection: only a proper crossing in segment interiors
    // implies polygon interior overlap. COLLINEAR_OVERLAPPING and SAME_LINE
    // are 1D boundary contact, not 2D interior overlap; they go into the
    // weak mask below.
    constexpr uint16_t strong_mask = (1u << INTERSECT);
    if (any_segments_intersect_grouped(combined_edges, group_ids,
                                        strong_mask)) {
        return PARTIAL_OVERLAP;
    }

    // Weak touch: boundary contact only.
    constexpr uint16_t weak_mask =
        (1u << SAME_LINE) | (1u << COLLINEAR_OVERLAPPING) |
        (1u << TOUCH_AT_END) | (1u << TOUCH_AT_MIDDLE);
    bool const has_edge_touch = any_segments_intersect_grouped(
        combined_edges, group_ids, weak_mask);

    // No proper crossings, so if any vertex of one polygon is strictly
    // inside the other, the whole polygon is inside (no edge crosses out).
    // Iterate every vertex because the first vertex may happen to lie on a
    // shared boundary; we need at least one strictly-interior witness.
    std::size_t const n_a = a.size();
    std::size_t const n_b = b.size();
    for (std::size_t i = 0; i < n_b; ++i) {
        if (point_in_polygon(a, b[i], true)) {
            return FULL_OVERLAP;
        }
    }
    for (std::size_t i = 0; i < n_a; ++i) {
        if (point_in_polygon(b, a[i], true)) {
            return FULL_OVERLAP;
        }
    }

    if (has_edge_touch) {
        return LINE_TOUCH;
    }

    // Fall back to per-vertex boundary check: catches the rare case where a
    // vertex of one polygon lies on the boundary of the other but the
    // edges themselves did not register a touch (e.g. an isolated shared
    // vertex with no adjacent edge interaction picked up by the sweep).
    for (std::size_t i = 0; i < n_a; ++i) {
        if (point_in_polygon(b, a[i], false)) {
            return POINT_TOUCH;
        }
    }
    for (std::size_t i = 0; i < n_b; ++i) {
        if (point_in_polygon(a, b[i], false)) {
            return POINT_TOUCH;
        }
    }
    return NO_OVERLAP;
}

/*========== Segment / Polygon Boundary Utilities ==========*/

// Length of the 1D portion shared by two segments. Returns 0 when the
// segments do not overlap in a 1D sense (not collinear, or collinear but
// disjoint, or touching only at a single point). Result is in physical
// distance units (sqrt of squared length).
template <typename T>
long double segment_overlap_length(Line<T> const& a, Line<T> const& b) {
    LineIntersect const classification = line_intersect(a, b);
    if (classification == SAME_LINE) {
        Point<T> const direction = a.end - a.start;
        return std::sqrt(as<long double>(direction.dot(direction)));
    }
    if (classification != COLLINEAR_OVERLAPPING) {
        return 0.0L;
    }

    std::array<T, 4> const projected =
        detail::project_collinear_endpoints(a, b);
    T const a_low = projected[0];
    T const a_high = projected[1];
    T const b_low = projected[2];
    T const b_high = projected[3];

    T const overlap_low = std::max(a_low, b_low);
    T const overlap_high = std::min(a_high, b_high);
    if (overlap_low >= overlap_high) {
        return 0.0L;
    }

    Point<T> const direction = a.end - a.start;
    long double const direction_length =
        std::sqrt(as<long double>(direction.dot(direction)));

    // The projection axis is x for non-vertical segments and y for vertical.
    // The 1D overlap converts to physical length by scaling with the
    // segment's full-length-to-projected-extent ratio.
    bool const vertical = (a.start.x == a.end.x);
    long double const projected_extent =
        vertical ? std::abs(as<long double>(direction.y))
                 : std::abs(as<long double>(direction.x));
    if (projected_extent == 0.0L) {
        return 0.0L;
    }
    return as<long double>(overlap_high - overlap_low) *
           (direction_length / projected_extent);
}

// Sum of overlap lengths over all edge pairs of two polygons. This is the
// length of their shared boundary when they touch.
template <typename T>
long double common_boundary_length(Polygon<T> const& a, Polygon<T> const& b) {
    auto const edges_a = a.edges();
    auto const edges_b = b.edges();
    long double total = 0.0L;
    for (auto const& edge_a : edges_a) {
        for (auto const& edge_b : edges_b) {
            total += segment_overlap_length(edge_a, edge_b);
        }
    }
    return total;
}

// Proper intersection point of two segments. Returns std::nullopt when the
// segments do not produce a single well-defined crossing point (no
// intersection, parallel, collinear overlap, or shared-line). Endpoint and
// T-junction touches return the touch point.
template <typename T>
std::optional<Point<long double>> segment_intersection_point(
    Line<T> const& a, Line<T> const& b) {
    LineIntersect const classification = line_intersect(a, b);
    if (classification == NO_INTERSECT || classification == PARALLEL ||
        classification == COLLINEAR_DISJOINT ||
        classification == COLLINEAR_OVERLAPPING ||
        classification == SAME_LINE) {
        return std::nullopt;
    }

    // INTERSECT, TOUCH_AT_END, or TOUCH_AT_MIDDLE: parametric solve on a.
    using Wide = wide_t<T>;
    Point<T> const slope_a = a.end - a.start;
    Point<T> const slope_b = b.end - b.start;
    Wide const determinant =
        as<Wide>(slope_a.x) * as<Wide>(slope_b.y) -
        as<Wide>(slope_a.y) * as<Wide>(slope_b.x);
    if (determinant == Wide{0}) {
        return std::nullopt;
    }
    Wide const delta_x = as<Wide>(b.start.x - a.start.x);
    Wide const delta_y = as<Wide>(b.start.y - a.start.y);
    Wide const t_numerator =
        delta_x * as<Wide>(slope_b.y) - delta_y * as<Wide>(slope_b.x);

    long double const t_param =
        as<long double>(t_numerator) / as<long double>(determinant);
    long double const x =
        as<long double>(a.start.x) + t_param * as<long double>(slope_a.x);
    long double const y =
        as<long double>(a.start.y) + t_param * as<long double>(slope_a.y);
    return Point<long double>{x, y};
}

/*========== Polygon Orientation ==========*/

enum PolygonOrientation : uint8_t {
    DEGENERATE        = 0,
    COUNTER_CLOCKWISE = 1,
    CLOCKWISE         = 2,
};

template <typename T>
PolygonOrientation polygon_orientation(Polygon<T> const& poly) {
    wide_t<T> const signed_2x = polygon_signed_area_2x(poly);
    if (signed_2x > wide_t<T>{0}) {
        return COUNTER_CLOCKWISE;
    }
    if (signed_2x < wide_t<T>{0}) {
        return CLOCKWISE;
    }
    return DEGENERATE;
}

// Returns a new polygon with vertex order reversed (CW <-> CCW).
template <typename T>
Polygon<T> reverse_orientation(Polygon<T> const& poly) {
    std::vector<Point<T>> reversed;
    std::size_t const vertex_count = poly.size();
    reversed.reserve(vertex_count);
    for (std::size_t i = vertex_count; i-- > 0;) {
        reversed.push_back(poly[i]);
    }
    return Polygon<T>(std::move(reversed));
}

// True when polygon has no self-intersecting edges (under the default hit
// mask, which already excludes adjacent-edge endpoint touches).
template <typename T>
bool is_simple_polygon(Polygon<T> const& poly) {
    return !any_segments_intersect(poly.edges());
}

}  // namespace geometry
