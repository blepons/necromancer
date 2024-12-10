#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include "entity_action.hpp"

namespace rln {

using json = nlohmann::json;

class PolymorphAction : public EntityAction {
public:
    PolymorphAction(Game* game,
                    Point pos,
                    std::shared_ptr<Entity> entity,
                    const json& data);

    ActionResult perform() override;

private:
    std::string kind_;
    json data_;
};

}  // namespace rln
