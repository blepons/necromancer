#pragma once

#include <vector>
#include "event.hpp"

namespace rln {

struct TurnResult {
    std::vector<Event> events;
    bool game_changed;

    bool refresh_needed() const { return !events.empty() || game_changed; }
};

}  // namespace rln
