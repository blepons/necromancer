#include "stage.hpp"
#include "entity.hpp"
#include "fov.hpp"
#include "game.hpp"
#include "hero.hpp"
#include "line.hpp"

namespace rln {

Tile& Stage::operator[](Point position) {
    return tiles(position.x, position.y);
}

const Tile& Stage::operator[](Point position) const {
    return tiles(position.x, position.y);
}

Tile& Stage::tile_at(Point position) {
    return tiles.at(position.x, position.y);
}

const Tile& Stage::tile_at(Point position) const {
    return tiles.at(position.x, position.y);
}

Entity* Stage::entity_at(Point position) {
    return entities_grid.at(position.x, position.y);
}

const Entity* Stage::entity_at(Point position) const {
    return entities_grid.at(position.x, position.y);
}

bool Stage::occupied(Point position) const {
    return entity_at(position) != nullptr;
}

void Stage::set_entity_no_check(Entity* entity, Point position) {
    entities_grid.at(position.x, position.y) = entity;
}

void Stage::add_entity(Entity* entity) {
    auto pos = entity->position();
    if (occupied(pos)) {
        // throw?
    }
    entities.push_back(entity);
    entities_grid(pos.x, pos.y) = entity;
}

void Stage::move_entity(Point from, Point to) {
    auto entity = entity_at(from);
    if (entity == nullptr) {
        // throw?
    }
    set_entity_no_check(entity, to);
}

void Stage::remove_entity(Entity* entity) {
    auto pos = entity->position();

    // do something with entity order that changes after removal

    entities_grid.at(pos.x, pos.y) = nullptr;
}

bool Stage::visible(Entity* entity, Point position) const {
    for (auto point : geom::Line(entity->position(), position)) {
        if (point == position) {
            return true;
        }
        if (!tile_at(point).transparent()) {
            return false;
        }
    }
    std::unreachable();
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

bool Stage::targetable(Entity* entity, Point position) const {
    return targetable(position, entity->position());
}

bool Stage::visible_to_hero(Entity* entity) const {
    return tile_at(entity->position()).visible();
}

void Stage::explore(Point position, bool force) {
    auto tile = tile_at(position);
    tile.try_explore(force);
    //     if (tile.visible()) {
    //         auto entity = entity_at(position);
    //         if (entity != nullptr) {
    //             game->hero()->see_entity(entity);
    //         }
    //     }
    // }
}

void Stage::update_fov() {
    fov->update(game->hero()->position());
}

}  // namespace rln
