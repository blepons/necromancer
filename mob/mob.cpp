#include "mob.hpp"
#include <algorithm>
#include <memory>
#include <ranges>
#include <utility>
#include <vector>
#include "asleep_state.hpp"
#include "change_state_action.hpp"
#include "corpse.hpp"
#include "hero.hpp"
#include "mob_state.hpp"
#include "move.hpp"
#include "stage.hpp"
#include "wander_state.hpp"

namespace rln {

Mob::Mob(std::string race,
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
    : Entity(passability, vision, std::move(faction), max_hp, damage, speed),
      race_(std::move(race)),
      attack_(std::move(attack)),
      vision_(vision),
      hearing_(hearing),
      tracking_(tracking),
      experience_reward_(experience_reward) {
    for (auto& item : moves) {
        cooldowns_[item] = 0;
    }
}

std::shared_ptr<Mob> Mob::getptr() {
    return std::static_pointer_cast<Mob>(shared_from_this());
}

void Mob::init(Point pos) {
    Entity::init(pos);
    state_ = std::make_unique<AsleepState>(getptr());
}

void Mob::use_move(std::shared_ptr<Move> move) {
    cooldowns_.at(move) += move->cooldown();
}

bool Mob::can_use_move(std::shared_ptr<Move> move) {
    return cooldowns_[move] == 0;
}

bool Mob::needs_input() const {
    return false;
}

std::shared_ptr<Action> Mob::action(Game* game) {
    for (auto& [_, cooldown] : cooldowns_) {
        cooldown = std::max(cooldown - 1, 0);
    }
    if (asleep() && entity_nearby(game, hearing())) {
        auto mob = getptr();
        return std::make_shared<ChangeStateAction>(
            game, position(), mob, std::make_unique<WanderState>(mob));
    }
    return state().action(game);
}

void Mob::attack(std::shared_ptr<Entity> target) {
    attack_.perform(getptr(), target);
}

bool Mob::on_take_damage(std::shared_ptr<Action>,
                         int damage,
                         std::shared_ptr<Entity>) {
    decrease_health(damage);
    return true;
}

void Mob::react_to_damage(std::shared_ptr<Action> action,
                          int damage,
                          std::shared_ptr<Entity>) {
    auto mob = getptr();
    auto available_moves =
        cooldowns_ | std::views::filter([mob, damage](const auto& item) {
            return item.first->should_use_on_damage(mob, damage) &&
                   item.second == 0;
        }) |
        std::views::keys;
    auto moves = std::vector<std::shared_ptr<Move>>(available_moves.begin(),
                                                    available_moves.end());
    auto game = action->game();
    action->add_action(moves[game->random(0, moves.size())]->action(game, mob));
}

void Mob::on_death(std::shared_ptr<Action> action,
                   std::shared_ptr<Entity> entity) {
    if (auto hero = std::dynamic_pointer_cast<Hero>(entity); hero != nullptr) {
        hero->gain_experience(experience_reward());
    }
    auto moves = std::views::keys(cooldowns_);
    auto corpse = std::make_shared<Corpse>(
        std::min(max_health() / 15, 1), race(), attack_,
        std::vector(moves.begin(), moves.end()), damage(), vision(), hearing(),
        tracking(), passability(), max_health(), speed());
    action->game()->stage()->replace_entity(action->game(), corpse, position());
}

void Mob::on_change_position(Game*, Point, Point) {}

void Mob::on_end_turn(std::shared_ptr<Action>) {}

std::string Mob::race() const {
    return race_;
}

int Mob::vision() const {
    return vision_;
}

int Mob::hearing() const {
    return hearing_;
}

int Mob::tracking() const {
    return tracking_;
}

int Mob::experience_reward() const {
    return experience_reward_;
}

MobState& Mob::state() {
    return *state_;
}

void Mob::change_state(std::unique_ptr<MobState>&& new_state) {
    state_ = std::move(new_state);
}

bool Mob::asleep() const {
    return dynamic_cast<AsleepState*>(state_.get()) != nullptr;
}

bool Mob::wandering() const {
    return dynamic_cast<WanderState*>(state_.get()) != nullptr;
}

bool Mob::entity_nearby(Game* game, int distance) {
    return std::ranges::any_of(game->stage()->entities(), [&](auto& other) {
        return id() != other->id() &&
               Point::euclidean_ceil(position(), other->position()) <=
                   static_cast<unsigned>(distance) &&
               game->stage()->visible(position(), other->position());
    });
}

}  // namespace rln
