#include "line_action.hpp"
#include <memory>
#include "action.hpp"
#include "line.hpp"
#include "point.hpp"
#include "stage.hpp"

namespace rln {

LineAction::LineAction(Game* game,
                       std::shared_ptr<Entity> entity,
                       Point init,
                       Point target,
                       int range)
    : EntityAction(game, init, entity), target_(target), range_(range) {}

ActionResult LineAction::perform() {
    if (Point::manhattan(target_, pos()) > static_cast<unsigned>(range_)) {
        return ActionResult::succeed();
    }

    auto line = geom::Line(pos(), target_);
    for (auto it = ++line.begin(); it != line.end(); ++it) {
        auto point = *it;
        if (game()->stage()->occupied(point) ||
            !game()->stage()->tile_at(point).transparent()) {
            on_hit(point);
            return ActionResult::succeed();
        }
    }

    return ActionResult::succeed();
}

}  // namespace rln
