#pragma once

#include <memory>
#include <string>
#include "passability.hpp"
#include "point.hpp"

namespace rln {

class Action;
class Entity;

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

    virtual std::shared_ptr<Action> on_operate(Point pos) const;

    virtual std::shared_ptr<Action> on_turn(
        std::shared_ptr<Entity> entity) const;

    std::string identifier() const;

private:
    std::string identifier_;
    Passability passability_;
    bool transparent_;
};

}  // namespace rln
