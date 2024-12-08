#include "undead.hpp"
#include <string>
#include <utility>
#include "action.hpp"
#include "stage.hpp"

namespace rln {

Undead::Undead(std::string undead_type,
               float stats_multiplier,
               std::string race,
               Attack attack,
               std::vector<std::shared_ptr<Move>> moves,
               int damage,
               int vision,
               int hearing,
               int tracking,
               int experience_reward,
               Passability passability,
               std::string faction,
               int max_hp,
               int speed)
    : Mob(std::move(race),
          std::move(attack),
          std::move(moves),
          damage * stats_multiplier,
          vision,
          hearing,
          tracking,
          experience_reward,
          passability,
          std::move(faction),
          max_hp * stats_multiplier,
          speed),
      undead_type_(std::move(undead_type)) {}

void Undead::on_death(std::shared_ptr<Action> action, std::shared_ptr<Entity>) {
    action->game()->stage()->remove_entity(shared_from_this());
}

std::string Undead::undead_type() const {
    return undead_type_;
}

}  // namespace rln
