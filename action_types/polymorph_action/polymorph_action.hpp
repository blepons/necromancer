#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include "entity_action.hpp"

using json = nlohmann::json;

namespace rln {

class PolymorphAction : public EntityAction {
public:
    PolymorphAction(Game* game,
                    Point pos,
                    std::shared_ptr<Entity> entity,
                    // std::string_view kind);
                    const json& data);

    ActionResult perform() override;

private:
    std::string kind_;
    json data_;
};

}  // namespace rln
