#pragma once

#include <memory>
#include "action.hpp"

namespace rln {

class Entity;

class EntityAction : public Action {
public:
    EntityAction(Game* game, Point pos, std::shared_ptr<Entity> entity);

    std::shared_ptr<Entity> entity();

protected:
    std::shared_ptr<Entity> entity_;
};

}  // namespace rln
