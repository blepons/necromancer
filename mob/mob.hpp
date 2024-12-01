#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "attack.hpp"
#include "entity.hpp"

namespace rln {

class MobState;
class Move;

class Mob : public Entity {
public:
    Mob(std::string race,
        Attack attack,
        std::vector<std::shared_ptr<Move>> moves,
        int vision,
        int hearing,
        int tracking,
        int experience_reward,
        Passability passability,
        std::string faction,
        int max_hp,
        int speed);

    std::shared_ptr<Mob> getptr();

    void init(Point pos) override;

    void use_move(std::shared_ptr<Move> move);

    bool can_use_move(std::shared_ptr<Move> move) const;

    std::shared_ptr<Action> action(Game* game) override;

    int vision() const;

    int hearing() const;

    int tracking() const;

    int experience_reward() const;

    MobState& state();

    void change_state(std::unique_ptr<MobState>&& new_state);

protected:
    std::string race_;
    Attack attack_;
    std::unordered_map<std::shared_ptr<Move>, int> cooldowns_;

    int vision_;
    int hearing_;
    int tracking_;
    int experience_reward_;

    std::unique_ptr<MobState> state_;
};

}  // namespace rln
