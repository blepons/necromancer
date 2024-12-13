#include "input_handler.hpp"
#include <SFML/Graphics.hpp>
#include "direction.hpp"
#include "hero.hpp"

namespace rln {

InputHandler::InputHandler(Game* game, sf::RenderWindow& window)
    : game_(game), window_(window) {}

void InputHandler::handle_input() {
    sf::Event event;
    if (!game_->hero()->alive()) {
        window().close();
    }
    while (window().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window().close();
        }
        if (event.type == sf::Event::KeyPressed) {
            Direction dir = Direction::none();
            switch (event.key.code) {
                case sf::Keyboard::W:
                    dir = Direction::north();
                    break;
                case sf::Keyboard::S:
                    dir = Direction::south();
                    break;
                case sf::Keyboard::A:
                    dir = Direction::west();
                    break;
                case sf::Keyboard::D:
                    dir = Direction::east();
                    break;
                case sf::Keyboard::Escape:
                    window().close();
                    break;
                default:
                    break;
            }
            if (dir != Direction::none()) {
                game_->hero()->walk(game_, dir);
            }
        }
    }
}

}  // namespace rln
