#pragma once

#include <SFML/Graphics.hpp>
#include <cstddef>
#include <filesystem>
#include <optional>
#include <string>
#include <unordered_map>
#include "direction.hpp"
#include "game.hpp"
#include "ui_drawer.hpp"

namespace rln {

class Renderer {
public:
    Renderer(Game* game, const std::string& textures_path);

    void load_textures(const std::string& textures_path);

    void render();

    sf::RenderWindow& window() { return window_; }

    std::optional<Point> cursor() const { return cursor_; }

    bool cursor_exists() const { return cursor_.has_value(); }

    void create_cursor();

    void move_cursor(Direction dir);

    void remove_cursor();

protected:
    Game* game() { return game_; }

    UIDrawer& ui_drawer() { return ui_drawer_; }

    void load_texture(const std::filesystem::path& identifier);

    void draw_ui();

    void highlight_selected_tile();

    static constexpr std::size_t map_vertical_offset = 5;

    static constexpr std::size_t map_horizontal_offset = 0;

private:
    Game* game_;
    sf::RenderWindow window_;
    std::unordered_map<std::string, sf::Texture> textures_;
    static constexpr int tile_size = 32;

    std::optional<Point> cursor_;

    UIDrawer ui_drawer_;
};

}  // namespace rln
