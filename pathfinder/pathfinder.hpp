#pragma once

#include <cstddef>
#include <optional>
#include "direction.hpp"
#include "tile.hpp"

namespace rln {

class Mob;
class Stage;

class Pathfinder {
public:
    struct Path {
        Path(Direction start_direction, Point start, int length, int cost);

        Direction start_direction;
        Point pos;
        int length;
        int cost;
    };

    static constexpr int default_cost = 100;
    static constexpr int diagonal_cost = 120;
    // static constexpr int liquid_cost = 200;
    static constexpr int occupied_cost = 400;
    static constexpr int door_cost = 1000;

public:
    Pathfinder(Point start, Point end, Stage* stage);

    std::optional<Direction> search();

    std::size_t priority(const Path& path, Point end) const;

    static int heuristic(Point start, Point end);

    std::optional<int> cost(Point pos, const Tile& tile);

    std::optional<Direction> process(const Path& path);

    std::optional<Direction> reached_goal(const Path& path) const;

    std::optional<Direction> unreachable() const;

private:
    Stage* stage_;
    Point start_;
    Point end_;
    Mob* mob_;
    std::optional<Path> nearest_;
};

}  // namespace rln
