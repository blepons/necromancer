#include "summon_move.hpp"
#include <algorithm>
#include <memory>
#include <ranges>
#include <string>
#include <vector>
#include "do_nothing_action.hpp"
#include "mob.hpp"
#include "spawn_action.hpp"
#include "stage.hpp"

namespace rln {

SummonMove::SummonMove(int cooldown, const json& data)
    : Move(cooldown), data_(data) {}

std::string SummonMove::identifier() const {
    return "summon";
}

json SummonMove::serialize() {
    json data = Move::serialize();
    json summons_data = {{"summons", data_}};
    data.update(summons_data);
    return data;
}

bool SummonMove::should_use(Game* game, std::shared_ptr<Mob> mob) const {
    return std::ranges::any_of(mob->position().neighbors(),
                               [game](const auto neighbor) {
                                   return !game->stage()->occupied(neighbor);
                               });
}

std::shared_ptr<Action> SummonMove::action(Game* game,
                                           std::shared_ptr<Mob> mob) {
    auto& creatures = data_.at("creatures");
    auto summoned_mob_data = creatures[game->random(0, creatures.size())];
    auto filtered_tiles =
        mob->position().neighbors() |
        std::views::filter([game](const auto neighbor) {
            return !game->stage()->occupied(neighbor) &&
                   game->stage()->tile_at(neighbor).transparent();
        });
    auto available_tiles =
        std::vector(filtered_tiles.cbegin(), filtered_tiles.cend());
    if (!available_tiles.empty()) {
        auto chosen_tile =
            available_tiles[game->random(0, available_tiles.size())];
        mob->moves()[shared_from_this()] = cooldown();
        return std::make_shared<SpawnAction>(game, chosen_tile, mob,
                                             summoned_mob_data);
    }
    return std::make_shared<DoNothingAction>(game, mob->position(), mob);
}

}  // namespace rln
