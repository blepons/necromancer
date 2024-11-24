#pragma once

#include "point.hpp"

namespace rln {

class Entity;

struct Event {
public:
    enum class EventType {
        DIE,
        HIT,
        POLYMORPH,
        SPAWN,
    };

    Event(EventType type, Entity* entity, Point pos);

    EventType type;
    Entity* entity;
    Point pos;
};

}  // namespace rln
