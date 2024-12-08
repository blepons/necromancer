#pragma once

#include <memory>
#include "entity_action.hpp"

namespace rln {

class DesiccationAction : public EntityAction {
public:
    DesiccationAction(Game* game,
                      Point pos,
                      std::shared_ptr<Hero> hero,
                      int range,
                      int stat_increment);

    ActionResult perform() override;

private:
    int range_;
    int stat_increment_;
};

}  // namespace rln
