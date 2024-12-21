#pragma once

#include <memory>
#include "line_action.hpp"

namespace rln {

class BoltAttackAction : public LineAction {
public:
    BoltAttackAction(Game* game,
                     std::shared_ptr<Entity> entity,
                     Point init,
                     Point target,
                     int range,
                     int damage);

    void on_hit(Point pos) override;

private:
    int damage_;
};

}  // namespace rln
