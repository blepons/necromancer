#include "ui_drawer.hpp"
#include <array>
#include <iterator>
#include <numeric>
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
    std::string hp = "hp: " + std::to_string(game->hero()->health());
    std::string mp = "mana: " + std::to_string(game->hero()->mana());
    std::string energy =
        "energy: " + std::to_string(game->hero()->energy().amount());
    std::string lvl = "lvl: " + std::to_string(game->hero()->level());

    std::array stats = {hp, mp, energy, lvl};

    auto result =
        std::accumulate(std::begin(stats), std::end(stats), std::string(),
                        [](std::string&& ss, const std::string& s) {
                            return ss.empty() ? s : ss + "  " + s;
                        });
    text_.setString(result);
}

}  // namespace rln
