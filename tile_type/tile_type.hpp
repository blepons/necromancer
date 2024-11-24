#pragma once

#include <string>
#include "passability.hpp"
#include "point.hpp"

namespace rln {

class Action;

class TileType {
public:
    // TODO: ctor

    virtual ~TileType() = default;

    Passability passability() const;

    virtual bool transparent() const;

    bool can_enter(Passability passability) const {
        return passability.overlaps(passability_);
    }

    bool walkable() const { return passability_.overlaps(Passability::walk()); }

    bool traversable() const {
        return passability_.overlaps(Passability::door_or_walk());
    }

    virtual bool can_operate() const;

    virtual Action* on_operate(Point pos);

    std::string identifier() const;

private:
    std::string identifier_;
    Passability passability_;
};

}  // namespace rln
