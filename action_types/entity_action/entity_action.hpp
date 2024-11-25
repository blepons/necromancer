#pragma once

#include "action.hpp"

namespace rln {

class Entity;

class EntityAction : public Action {
public:
    EntityAction(Game* game, Point pos, Entity* entity);

    Entity* entity();

protected:
    Entity* entity_;
};

}  // namespace rln
