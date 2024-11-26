#pragma once

#include <cstddef>
#include "point.hpp"

namespace rln {

class Stage;
struct Slope;

// TODO
class Fov {
public:
    // TODO: move to update() parameter if Fov is moved to Entity
    static constexpr std::size_t view_distance = 10;

    Fov(Stage* stage);

    void update(Point origin, Point bound);

private:
    Stage* stage_;
    bool needs_recalculation_;

    void compute(unsigned octant, Point origin, int x, Slope top, Slope bottom);

    bool blocks_light(int x, int y, unsigned octant, Point origin);

    void set_visible(int x, int y, unsigned octant, Point origin);
};

}  // namespace rln
