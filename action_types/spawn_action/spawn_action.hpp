#pragma once

#include "entity_action.hpp"
#include <memory>



// remove when json placeholder is removed
#include <string>

namespace rln {

// TODO: include json library
class json {
public:
    std::string operator[](const std::string&) const;
};

class SpawnAction : public EntityAction {
public:
    SpawnAction(Game* game, Point pos, std::shared_ptr<Entity> entity, const json& data);

    ActionResult perform() override;

private:
    json data_;
};

}
