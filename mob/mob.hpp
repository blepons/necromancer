#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include "attack.hpp"
#include "entity.hpp"

namespace rln {

class MobState;
class Move;

// TODO
class Mob : public Entity {
public:
    // TODO: ctor

    void use_move(Move* move);

    bool can_use_move(Move* move) const;

    virtual int experience() const;

    std::shared_ptr<Action> action(Game* game) override;

    void wake_up();

    int vision() const;

    int tracking() const;

protected:
    void change_state(MobState* new_state);

protected:
    std::vector<Move*> moves_;
    Attack attack_;
    int vision_;
    int tracking_;
    std::unordered_map<Move*, int> cooldowns_;
    MobState* state_;
};

}  // namespace rln
