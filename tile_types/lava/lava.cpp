#include "lava.hpp"
#include <memory>
#include "lava_burn_action.hpp"

namespace rln {

Lava::Lava() : Tile("lava", Passability::walk(), true) {}

std::shared_ptr<Action> Lava::on_turn(Game* game, Point position) const {
    return std::make_shared<LavaBurnAction>(game, position);
}

}  // namespace rln
