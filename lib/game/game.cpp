#include "game.hpp"
#include <memory>
#include "action.hpp"
#include "entity.hpp"
#include "entity_action.hpp"
#include "hero.hpp"
#include "plugin_manager.hpp"
#include "stage.hpp"

namespace rln {

Game::Game(FloorManager* floor_manager,
           TileRegistry tile_registry,
           UndeadRegistry undead_registry)
    : floor_manager_(floor_manager),
      tile_turn_processed_(false),
      tile_registry_(std::move(tile_registry)),
      undead_registry_(std::move(undead_registry)) {}

std::shared_ptr<Hero> Game::hero() {
    return hero_;
}

std::shared_ptr<const Hero> Game::hero() const {
    return hero_;
}

void Game::hero(std::shared_ptr<Hero> hero) {
    hero_ = hero;
}

const Fov& Game::hero_fov() const {
    return hero_->fov();
}

Stage* Game::stage() {
    return floor_manager()->stage();
}

const MobPlugin& Game::plugin(const std::string& id) {
    return PluginManager::get_instance().plugins().at(id);
}

const TileRegistry& Game::tile_registry() const {
    return tile_registry_;
}

const UndeadRegistry& Game::undead_registry() const {
    return undead_registry_;
}

FloorManager* Game::floor_manager() {
    return floor_manager_;
}

// Initial implementation
// TurnResult Game::update() {
//     bool game_changed = false;
//     while (true) {
//         while (!actions_.empty()) {
//             auto action = actions_.front();
//             auto result = action->perform();
//             while (result.alternative != nullptr) {
//                 actions_.pop_front();
//                 action = result.alternative;
//                 actions_.push_front(action);
//                 result = action->perform();
//             }
//             game_changed = true;
//             if (result.done) {
//                 actions_.pop_front();
//                 if (auto entity_action =
//                 std::dynamic_pointer_cast<EntityAction>(action);
//                 entity_action != nullptr) {
//                     if (result.success) {
//                         entity_action->entity()->end_turn(entity_action);
//                         stage()->increment_entity_index();
//                     } else if (entity_action->entity() == hero()) {
//                         return turn_result(game_changed);
//                     }
//                 }
//             }
//             if (!events_.empty()) {
//                 return turn_result(game_changed);
//             }
//         }
//         while (actions_.empty()) {
//             auto entity = stage()->current_entity();
//             auto& energy = entity->energy();
//             if (energy.can_take_turn() && entity->needs_input()) {
//                 return turn_result(game_changed);
//             }
//             if (energy.will_take_turn(entity->speed())) {
//                 energy.gain(entity->speed());
//                 if (entity->needs_input()) {
//                     return turn_result(game_changed);
//                 }
//                 actions_.push_back(entity->action(this));
//             } else {
//                 add_action(stage()->tile_at(entity->position()).on_turn(entity));
//                 stage()->increment_entity_index();
//             }
//         }
//     }
// }

TurnResult Game::update() {
    bool game_changed = false;
    while (true) {
        while (!actions_.empty()) {
            auto action = actions_.front();
            auto result = action->perform();
            while (result.alternative != nullptr) {
                actions_.pop_front();
                action = result.alternative;
                actions_.push_front(action);
                result = action->perform();
            }
            game_changed = true;
            if (result.done) {
                actions_.pop_front();
                if (auto entity_action =
                        std::dynamic_pointer_cast<EntityAction>(action);
                    entity_action != nullptr) {
                    if (result.success) {
                        entity_action->entity()->end_turn(entity_action);
                        increment_entity_index();
                    } else if (std::dynamic_pointer_cast<Hero>(
                                   entity_action->entity()) != nullptr) {
                        return turn_result(game_changed);
                    }
                }
            }
            if (!events_.empty()) {
                return turn_result(game_changed);
            }
        }

        auto entity = stage()->current_entity();
        auto& energy = entity->energy();

        if (!tile_turn_processed_) {
            auto action = stage()
                              ->tile_at(entity->position())
                              .on_turn(this, entity->position());
            if (action) {
                add_action(action);
            }
            tile_turn_processed_ = true;
        }

        if (energy.can_take_turn()) {
            if (entity->needs_input()) {
                return turn_result(game_changed);
            }
            add_action(entity->action(this));
        } else {
            energy.gain(entity->speed());
            if (entity->needs_input()) {
                return turn_result(game_changed);
            }
            if (energy.can_take_turn()) {
                add_action(entity->action(this));
            } else {
                increment_entity_index();
            }
        }
    }
}

TurnResult Game::turn_result(bool game_changed) {
    TurnResult tr = {std::move(events_), game_changed};
    events_ = {};
    return tr;
}

void Game::add_action(std::shared_ptr<Action> action) {
    actions_.push_back(action);
}

void Game::add_event(Event event) {
    events_.push_back(event);
}

int Game::random(int min, int max) {
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen_);
}

int Game::unique_id() {
    auto id = random(0);
    while (used_ids_.contains(id)) {
        id = random(0);
    }
    used_ids_.insert(id);
    return id;
}

void Game::assign_id(std::shared_ptr<Entity> entity) {
    entity->id(unique_id());
}

void Game::reserve_id(int id) {
    used_ids_.insert(id);
}

void Game::next_floor() {
    actions_.clear();
    events_.clear();
    tile_turn_processed_ = false;
    floor_manager()->unload_current_floor();
    floor_manager()->load_next_floor(this);
    transfer_hero();
}

void Game::transfer_hero() {
    if (hero()) {
        hero()->position(stage()->start_pos());
        hero()->fov().init(stage());
        hero()->fov().update(hero()->position());
    }
}

void Game::increment_entity_index() {
    stage()->increment_entity_index();
    tile_turn_processed_ = false;
}

}  // namespace rln
