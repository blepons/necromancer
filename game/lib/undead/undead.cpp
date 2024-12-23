#include "undead.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>
#include <utility>
#include "action.hpp"
#include "disappear_action.hpp"

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
               std::string_view faction,
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
          faction,
          max_hp * stats_multiplier,
          speed),
      undead_type_(std::move(undead_type)) {}

std::string Undead::supertype() const {
    return "undead";
}

std::string Undead::identifier() const {
    return undead_type();
}

json Undead::serialize() {
    json data = Mob::serialize();
    json undead_data = {{"undead_type", undead_type()}};
    data.update(undead_data);
    return data;
}

void Undead::on_death(std::shared_ptr<Action> action, std::shared_ptr<Entity>) {
    action->add_action(std::make_shared<DisappearAction>(
        action->game(), position(), shared_from_this()));
}

std::string Undead::undead_type() const {
    return undead_type_;
}

}  // namespace rln
