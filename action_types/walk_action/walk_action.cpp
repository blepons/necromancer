#include "walk_action.hpp"
#include <memory>
#include "action.hpp"
#include "attack_action.hpp"
#include "direction.hpp"
#include "entity_action.hpp"
#include "hero.hpp"
#include "rest_action.hpp"
#include "stage.hpp"
#include "tile.hpp"
#include "tile_type.hpp"

namespace rln {

WalkAction::WalkAction(Game* game,
                       Point pos,
                       Entity* entity,
                       Direction direction)
    : EntityAction(game, pos, entity), direction_(direction) {}

ActionResult WalkAction::perform() {
    if (direction_ == Direction::none()) {
        return ActionResult::alternate(
            std::make_unique<RestAction>(game_, pos_, entity_));
    }

    auto new_pos = Point(pos_.x + direction_.x, pos_.y + direction_.y);
    auto target = game()->stage()->entity_at(new_pos);
    if (target != nullptr && target != entity()) {
        return ActionResult::alternate(
            std::make_unique<AttackAction>(entity(), target, game(), pos()));
    }

    auto tile = game()->stage()->tile_at(new_pos).type();
    if (tile->can_operate() && tile->can_enter(entity()->passability())) {
        return ActionResult::alternate(tile->on_operate(new_pos));
    }

    if (!game()->stage()->can_occupy(new_pos, entity()->passability())) {
        if (auto hero = dynamic_cast<Hero*>(entity()); hero != nullptr) {
            game()->stage()->explore(new_pos, true);
        }
        return ActionResult::fail();
    }

    move_entity(entity(), new_pos);
    return ActionResult::succeed();
}

}  // namespace rln
