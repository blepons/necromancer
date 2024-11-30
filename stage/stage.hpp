#pragma once

#include <memory>
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

    void tile_at(Point position, std::unique_ptr<Tile> tile);

    std::shared_ptr<Entity> entity_at(Point position);

    std::shared_ptr<const Entity> entity_at(Point position) const;

    bool occupied(Point position) const;

    bool visible(std::shared_ptr<Entity> entity, Point position) const;

    bool targetable(Point from, Point to) const;

    bool targetable(std::shared_ptr<Entity> entity, Point position) const;

    bool visible_to_hero(std::shared_ptr<Entity> entity) const;

    void add_entity(std::shared_ptr<Entity> entity);

    void move_entity(Point from, Point to);

    void remove_entity(std::shared_ptr<Entity> entity);

    void explore(Point position, bool force);

    void update_fov();

    void fov_needs_update();

    bool can_occupy(Point position, Passability passability) const;

    bool at_bounds(Point position) const;

private:
    Game* game;
    std::vector<std::shared_ptr<Entity>> entities;
    Fov* fov;
    bpns::matrix<std::unique_ptr<Tile>> tiles;
    bpns::matrix<std::shared_ptr<Entity>> entities_grid;

    void set_entity_no_check(std::shared_ptr<Entity> entity, Point position);
};

}  // namespace rln
