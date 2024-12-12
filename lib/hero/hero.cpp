#include "hero.hpp"
#include <algorithm>
#include <cmath>
#include <memory>
#include <nlohmann/json.hpp>
#include "action.hpp"
#include "rest_action.hpp"
#include "skill_set.hpp"
#include "stage.hpp"
#include "walk_action.hpp"

namespace rln {

Hero::Hero(int max_mana, SkillSet skills, int max_hp, int damage)
    : Entity(Passability::door_or_walk(),
             20,
             Faction::hero,
             max_hp,
             damage,
             Energy::normal_speed),
      max_mana_(max_mana),
      mana_(max_mana),
      experience_(0),
      skills_(std::move(skills)),
      next_action_() {}

void Hero::init(const json& data) {
    Entity::init(data);
    auto mana__ = data.value("mana", max_mana());
    auto experience__ = data.value("experience", 0);

    mana_ = mana__;
    experience_ = experience__;
}

std::string Hero::identifier() const {
    return "hero";
}

json Hero::serialize() {
    json data = Entity::serialize();
    json hero_data = {{"max_mana", max_mana()},
                      {"mana", mana()},
                      {"experience", experience()},
                      {"skills", skills_.serialize()}};
    data.update(hero_data);
    return data;
}

int Hero::level() const {
    int level = 1;
    while (level < max_lvl && experience_needed_for_lvl[level] <= experience_) {
        ++level;
    }
    return level;
}

void Hero::gain_experience(int amount) {
    auto lvl = level();
    experience_ += amount;
    recalculate_level(lvl);
}

void Hero::recalculate_level(int previous_lvl) {
    auto lvl = level();
    if (lvl - previous_lvl) {
        on_level_up(previous_lvl, lvl);
    }
}

void Hero::on_level_up(int previous_lvl, int new_lvl) {
    auto lvl_diff = new_lvl - previous_lvl;

    max_health(max_health() + hp_increment * lvl_diff);
    max_mana(max_mana() + mp_increment * lvl_diff);
    increase_health(hp_increment * lvl_diff);
    gain_mana(mp_increment * lvl_diff);
}

SkillSet& Hero::skill_set() {
    return skills_;
}

int Hero::mana() const {
    return mana_;
}

int Hero::max_mana() const {
    return max_mana_;
}

void Hero::max_mana(int amount) {
    max_mana_ = amount;
}

void Hero::spend_mana(int amount) {
    if (mana() < amount) {
        // throw?
    }
    mana_ -= amount;
}

void Hero::gain_mana(int amount) {
    mana_ = std::clamp(mana_ + amount, 0, max_mana());
}

int Hero::experience() const {
    return experience_;
}

void Hero::explore(Point pos, bool forced) {
    // TODO: store matrix of explored tiles?
}

void Hero::wait_for_input() {
    next_action_ = nullptr;
}

void Hero::rest(Game* game) {
    next_action(
        std::make_shared<RestAction>(game, position(), shared_from_this()));
}

void Hero::walk(Game* game, Direction dir) {
    next_action(std::make_shared<WalkAction>(game, position(),
                                             shared_from_this(), dir));
}

bool Hero::needs_input() const {
    return next_action_ == nullptr;
}

std::shared_ptr<Action> Hero::action(Game*) {
    auto action = next_action();
    wait_for_input();
    return action;
}

std::shared_ptr<Action> Hero::next_action() {
    return next_action_;
}

void Hero::next_action(std::shared_ptr<Action> action) {
    next_action_ = action;
}

void Hero::attack(std::shared_ptr<Entity> target) {
    // TODO
    target->take_damage(nullptr, damage(), shared_from_this());
}

bool Hero::on_take_damage(std::shared_ptr<Action>,
                          int damage,
                          std::shared_ptr<Entity>) {
    decrease_health(damage);
    return true;
}

void Hero::react_to_damage(std::shared_ptr<Action>,
                           int,
                           std::shared_ptr<Entity>) {}

void Hero::on_death(std::shared_ptr<Action> action, std::shared_ptr<Entity>) {
    action->game()->stage()->remove_entity(shared_from_this());
}

void Hero::on_change_position(Game*, Point, Point to) {
    // TODO: ?
    fov().update(to);
}

void Hero::on_end_turn(std::shared_ptr<Action>) {}

}  // namespace rln
