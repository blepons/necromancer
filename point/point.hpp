#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdlib>
namespace geom {}

struct Point {
    Point(int x, int y) : x(x), y(y) {}

    int x;
    int y;

    static int chebyshev(Point start, Point end) {
        return std::max(std::abs(end.x - start.x), std::abs(end.y - start.y));
    }

    static int manhattan(Point start, Point end) {
        return std::abs(end.x - start.x) + std::abs(end.y - start.y);
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
