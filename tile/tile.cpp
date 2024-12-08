#include "tile.hpp"
#include <memory>
#include <string>
#include <utility>
#include "null_action.hpp"

namespace rln {

Tile::Tile(std::string identifier, Passability passability, bool transparent)
    : identifier_(std::move(identifier)),
      passability_(passability),
      transparent_(transparent) {}

Passability Tile::passability() const {
    return passability_;
}

bool Tile::transparent() const {
    return transparent_;
}

bool Tile::can_enter(Passability passability) const {
    return passability.overlaps(passability_);
}

bool Tile::walkable() const {
    return passability_.overlaps(Passability::walk());
}

bool Tile::traversable() const {
    return passability_.overlaps(Passability::door_or_walk());
}

bool Tile::can_operate() const {
    return false;
}

std::shared_ptr<Action> Tile::on_operate(Game*,
                                         std::shared_ptr<Entity>,
                                         Point) const {
    // TODO: decide if it should:
    //           1. throw
    //           2. return NullAction
    //           3. return nullptr (further check needed)
    return std::make_shared<NullAction>();
}

std::shared_ptr<Action> Tile::on_turn(Game*, Point) const {
    // TODO: decide if it should:
    //           1. return NullAction
    //           2. return nullptr (further check needed)
    return nullptr;
}

std::string Tile::identifier() const {
    return identifier_;
}

}  // namespace rln
