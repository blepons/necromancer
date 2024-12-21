#include "leave_corpse_action.hpp"
#include <memory>
#include <ranges>
#include "corpse.hpp"
#include "stage.hpp"

namespace rln {

LeaveCorpseAction::LeaveCorpseAction(Game* game,
                                     Point pos,
                                     std::shared_ptr<Mob> mob)
    : EntityAction(game, pos, mob) {}

ActionResult LeaveCorpseAction::perform() {
    auto mob = std::static_pointer_cast<Mob>(entity());
    auto moves = std::views::keys(mob->moves());
    auto corpse = std::make_shared<Corpse>(
        std::min(mob->max_health() / 15, 1), mob->race(), mob->attack(),
        std::vector(moves.begin(), moves.end()), mob->damage(), mob->vision(),
        mob->hearing(), mob->tracking(), mob->passability(), mob->max_health(),
        mob->speed());
    game()->stage()->replace_entity(game(), corpse, pos());
    return ActionResult::succeed();
}

}  // namespace rln
