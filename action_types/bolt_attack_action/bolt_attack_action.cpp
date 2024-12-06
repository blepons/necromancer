#include "bolt_attack_action.hpp"
#include "stage.hpp"

namespace rln {

BoltAttackAction::BoltAttackAction(Game* game,
                                   Point init,
                                   Point target,
                                   int range,
                                   int damage)
    : LineAction(game, init, target, range), damage_(damage) {}

void BoltAttackAction::on_hit(Point pos) {
    if (game()->stage()->occupied(pos)) {
        auto entity = game()->stage()->entity_at(pos);
        entity->take_damage(shared_from_this(), damage_, nullptr);
    }
}

}  // namespace rln
