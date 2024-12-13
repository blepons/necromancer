#include "essence.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include "hero.hpp"
#include "null_action.hpp"
#include "stage.hpp"

namespace rln {

Essence::Essence(int amount)
    : Entity(Passability::walk(), 0, Faction::non_entity, 1, 0, 0),
      amount_(amount) {}

std::string Essence::supertype() const {
    return "essence";
}

std::string Essence::identifier() const {
    return "essence";
}

json Essence::serialize() {
    json data = Entity::serialize();
    json essence_data = {{"essence_amount", amount()}};
    data.update(essence_data);
    return data;
}

std::shared_ptr<Action> Essence::action(Game*) {
    return std::make_shared<NullAction>();
}

void Essence::attack(std::shared_ptr<Entity>) {}

bool Essence::on_take_damage(std::shared_ptr<Action>,
                             int,
                             std::shared_ptr<Entity>) {
    health(0);
    return true;
}

void Essence::react_to_damage(std::shared_ptr<Action>,
                              int,
                              std::shared_ptr<Entity>) {}

void Essence::on_death(std::shared_ptr<Action> action,
                       std::shared_ptr<Entity> entity) {
    if (auto hero = std::dynamic_pointer_cast<Hero>(entity); hero != nullptr) {
        hero->gain_experience(amount());
    }
    action->game()->stage()->remove_entity(shared_from_this());
}

void Essence::on_change_position(Game*, Point, Point) {}

void Essence::on_end_turn(std::shared_ptr<Action>) {}

int Essence::amount() const {
    return amount_;
}

}  // namespace rln
