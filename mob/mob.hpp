#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include "entity.hpp"

namespace rln {

class MobState;
class Move;
class Attack;

// class Mob : public Entity {
// public:
//     // ctor: breed, generation, pos????

//     bool can_use_move(Move* move) const;

//     void use_move(Move* move);

// private:
//     MobBreed* breed_;
//     int generation_;                            // = parent.generation + 1
//     std::unordered_map<Move*, int> recharges_;  // 0 -> move can be done
//     MobState* state_;
// };

// V4
class Mob : public Entity {
public:
    // ctor: generation, pos????

    void use_move(Move* move);

    bool can_use_move(Move* move) const;

    virtual int experience() const;

    std::unique_ptr<Action> action(Game* game) override;

    void wake_up();

    int tracking() const;

protected:
    void change_state(MobState* new_state);

protected:
    std::vector<Attack*> attacks_;
    std::vector<Move*> moves_;
    int vision_;  /// max amount of tiles away the mob can see enemy
    int tracking_;
    std::unordered_map<Move*, int> cooldowns_;  // 0 -> move can be done
    MobState* state_;
};

}  // namespace rln
