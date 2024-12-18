#include "renderer.hpp"
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include "game.hpp"
#include "stage.hpp"
#include "ui_drawer.hpp"

namespace rln {

Renderer::Renderer(Game* game, const std::string& textures_path)
    : game_(game),
      window_(sf::VideoMode(800, 800), "Game Window"),
      ui_drawer_(window_) {
    load_textures(textures_path);
}

void Renderer::load_textures(const std::string& textures_path) {
    namespace fs = std::filesystem;
    static constexpr std::string_view extension = ".png";

    fs::path dir_path(textures_path);
    for (auto& file : fs::directory_iterator(dir_path)) {
        if ((file.is_regular_file() || file.is_symlink()) &&
            file.path().extension() == extension) {
            load_texture(file);
        }
    }
}

void Renderer::load_texture(const std::filesystem::path& file) {
    sf::Texture texture;
    if (texture.loadFromFile(file)) {
        textures_[file.stem()] = texture;
    }
}

void Renderer::draw_ui() {
    ui_drawer().update_stats(game());
    ui_drawer().draw(window());
}

void Renderer::render() {
    window().clear();

    Stage* stage = game()->stage();
    const auto& fov = game()->hero_fov();

    for (int x = 0; x < stage->bound_x(); ++x) {
        for (int y = 0; y < stage->bound_y(); ++y) {
            Point pos = {x, y};
            if (fov.visible({x, y})) {
                sf::Vector2f pos_with_offsets(
                    y * tile_size + map_horizontal_offset,
                    x * tile_size + UIDrawer::character_size +
                        map_vertical_offset);
                Tile& tile = stage->tile_at({x, y});
                std::shared_ptr<Entity> entity = stage->entity_at(pos);

                sf::Sprite tile_sprite;
                tile_sprite.setTexture(textures_.at(tile.identifier()));
                tile_sprite.setPosition(pos_with_offsets);
                window().draw(tile_sprite);

                if (entity) {
                    sf::Sprite entitySprite;
                    entitySprite.setTexture(textures_.at(entity->identifier()));
                    entitySprite.setPosition(pos_with_offsets);
                    window().draw(entitySprite);
                }
            }
        }
    }

    draw_ui();

    window().display();
}

}  // namespace rln
