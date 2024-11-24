#pragma once

#include <vector>
#include "passability.hpp"

namespace rln {

class Attack;
class Move;

class MobBreed {
protected:
    std::vector<Attack*> attacks_;
    std::vector<Move*> moves_;
    int max_hp_;
    int vision_;  /// max amount of tiles away the mob can see enemy
    int speed_;
    Passability passability_;

public:
    int experience() const /* abstract? */;
};

}  // namespace rln
