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
         Passability passability,
         std::string faction,
         int max_hp,
         int speed)
    : Entity(passability, std::move(faction), max_hp, speed),
      race_(std::move(race)),
      attack_(std::move(attack)),
      vision_(vision),
      hearing_(hearing),
      tracking_(tracking) {
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

}  // namespace rln
