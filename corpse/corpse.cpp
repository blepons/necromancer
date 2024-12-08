#include "corpse.hpp"
#include <memory>
#include <utility>
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
    : Entity(Passability::door_or_walk(), Faction::non_entity, corpse_hp, 0, 0),
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
