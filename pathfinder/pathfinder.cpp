#include "pathfinder.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <optional>
#include <unordered_set>
#include "cost_priority_queue.hpp"
#include "direction.hpp"
#include "mob.hpp"
#include "stage.hpp"
#include "tile.hpp"
#include "tile_type.hpp"

namespace rln {

Pathfinder::Pathfinder(Point start, Point end, Stage* stage)
    : stage_(stage), start_(start), end_(end) {}

std::optional<Direction> Pathfinder::search() {
    auto paths = rln::cost_priority_queue<Path>{};
    auto explored = std::unordered_set<Point>{};
    auto start_path = Path(Direction::none(), start_, 0, 0);
    paths.push({start_path, priority(start_path, end_)});

    while (!paths.empty()) {
        auto path = *paths.top();
        paths.pop();
        if (path.pos == end_) {
            return reached_goal(path);
        }
        if (explored.contains(path.pos)) {
            continue;
        }
        auto result = process(path);
        if (result != std::nullopt) {
            return result;
        }
        for (auto dir : Direction::all()) {
            auto neighbor = Point(path.pos.x + dir.x, path.pos.y + dir.y);
            if (explored.contains(neighbor) || stage_->at_bounds(neighbor)) {
                continue;
            }
            auto cst = cost(neighbor, stage_->tile_at(neighbor));
            if (cst == std::nullopt) {
                continue;
            }
            auto new_path = Path(path.start_direction == Direction::none()
                                     ? dir
                                     : path.start_direction,
                                 neighbor, path.length + 1, path.cost + *cst);
            paths.push({new_path, priority(new_path, end_)});
        }
    }
    return unreachable();
}

std::size_t Pathfinder::priority(const Path& path, Point end) const {
    return path.cost + heuristic(path.pos, end);
}

int Pathfinder::heuristic(Point start, Point end) {
    auto x_offset = std::abs(end.x - start.x);
    auto y_offset = std::abs(end.y - start.y);
    auto diagonal = std::min(x_offset, y_offset);
    auto straight = std::max(x_offset, y_offset);
    return straight * default_cost + diagonal * diagonal_cost;
}

std::optional<int> Pathfinder::cost(Point pos, const Tile& tile) {
    bool is_first_step = Point::chebyshev(start_, pos);
    if (stage_->entity_at(pos) != nullptr) {
        if (is_first_step) {
            return std::nullopt;
        }
        return occupied_cost;
    }
    if (tile.type()->identifier() == "closed_door") {
        if (mob_->passability().overlaps(Passability::door())) {
            return default_cost * 2;
        } else if (is_first_step) {
            return std::nullopt;
        } else {
            return door_cost;
        }
    }
    if (tile.can_enter(mob_->passability())) {
        return default_cost;
    }
    return std::nullopt;
}

std::optional<Direction> Pathfinder::process(const Path& path) {
    if (!nearest_ ||
        heuristic(path.pos, end_) < heuristic(nearest_->pos, end_)) {
        nearest_ = path;
    }
    if (path.length > mob_->tracking()) {
        return nearest_->start_direction;
    }
    return std::nullopt;
}

std::optional<Direction> Pathfinder::reached_goal(const Path& path) const {
    return path.start_direction;
}

std::optional<Direction> Pathfinder::unreachable() const {
    return nearest_ ? std::optional<Direction>(nearest_->start_direction)
                    : std::nullopt;
}

}  // namespace rln
