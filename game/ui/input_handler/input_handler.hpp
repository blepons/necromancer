#pragma once

#include <functional>
#include <optional>
#include <string>
#include "game.hpp"
#include "renderer.hpp"

namespace rln {

class InputHandler {
public:
    InputHandler(Game* game, Renderer& renderer);

    void handle_input();

protected:
    Renderer& renderer() { return renderer_; }

    Game* game() { return game_; }

    std::optional<std::string> skill_id() const { return skill_id_; }

    void handle_stage_input();

    void handle_cursor_input();

    bool valid_cursor();

private:
    Game* game_;
    Renderer& renderer_;

    std::function<bool(Game*, Point)> validator_;
    std::optional<std::string> skill_id_;
};

}  // namespace rln
