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

namespace rln {

WalkAction::WalkAction(Game* game,
                       Point pos,
                       std::shared_ptr<Entity> entity,
                       Direction direction)
    : EntityAction(game, pos, entity), direction_(direction) {}

ActionResult WalkAction::perform() {
    if (direction_ == Direction::none()) {
        return ActionResult::alternate(
            std::make_shared<RestAction>(game_, pos_, entity_));
    }

    auto new_pos = Point(pos_.x + direction_.x, pos_.y + direction_.y);
    auto target = game()->stage()->entity_at(new_pos);
    if (target != nullptr && target->id() != entity()->id()) {
        return ActionResult::alternate(
            std::make_shared<AttackAction>(entity(), target, game(), pos()));
    }

    auto tile = game()->stage()->tile_at(new_pos);
    if (tile.can_operate() && tile.can_enter(entity()->passability())) {
        return ActionResult::alternate(
            tile.on_operate(game(), entity(), new_pos));
    }

    if (!game()->stage()->can_occupy(new_pos, entity()->passability())) {
        if (auto hero = std::dynamic_pointer_cast<Hero>(entity());
            hero != nullptr) {
            hero->explore(new_pos, true);
        }
        return ActionResult::succeed();
    }

    move_entity(entity(), new_pos);
    return ActionResult::succeed();
}

}  // namespace rln
