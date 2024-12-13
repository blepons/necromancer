#include "renderer.hpp"
#include <memory>
#include <string>
#include "game.hpp"
#include "stage.hpp"
#include "ui_drawer.hpp"

namespace rln {

Renderer::Renderer(Game* game)
    : game_(game),
      window_(sf::VideoMode(800, 800), "Game Window"),
      ui_drawer_(window_) {
    load_textures();
}

void Renderer::load_textures() {
    // TODO: load textures by looking at directory contents
    // static constexpr std::string closed_door = "closed_door";
    // static constexpr std::string open_door = "open_door";
    // static constexpr std::string brick_wall = "brick_wall";
    // static constexpr std::string lava = "lava";
    // static constexpr std::string stone_floor = "stone_floor";

    static constexpr std::string wall = "wall";
    static constexpr std::string floor = "floor";
    static constexpr std::string lava = "lava";
    static constexpr std::string hero = "hero";

    // load_texture(closed_door);
    // load_texture(open_door);
    // load_texture(brick_wall);
    // load_texture(lava);
    // load_texture(stone_floor);

    load_texture(hero);
    load_texture(floor);
    load_texture(wall);
    load_texture(lava);
}

void Renderer::load_texture(const std::string& identifier) {
    sf::Texture texture;
    if (texture.loadFromFile("textures/" + identifier + ".png")) {
        textures_[identifier] = texture;
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
                tile_sprite.setTexture(textures_[tile.identifier()]);
                tile_sprite.setPosition(pos_with_offsets);
                window().draw(tile_sprite);

                if (entity) {
                    sf::Sprite entitySprite;
                    entitySprite.setTexture(textures_[entity->identifier()]);
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
