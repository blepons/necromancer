#include "input_handler.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include "action_skill.hpp"
#include "corpse.hpp"
#include "direction.hpp"
#include "hero.hpp"
#include "stage.hpp"
#include "targeted_skill.hpp"

namespace rln {

InputHandler::InputHandler(Game* game, Renderer& renderer)
    : game_(game), renderer_(renderer) {}

void InputHandler::handle_input() {
    if (!game_->hero()->alive()) {
        renderer().window().close();
    }
    if (renderer().cursor_exists()) {
        handle_cursor_input();
    } else {
        handle_stage_input();
    }
}

static bool desiccation_validator(Game* game, Point pos) {
    return std::dynamic_pointer_cast<Corpse>(game->stage()->entity_at(pos)) !=
           nullptr;
}

static bool curse_validator(Game* game, Point pos) {
    return game->stage()->occupied(pos);
}

static bool necromancy_validator(Game* game, Point pos) {
    return std::dynamic_pointer_cast<Corpse>(game->stage()->entity_at(pos)) !=
           nullptr;
}

static bool polymorph_validator(Game* game, Point pos) {
    return std::dynamic_pointer_cast<Undead>(game->stage()->entity_at(pos)) !=
           nullptr;
}

void InputHandler::handle_stage_input() {
    sf::Event event;
    while (renderer().window().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            renderer().window().close();
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::W:
                    game_->hero()->walk(game_, Direction::north());
                    break;
                case sf::Keyboard::S:
                    game_->hero()->walk(game_, Direction::south());
                    break;
                case sf::Keyboard::A:
                    game_->hero()->walk(game_, Direction::west());
                    break;
                case sf::Keyboard::D:
                    game_->hero()->walk(game_, Direction::east());
                    break;
                case sf::Keyboard::Num1:
                    skill_id_ = "desiccation";
                    validator_ = desiccation_validator;
                    renderer().create_cursor();
                    break;
                case sf::Keyboard::Num2:
                    skill_id_ = "curse";
                    validator_ = curse_validator;
                    renderer().create_cursor();
                    break;
                case sf::Keyboard::Num3:
                    skill_id_ = "necromancy";
                    validator_ = necromancy_validator;
                    renderer().create_cursor();
                    break;
                case sf::Keyboard::Num4:
                    skill_id_ = "polymorph";
                    validator_ = polymorph_validator;
                    break;
                case sf::Keyboard::Num5: {
                    skill_id_ = "wrath";
                    auto& [skill, level] =
                        game()->hero()->skill_set().get(*skill_id());
                    if (auto action_skill =
                            std::dynamic_pointer_cast<ActionSkill>(skill);
                        action_skill != nullptr &&
                        action_skill->mana_cost(game()->hero(), level) <=
                            game()->hero()->mana()) {
                        game()->add_action(action_skill->action(game(), level));
                    }
                    break;
                }
                case sf::Keyboard::Escape:
                    renderer().window().close();
                    break;
                default:
                    break;
            }
        }
    }
}

void InputHandler::handle_cursor_input() {
    sf::Event event;
    while (renderer().window().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            renderer().window().close();
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
                case sf::Keyboard::Space:
                    if (valid_cursor()) {
                        auto& [skill, level] =
                            game()->hero()->skill_set().get(*skill_id());
                        if (auto targeted_skill =
                                std::dynamic_pointer_cast<TargetedSkill>(skill);
                            targeted_skill != nullptr &&
                            targeted_skill->mana_cost(game()->hero(), level) <=
                                game()->hero()->mana()) {
                            game()->add_action(targeted_skill->action(
                                game(), level, *renderer().cursor()));
                            renderer().remove_cursor();
                            validator_ = nullptr;
                        }
                    }
                    break;
                case sf::Keyboard::Escape:
                    renderer().remove_cursor();
                    break;
                default:
                    break;
            }
            if (dir != Direction::none()) {
                renderer().move_cursor(dir);
            }
        }
    }
}

bool InputHandler::valid_cursor() {
    return validator_(game(), *renderer().cursor());
}

}  // namespace rln
