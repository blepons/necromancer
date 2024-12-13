#include "ui_drawer.hpp"
#include <stdexcept>
#include <string>
#include "hero.hpp"

namespace rln {

UIDrawer::UIDrawer(const sf::RenderWindow& window) {
    if (!font_.loadFromFile("FiraSans-Medium.ttf")) {
        throw std::runtime_error("Couldn't open font file");
    }

    text_.setFont(font_);
    text_.setCharacterSize(character_size);
    text_.setFillColor(sf::Color::White);
    // text_.setPosition(window.getSize().x * 0.02,
    //                   window.getSize().y - text_.getGlobalBounds().height -
    //                       text_.getGlobalBounds().top);
}

void UIDrawer::draw(sf::RenderWindow& window) {
    window.draw(text_);
}

void UIDrawer::update_stats(Game* game) {
    text_.setString("hp: " + std::to_string(game->hero()->health()) +
                    ", mana: " + std::to_string(game->hero()->mana()));
}

}  // namespace rln
