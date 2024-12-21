#pragma once

#include <memory>
#include "point.hpp"

namespace rln {

class Entity;

struct Event {
public:
    enum class EventType {
        DIE,
        HEAL,
        HIT,
        POLYMORPH,
        SPAWN,
    };

    Event(EventType type, std::shared_ptr<Entity> entity, Point pos)
        : type(type), entity(entity), pos(pos) {}

    EventType type;
    std::shared_ptr<Entity> entity;
    Point pos;
};

}  // namespace rln
