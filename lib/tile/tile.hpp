#pragma once

#include <memory>
#include <string>
#include "passability.hpp"
#include "point.hpp"

namespace rln {

class Action;
class Entity;
class Game;

class Tile {
public:
    Tile(std::string identifier, Passability passability, bool transparent);

    virtual ~Tile() = default;

    Passability passability() const;

    bool transparent() const;

    bool can_enter(Passability passability) const;

    bool walkable() const;

    bool traversable() const;

    virtual bool can_operate() const;

    virtual std::shared_ptr<Action> on_operate(Game* game,
                                               std::shared_ptr<Entity> entity,
                                               Point pos) const;

    virtual std::shared_ptr<Action> on_turn(Game* game, Point position) const;

    std::string identifier() const;

private:
    std::string identifier_;
    Passability passability_;
    bool transparent_;
};

}  // namespace rln
