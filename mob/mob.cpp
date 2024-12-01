#include "mob.hpp"
#include <memory>
#include <utility>
#include "asleep_state.hpp"
#include "mob_state.hpp"
#include "move.hpp"

namespace rln {

Mob::Mob(std::string race,
         Attack attack,
         std::vector<std::shared_ptr<Move>> moves,
         int vision,
         int hearing,
         int tracking,
         int experience_reward,
         Passability passability,
         std::string faction,
         int max_hp,
         int speed)
    : Entity(passability, std::move(faction), max_hp, speed),
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

// TODO: action

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

}  // namespace rln
