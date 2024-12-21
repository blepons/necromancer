#pragma once

#include <memory>
#include "entity_action.hpp"

namespace rln {

class LineAction : public EntityAction {
public:
    LineAction(Game* game,
               std::shared_ptr<Entity> entity,
               Point init,
               Point target,
               int range);

    ActionResult perform() override;

    virtual void on_hit(Point pos) = 0;

protected:
    Point target_;
    int range_;
};

}  // namespace rln
