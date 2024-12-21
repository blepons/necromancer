#pragma once

#include <memory>
#include <string>
#include "entity_action.hpp"

namespace rln {

class NecromancyAction : public EntityAction {
public:
    NecromancyAction(Game* game,
                     Point pos,
                     std::shared_ptr<Hero> hero,
                     int range,
                     const std::string& undead_type);

    ActionResult perform() override;

private:
    std::string undead_type_;
    int range_;
};

}  // namespace rln
