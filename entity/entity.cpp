#include "entity.hpp"
#include <algorithm>
#include <memory>
#include <utility>
#include "action.hpp"
#include "energy.hpp"
#include "event.hpp"
#include "faction.hpp"
#include "game.hpp"
#include "passability.hpp"
#include "point.hpp"
#include "stage.hpp"

namespace rln {

Entity::Entity(Passability passability,
               int view_distance,
               std::string faction,
               int max_hp,
               int damage,
               int speed)
    : energy_(),
      passability_(passability),
      fov_(view_distance),
      faction_(std::move(faction)),
      max_hp_(max_hp),
      hp_(max_hp_),
      damage_(damage),
      speed_(speed),
      position_({0, 0}) {}

void Entity::init(Point pos) {
    position(pos);
}

int Entity::id() const {
    return id_;
}

json Entity::serialize() {
    auto pos = position();
    json data = {{"type", "entity"},
                 {"identifier", identifier()},
                 {"energy", energy_.amount()},
                 // {"passability", passability} // TODO
                 {"faction", faction_.string()},
                 {"max_hp", max_health()},
                 {"hp", health()},
                 {"damage", damage()},
                 {"speed", speed()},
                 {"position", std::array<int, 2>{pos.x, pos.y}},
                 {"id", id()}};
    return data;
}

void Entity::id(int id) {
    id_ = id;
}

Energy& Entity::energy() {
    return energy_;
}

Passability Entity::passability() const {
    return passability_;
}

Fov& Entity::fov() {
    return fov_;
}

Faction& Entity::faction() {
    return faction_;
}

int Entity::max_health() const {
    return max_hp_;
}

void Entity::max_health(int amount) {
    max_hp_ = amount;
}

int Entity::health() const {
    return hp_;
}

void Entity::increase_health(int amount) {
    hp_ = std::clamp(hp_ + amount, 0, max_health());
}

void Entity::decrease_health(int amount) {
    hp_ = std::clamp(hp_ - amount, 0, max_health());
}

void Entity::health(int amount) {
    hp_ = amount;
}

bool Entity::alive() const {
    return hp_ > 0;
}

int Entity::damage() const {
    return damage_;
}

int Entity::speed() const {
    return speed_;
}

Point Entity::position() const {
    return position_;
}

void Entity::position(Point point) {
    position_ = point;
}

void Entity::move(Point point, Game* game) {
    const auto pos = position();
    if (point == pos) {
        return;
    }
    on_change_position(game, pos, point);
    game->stage()->move_entity(pos, point);
    position_ = point;
}

bool Entity::take_damage(std::shared_ptr<Action> action,
                         int damage,
                         std::shared_ptr<Entity> source) {
    if (on_take_damage(action, damage, source) && alive()) {
        react_to_damage(action, damage, source);
        return false;
    }
    action->add_event(
        Event(Event::EventType::DIE, shared_from_this(), position()));
    on_death(action, source);
    return true;
}

void Entity::end_turn(std::shared_ptr<Action> action) {
    energy_.spend();
    if (alive()) {
        on_end_turn(action);
    }
}

bool Entity::needs_input() const {
    return false;
}

}  // namespace rln
