#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include "entity_action.hpp"

using json = nlohmann::json;

namespace rln {

class SpawnAction : public EntityAction {
public:
    SpawnAction(Game* game,
                Point pos,
                std::shared_ptr<Entity> entity,
                const json& data);

    ActionResult perform() override;

private:
    json data_;
};

}  // namespace rln
