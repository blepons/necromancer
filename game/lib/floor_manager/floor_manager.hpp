#pragma once

namespace rln {

class Stage;
class Game;

class FloorManager {
public:
    virtual ~FloorManager() = default;

    virtual Stage* stage() = 0;

    virtual void load_next_floor(Game* game) = 0;

    virtual void unload_current_floor() = 0;
};

}  // namespace rln
