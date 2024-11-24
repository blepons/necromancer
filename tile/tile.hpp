#pragma once

#include "passability.hpp"
#include "tile_type.hpp"

namespace rln {

class Tile {
public:
    // ctor

    TileType*& type();

    TileType* const& type() const;

    bool transparent() const { return type_->transparent(); }

    bool visible() const { return visible_; }

    void visible(bool is_visible) { visible_ = is_visible; }

    bool explored() const { return explored_; }

    bool try_explore(bool force) {
        if (!explored_ && (visible_ || force)) {
            explored_ = true;
            return true;
        }
        return false;
    }

    bool walkable() const { return type_->walkable(); }

    bool traversable() const { return type_->traversable(); }

    bool can_enter(Passability passability) const {
        return type_->can_enter(passability);
    }

    bool can_operate() const;

private:
    TileType* type_;
    bool visible_;
    bool explored_;
};

}  // namespace rln
