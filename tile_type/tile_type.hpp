#pragma once

#include <memory>
#include <string>
#include "passability.hpp"
#include "point.hpp"

namespace rln {

class Action;

class TileType {
public:
    TileType(std::string identifier, Passability passability);

    virtual ~TileType() = default;

    Passability passability() const;

    // TODO: decide if flag should be stored instead
    virtual bool transparent() const;

    bool can_enter(Passability passability) const;

    bool walkable() const;

    bool traversable() const;

    virtual bool can_operate() const;

    virtual std::unique_ptr<Action> on_operate(Point pos) const;

    std::string identifier() const;

private:
    std::string identifier_;
    Passability passability_;
};

}  // namespace rln
