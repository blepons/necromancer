#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "game.hpp"

namespace rln {

class InputHandler {
public:
    InputHandler(Game* game, sf::RenderWindow& window);

    void handle_input();

protected:
    sf::RenderWindow& window() { return window_; }

private:
    Game* game_;
    sf::RenderWindow& window_;
};

}  // namespace rln
