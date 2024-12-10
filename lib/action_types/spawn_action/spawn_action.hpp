#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include "entity_action.hpp"

namespace rln {

using json = nlohmann::json;

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
