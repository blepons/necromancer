#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
namespace geom {}

struct Point {
    Point(int x, int y) : x(x), y(y) {}

    int x;
    int y;

    static unsigned chebyshev(Point start, Point end) {
        return std::max(std::abs(end.x - start.x), std::abs(end.y - start.y));
    }

    static unsigned chebyshev(int x, int y) {
        return std::max(std::abs(x), std::abs(y));
    }

    static unsigned manhattan(Point start, Point end) {
        return std::abs(end.x - start.x) + std::abs(end.y - start.y);
    }

    static unsigned manhattan(int x, int y) {
        return std::abs(x) + std::abs(y);
    }

    static unsigned euclidean_ceil(Point start, Point end) {
        const int x_offset = end.x - start.x;
        const int y_offset = end.y - start.y;
        return static_cast<unsigned>(
            std::ceil(std::sqrt(x_offset * x_offset + y_offset * y_offset)));
    }

    static unsigned euclidean_ceil(int x, int y) {
        return static_cast<unsigned>(std::ceil(std::sqrt(x * x + y * y)));
    }
};

inline auto operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

namespace std {

template <>
struct hash<Point> {
    std::size_t operator()(const Point& point) const {
        std::size_t seed = 0;
        seed ^= hash<int>{}(point.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hash<int>{}(point.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

}  // namespace std
