#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "game.hpp"

namespace rln {

class Renderer {
public:
    Renderer(Game* game);

    void load_textures();

    void render();

protected:
    Game* game() { return game_; }

    sf::RenderWindow& window() { return window_; }

    void load_texture(const std::string& identifier);

private:
    Game* game_;
    sf::RenderWindow window_;
    std::unordered_map<std::string, sf::Texture> textures_;
    static constexpr int tile_size = 32;
};

}  // namespace rln
