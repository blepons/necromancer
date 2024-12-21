#include "wander_state.hpp"
#include <memory>
#include <optional>
#include <ranges>
#include <string>
#include <vector>
#include "mob.hpp"
#include "move.hpp"
#include "pathfinder.hpp"
#include "stage.hpp"
#include "walk_action.hpp"

namespace rln {

WanderState::WanderState(std::shared_ptr<Mob> mob) : MobState(mob) {}

std::string WanderState::identifier() const {
    return "wander";
}

std::shared_ptr<Action> WanderState::action(Game* game) {
    auto available_moves =
        mob()->moves() | std::views::keys |
        std::views::filter([game, mob = mob()](const auto& move) {
            return mob->can_use_move(move) && move->should_use(game, mob);
        });
    if (!std::ranges::empty(available_moves)) {
        auto moves = std::vector<std::shared_ptr<Move>>(available_moves.begin(),
                                                        available_moves.end());
        return moves[game->random(0, moves.size())]->action(game, mob());
    }
    auto dir = melee_dir(game);
    if (dir == Direction::none()) {
        dir = towards_enemy(game);
    }
    return std::make_shared<WalkAction>(game, mob()->position(), mob(), dir);
}

Direction WanderState::melee_dir(Game* game) {
    auto fltr = game->stage()->entities() |
                std::views::filter(
                    [mob = mob(), stage = game->stage()](const auto& entity) {
                        return mob->id() != entity->id() &&
                               mob->faction().hostile(entity->faction()) &&
                               stage->visible(mob, entity->position());
                    }) |
                std::views::transform(
                    [](const auto& entity) { return entity->position(); });
    auto targets = std::vector<Point>(fltr.begin(), fltr.end());
    std::optional<Direction> dir = std::nullopt;
    if (!targets.empty()) {
        dir = Pathfinder(mob(), mob()->position(), targets, game->stage())
                  .search();
    }
    return dir != std::nullopt ? *dir : Direction::none();
}

Direction WanderState::towards_enemy(Game* game) {
    auto dirs = Direction::all() |
                std::views::filter([stage = game->stage(), mob = mob(),
                                    pos = mob()->position()](const auto& dir) {
                    auto neighbor = Point(pos.x + dir.x, pos.y + dir.y);
                    return stage->occupied(neighbor) &&
                           mob->faction().hostile(
                               stage->entity_at(neighbor)->faction());
                });
    if (!std::ranges::empty(dirs)) {
        auto directions = std::vector<Direction>(dirs.begin(), dirs.end());
        return directions[game->random(0, directions.size())];
    }
    return Direction::none();
}

}  // namespace rln
