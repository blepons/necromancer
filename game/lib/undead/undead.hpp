#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include "mob.hpp"

namespace rln {

class Undead : public Mob {
public:
    Undead(std::string undead_type,
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
           int speed);

    std::string supertype() const override;

    std::string identifier() const override;

    json serialize() override;

    void on_death(std::shared_ptr<Action> action,
                  std::shared_ptr<Entity> source) override;

    std::string undead_type() const;

    void undead_type(std::string new_type);

protected:
    std::string undead_type_;
};

}  // namespace rln
