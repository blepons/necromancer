#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include "attack.hpp"
#include "entity.hpp"

namespace rln {

class MobState;
class Move;

class Mob : public Entity {
public:
    // TODO: ctor

    std::shared_ptr<Mob> getptr();

    void init(Point pos) override;

    void use_move(Move* move);

    bool can_use_move(Move* move) const;

    virtual int experience() const;

    std::shared_ptr<Action> action(Game* game) override;

    int vision() const;

    int tracking() const;

    MobState& state();

    void change_state(std::unique_ptr<MobState>&& new_state);

protected:
    std::vector<Move*> moves_;
    Attack attack_;
    int vision_;
    int tracking_;
    std::unordered_map<Move*, int> cooldowns_;
    std::unique_ptr<MobState> state_;
};

}  // namespace rln
