#pragma once

#include "line_action.hpp"

namespace rln {

class BoltAttackAction : public LineAction {
public:
    BoltAttackAction(Game* game,
                     Point init,
                     Point target,
                     int range,
                     int damage);

    void on_hit(Point pos) override;

private:
    int damage_;
};

}  // namespace rln
