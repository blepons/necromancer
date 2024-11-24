#pragma once

#include <vector>
#include "point.hpp"

class Direction : public Point {
public:
    using Point::Point;

    static Direction none() { return Direction(0, 0); }

    static Direction north() { return Direction(0, 1); }

    static Direction south() { return Direction(0, -1); }

    static Direction west() { return Direction(-1, 0); }

    static Direction east() { return Direction(1, 0); }

    static Direction northwest() { return Direction(-1, 1); }

    static Direction northeast() { return Direction(1, 1); }

    static Direction southwest() { return Direction(-1, -1); }

    static Direction southeast() { return Direction(1, -1); }

    static std::vector<Direction> all() {
        return {north(), northeast(), east(), southeast(),
                south(), southwest(), west(), northwest()};
    }
};
