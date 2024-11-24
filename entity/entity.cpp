#include "entity.hpp"
#include <algorithm>
#include "action.hpp"
#include "energy.hpp"
#include "event.hpp"
#include "game.hpp"
#include "passability.hpp"
#include "point.hpp"
#include "stage.hpp"

namespace rln {

Entity::Entity(Passability passability, int max_hp, int speed, Point position)
    : energy_(),
      passability_(passability),
      max_hp_(max_hp),
      hp_(max_hp_),
      speed_(speed),
      position_(position) {}

Passability Entity::passability() const {
    return passability_;
}

int Entity::max_health() const {
    return max_hp_;
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

int Entity::speed() const {
    return speed_;
}

Point Entity::position() const {
    return position_;
}

void Entity::position(Point point, Game* game) {
    const auto pos = position();
    if (point == pos) {
        return;
    }
    on_change_position(game, pos, point);
    game->stage()->move_entity(pos, point);
    position_ = point;
}

bool Entity::take_damage(Action* action, int damage, Entity* source) {
    on_take_damage(action, damage, source);
    if (alive()) {
        return false;
    }
    action->add_event(Event(Event::EventType::DIE, this, position()));
    on_death(action, source);
    return true;
}

void Entity::end_turn(Action* action) {
    energy_.spend();
    if (alive()) {
        on_end_turn(action);
    }
}

bool Entity::needs_input() const {
    return false;
}

}  // namespace rln
