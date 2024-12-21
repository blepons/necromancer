#include "downward_stairs.hpp"
#include <memory>
#include "game.hpp"
#include "hero.hpp"
#include "next_floor_action.hpp"
#include "stage.hpp"

namespace rln {

DownwardStairs::DownwardStairs()
    : Tile("downward_stairs", Passability::walk(), true) {}

std::shared_ptr<Action> DownwardStairs::on_turn(Game* game,
                                                Point position) const {
    if (game->stage()->entity_at(position)->id() == game->hero()->id()) {
        return std::make_shared<NextFloorAction>(game);
    }
    return nullptr;
}

}  // namespace rln
