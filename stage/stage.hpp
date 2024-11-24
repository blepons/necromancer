#pragma once

#include <vector>
#include "entity.hpp"
#include "matrix.hpp"
#include "passability.hpp"
#include "tile.hpp"

namespace rln {

class Game;
class Fov;

class Stage {
public:
    Tile& operator[](Point position);

    const Tile& operator[](Point position) const;

    Tile& tile_at(Point position);

    const Tile& tile_at(Point position) const;

    Entity* entity_at(Point position);

    const Entity* entity_at(Point position) const;

    bool occupied(Point position) const;

    bool visible(Entity* entity, Point position) const;

    bool targetable(Point from, Point to) const;

    bool targetable(Entity* entity, Point position)
        const;  // can_see() that returns false if position is blocked by
                // another entity

    bool visible_to_hero(Entity* entity) const;

    void add_entity(Entity* entity);

    void move_entity(Point from, Point to);

    void remove_entity(Entity* entity);

    void explore(Point position, bool force);

    void update_fov();

    void fov_needs_update();

    bool can_occupy(Point position, Passability passability) const;

    bool at_bounds(Point position) const;

private:
    Game* game;
    std::vector<Entity*> entities;
    Fov* fov;
    bpns::matrix<Tile> tiles;
    bpns::matrix<Entity*> entities_grid;

    void set_entity_no_check(Entity* entity, Point position);
};

}  // namespace rln
