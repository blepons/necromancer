#pragma once

#include <SFML/Graphics.hpp>
#include <cstddef>
#include <string>
#include <unordered_map>
#include "game.hpp"
#include "ui_drawer.hpp"

namespace rln {

class Renderer {
public:
    Renderer(Game* game);

    void load_textures();

    void render();

    sf::RenderWindow& window() { return window_; }

protected:
    Game* game() { return game_; }

    UIDrawer& ui_drawer() { return ui_drawer_; }

    void load_texture(const std::string& identifier);

    void draw_ui();

    static constexpr std::size_t map_vertical_offset = 5;

    static constexpr std::size_t map_horizontal_offset = 0;

private:
    Game* game_;
    sf::RenderWindow window_;
    std::unordered_map<std::string, sf::Texture> textures_;
    static constexpr int tile_size = 32;

    UIDrawer ui_drawer_;
};

}  // namespace rln
