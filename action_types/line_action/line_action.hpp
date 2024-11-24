#pragma once

#include "action.hpp"

namespace rln {

class LineAction : public Action {
public:
    LineAction(Game* game, Point init, Point target, int range);

    ActionResult perform() override;

    bool immediate() const override;

    virtual void on_hit(Point pos) = 0;

protected:
    Point target_;
    int range_;
};

}  // namespace rln
