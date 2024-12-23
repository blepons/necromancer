#pragma once

#include <memory>
#include <string>
#include "entity_action.hpp"

namespace rln {

using json = nlohmann::json;

class PolymorphAction : public EntityAction {
public:
    PolymorphAction(Game* game,
                    Point pos,
                    std::shared_ptr<Entity> entity,
                    std::string new_undead_type);

    ActionResult perform() override;

private:
    std::string new_undead_type_;
};

}  // namespace rln
