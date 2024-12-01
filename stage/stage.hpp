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
    int bound_x() const;

    int bound_y() const;

    Tile& operator[](Point position);

    const Tile& operator[](Point position) const;

    Tile& tile_at(Point position);

    const Tile& tile_at(Point position) const;

    void tile_at(Point position, std::unique_ptr<Tile> tile);

    std::shared_ptr<Entity> entity_at(Point position);

    std::shared_ptr<const Entity> entity_at(Point position) const;

    std::vector<std::shared_ptr<Entity>>& entities();

    bool occupied(Point position) const;

    bool visible(std::shared_ptr<Entity> entity, Point position) const;

    bool targetable(Point from, Point to) const;

    bool targetable(std::shared_ptr<Entity> entity, Point position) const;

    void add_entity(std::shared_ptr<Entity> entity, Point position);

    void replace_entity(std::shared_ptr<Entity> entity, Point position);

    void move_entity(Point from, Point to);

    void remove_entity(std::shared_ptr<Entity> entity);

    void update_fov();

    void fov_needs_update();

    bool can_occupy(Point position, Passability passability) const;

    bool at_bounds(Point position) const;

private:
    Game* game_;
    std::vector<std::shared_ptr<Entity>> entities_;
    bpns::matrix<std::unique_ptr<Tile>> tiles_;
    bpns::matrix<std::shared_ptr<Entity>> entities_grid_;

    void set_entity_no_check(std::shared_ptr<Entity> entity, Point position);
};

}  // namespace rln
