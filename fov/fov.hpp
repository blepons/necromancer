#pragma once

#include <cstddef>
#include "point.hpp"

namespace rln {

class Stage;

// TODO
class Fov {
public:
    static constexpr std::size_t view_distance = 10;

    Fov(Stage* stage);

    void update(Point origin);

private:
    Stage* stage;
    bool needs_recalculation_;
};

}  // namespace rln
