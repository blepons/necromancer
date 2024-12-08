#include "stage.hpp"
#include <algorithm>
#include <iterator>
#include <memory>
#include "entity.hpp"
#include "fov.hpp"
#include "game.hpp"
#include "line.hpp"

namespace rln {

Stage::Stage(std::vector<std::shared_ptr<Entity>> entities,
             bpns::matrix<std::shared_ptr<Tile>> tiles,
             Point start_pos)
    : entities_(std::move(entities)),
      entity_index_(0),
      tiles_(std::move(tiles)),
      start_pos_(start_pos) {
    for (const auto& entity : entities_) {
        set_entity_no_check(entity, entity->position());
    }
}

Point Stage::start_pos() const {
    return start_pos_;
}

int Stage::bound_x() const {
    return tiles_.rows();
}

int Stage::bound_y() const {
    return tiles_.columns();
}

Tile& Stage::operator[](Point position) {
    return *tiles_(position.x, position.y);
}

const Tile& Stage::operator[](Point position) const {
    return *tiles_(position.x, position.y);
}

Tile& Stage::tile_at(Point position) {
    return *tiles_.at(position.x, position.y);
}

const Tile& Stage::tile_at(Point position) const {
    return *tiles_.at(position.x, position.y);
}

void Stage::tile_at(Point position, std::shared_ptr<Tile> tile) {
    tiles_(position.x, position.y) = std::move(tile);
}

std::shared_ptr<Entity> Stage::entity_at(Point position) {
    return entities_grid_.at(position.x, position.y);
}

std::shared_ptr<const Entity> Stage::entity_at(Point position) const {
    return entities_grid_.at(position.x, position.y);
}

std::vector<std::shared_ptr<Entity>>& Stage::entities() {
    return entities_;
}

bool Stage::occupied(Point position) const {
    return entity_at(position) != nullptr;
}

bool Stage::visible(Point from, Point to) const {
    for (auto point : geom::Line(from, to)) {
        if (point == to) {
            return true;
        }
        if (!tile_at(point).transparent()) {
            return false;
        }
    }
    std::unreachable();
}

bool Stage::visible(std::shared_ptr<Entity> entity, Point position) const {
    return visible(position, entity->position());
}

bool Stage::targetable(Point from, Point to) const {
    for (auto point : geom::Line(from, to)) {
        if (point == to) {
            return true;
        }
        if (occupied(point)) {
            return false;
        }
        if (!tile_at(point).transparent()) {
            return false;
        }
    }
    std::unreachable();
}

bool Stage::targetable(std::shared_ptr<Entity> entity, Point position) const {
    return targetable(position, entity->position());
}

void Stage::set_entity_no_check(std::shared_ptr<Entity> entity,
                                Point position) {
    entities_grid_.at(position.x, position.y) = entity;
}

void Stage::add_entity(Game* game,
                       std::shared_ptr<Entity> entity,
                       Point position) {
    if (occupied(position)) {
        // throw?
    }
    game->assign_id(entity);
    entity->init(position);
    entity->fov().init(this);
    entities_.push_back(entity);
    entities_grid_(position.x, position.y) = entity;
}

void Stage::replace_entity(Game* game,
                           std::shared_ptr<Entity> entity,
                           Point position) {
    auto old_entity = entity_at(position);
    if (old_entity == nullptr) {
        // throw?
    }
    set_entity_no_check(entity, position);
    game->assign_id(entity);
    entity->init(position);
    entity->fov().init(this);
    auto it = std::ranges::find_if(
        entities_,
        [id = entity->id()](const auto& e) { return e->id() == id; });
    *it = entity;
}

void Stage::move_entity(Point from, Point to) {
    auto entity = entity_at(from);
    if (entity == nullptr) {
        // throw?
    }
    set_entity_no_check(entity, to);
}

void Stage::remove_entity(std::shared_ptr<Entity> entity) {
    auto pos = entity->position();
    auto it = std::find(entities_.begin(), entities_.end(), entity);
    auto index = std::distance(entities_.begin(), it);
    if (entity_index_ > index) {
        --entity_index_;
    }
    entities_.erase(it);
    if (static_cast<unsigned>(entity_index_) >= entities_.size()) {
        entity_index_ = 0;
    }
    entities_grid_.at(pos.x, pos.y) = nullptr;
}

bool Stage::can_occupy(Point position, Passability passability) const {
    return tile_at(position).passability().overlaps(passability);
}

bool Stage::out_of_bounds(Point position) const {
    return position.x >= bound_x() || position.x < 0 ||
           position.y >= bound_y() || position.y < 0;
}

std::shared_ptr<Entity> Stage::current_entity() {
    return entities_[entity_index_];
}

void Stage::increment_entity_index() {
    entity_index_ = (entity_index_ + 1) % entities_.size();
}

}  // namespace rln
