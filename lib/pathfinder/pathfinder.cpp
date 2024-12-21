#include "pathfinder.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <optional>
#include <unordered_set>
#include <utility>
#include <vector>
#include "cost_priority_queue.hpp"
#include "direction.hpp"
#include "mob.hpp"
#include "stage.hpp"
#include "tile.hpp"

namespace rln {

Pathfinder::Pathfinder(std::shared_ptr<Mob> mob,
                       Point start,
                       std::vector<Point> ends,
                       Stage* stage)
    : stage_(stage), start_(start), ends_(std::move(ends)), mob_(mob) {}

std::optional<Direction> Pathfinder::search() {
    auto paths = std::vector<rln::cost_priority_queue<Path>>(ends_.size());
    auto explored = std::vector<std::unordered_set<Point>>(ends_.size());

    for (std::size_t i = 0; i < ends_.size(); ++i) {
        auto start_path = Path(Direction::none(), start_, 0, 0);
        paths[i].push({start_path, priority(start_path, ends_[i])});
    }

    while (true) {
        std::optional<Direction> result;
        for (std::size_t i = 0; i < ends_.size(); ++i) {
            if (paths[i].empty()) {
                continue;
            }

            auto path = *paths[i].top();
            paths[i].pop();

            if (path.pos == ends_[i]) {
                return path.start_direction;
            }

            if (explored[i].contains(path.pos)) {
                continue;
            }
            explored[i].insert(path.pos);

            auto result_path = process(path, ends_[i]);
            if (result_path != std::nullopt) {
                return result_path;
            }

            for (auto dir : Direction::all()) {
                auto neighbor = Point(path.pos.x + dir.x, path.pos.y + dir.y);
                if (explored[i].contains(neighbor) ||
                    stage_->out_of_bounds(neighbor)) {
                    continue;
                }
                auto cst = cost(neighbor, stage_->tile_at(neighbor));
                if (cst == std::nullopt) {
                    continue;
                }
                auto new_path =
                    Path(path.start_direction == Direction::none()
                             ? dir
                             : path.start_direction,
                         neighbor, path.length + 1, path.cost + *cst);
                paths[i].push({new_path, priority(new_path, ends_[i])});
            }
        }

        if (result != std::nullopt) {
            return result;
        }

        for (std::size_t i = 0; i < ends_.size(); ++i) {
            if (!nearest_ || heuristic(paths[i].top().value.pos, ends_[i]) <
                                 heuristic(nearest_->pos, ends_[i])) {
                nearest_ = *paths[i].top();
                paths[i].pop();
            }
        }
        return nearest_ ? std::optional<Direction>(nearest_->start_direction)
                        : std::nullopt;
    }
}

std::size_t Pathfinder::priority(const Path& path, Point end) const {
    return path.cost + heuristic(path.pos, end);
}

int Pathfinder::heuristic(Point start, Point end) {
    auto x_offset = std::abs(end.x - start.x);
    auto y_offset = std::abs(end.y - start.y);
    auto diagonal = std::min(x_offset, y_offset);
    auto straight = std::max(x_offset, y_offset) - diagonal;
    return straight * default_cost + diagonal * diagonal_cost;
}

std::optional<int> Pathfinder::cost(Point pos, const Tile& tile) {
    bool is_first_step = Point::chebyshev(start_, pos) == 1;
    if (stage_->entity_at(pos) != nullptr) {
        if (is_first_step) {
            return std::nullopt;
        }
        return occupied_cost;
    }
    if (tile.identifier() == "closed_door") {
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

std::optional<Direction> Pathfinder::process(const Path& path, Point end) {
    if (!nearest_ || heuristic(path.pos, end) < heuristic(nearest_->pos, end)) {
        nearest_ = path;
    }
    if (path.length > mob_->tracking()) {
        return nearest_->start_direction;
    }
    return std::nullopt;
}

}  // namespace rln
