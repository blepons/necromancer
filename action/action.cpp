#include "action.hpp"
#include "entity.hpp"
#include "game.hpp"

namespace rln {

Action::Action(Game* game, Point pos) : game_(game), pos_(pos) {}

Game* Action::game() const {
    return game_;
}

Point Action::pos() const {
    return pos_;
}

bool Action::immediate() const {
    return true;
}

void Action::add_action(Action* action) {
    game_->add_action(action);
}

void Action::add_event(Event event) {
    game_->add_event(event);
}

void Action::move_entity(Entity* entity, Point destination) {
    entity->position(destination, game_);
}

}  // namespace rln
