#include "tile_type.hpp"
#include <memory>
#include <string>
#include <utility>
#include "null_action.hpp"

namespace rln {

TileType::TileType(std::string identifier, Passability passability)
    : identifier_(std::move(identifier)), passability_(passability) {}

Passability TileType::passability() const {
    return passability_;
}

bool TileType::transparent() const {
    return true;
}

bool TileType::can_enter(Passability passability) const {
    return passability.overlaps(passability_);
}

bool TileType::walkable() const {
    return passability_.overlaps(Passability::walk());
}

bool TileType::traversable() const {
    return passability_.overlaps(Passability::door_or_walk());
}

bool TileType::can_operate() const {
    return false;
}

std::unique_ptr<Action> TileType::on_operate(Point) const {
    return std::make_unique<NullAction>();
}

std::string TileType::identifier() const {
    return identifier_;
}

}  // namespace rln
