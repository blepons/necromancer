#pragma once

#include <SFML/Graphics.hpp>
#include <cstddef>
#include "game.hpp"

namespace rln {

class UIDrawer {
public:
    UIDrawer(const sf::RenderWindow& window);

    void draw(sf::RenderWindow& window);

    void update_stats(Game* game);

    static constexpr std::size_t character_size = 20;

private:
    sf::Font font_;

    // TODO
    sf::Text text_;
};

}  // namespace rln
