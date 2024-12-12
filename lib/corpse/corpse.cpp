#include "corpse.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include "move.hpp"
#include "null_action.hpp"
#include "stage.hpp"

namespace rln {

Corpse::Corpse(int corpse_hp,
               std::string dead_mob_type,
               Attack attack,
               std::vector<std::shared_ptr<Move>> moves,
               int damage,
               int vision,
               int hearing,
               int tracking,
               Passability passability,
               int max_hp,
               int speed)
    : Entity(Passability::door_or_walk(),
             0,
             Faction::non_entity,
             corpse_hp,
             0,
             0),
      dead_mob_type_(std::move(dead_mob_type)),
      stats_(std::move(attack),
             std::move(moves),
             damage,
             vision,
             hearing,
             tracking,
             passability,
             max_hp,
             speed) {}

json Corpse::serialize() {
    json data = Entity::serialize();
    json::array_t moves;
    for (const auto& move : stats_.moves) {
        moves.emplace_back(move->serialize());
    }
    json corpse_data = {
        {"race", dead_mob_type_},
        {"attack", stats_.attack.serialize()},
        {"moves", moves},
        {"vision", stats_.vision},
        {"hearing", stats_.hearing},
        {"tracking", stats_.tracking},
        {"passability", "door_or_walk"},  // TODO: remove temporary solution
        {"mob_max_hp", stats_.max_hp},
        {"speed", stats_.speed}};
    data.update(corpse_data);
    return data;
}

std::string Corpse::identifier() const {
    return "corpse";
}

std::shared_ptr<Action> Corpse::action(Game*) {
    return std::make_shared<NullAction>();
}

void Corpse::attack(std::shared_ptr<Entity>) {}

bool Corpse::on_take_damage(std::shared_ptr<Action>,
                            int damage,
                            std::shared_ptr<Entity>) {
    decrease_health(damage);
    return true;
}

void Corpse::react_to_damage(std::shared_ptr<Action>,
                             int,
                             std::shared_ptr<Entity>) {}

void Corpse::on_death(std::shared_ptr<Action> action, std::shared_ptr<Entity>) {
    action->game()->stage()->remove_entity(shared_from_this());
}

void Corpse::on_change_position(Game*, Point, Point) {}

void Corpse::on_end_turn(std::shared_ptr<Action>) {}

std::string Corpse::dead_mob_race() const {
    return dead_mob_type_;
}

const Corpse::DeadMobStats& Corpse::dead_mob_stats() const {
    return stats_;
}

}  // namespace rln
