#include "bolt_attack_action.hpp"
#include <memory>
#include "stage.hpp"

namespace rln {

BoltAttackAction::BoltAttackAction(Game* game,
                                   std::shared_ptr<Entity> entity,
                                   Point init,
                                   Point target,
                                   int range,
                                   int damage)
    : LineAction(game, entity, init, target, range), damage_(damage) {}

void BoltAttackAction::on_hit(Point pos) {
    if (game()->stage()->occupied(pos)) {
        auto target = game()->stage()->entity_at(pos);
        target->take_damage(shared_from_this(), damage_, entity());
    }
}

}  // namespace rln
