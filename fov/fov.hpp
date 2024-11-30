#pragma once

#include <cstddef>
#include "matrix.hpp"
#include "point.hpp"

namespace rln {

class Stage;
struct Slope;

// TODO
class Fov {
public:
    // TODO: move to update() parameter if Fov is moved to Entity
    static constexpr std::size_t view_distance = 10;

    Fov();

    void init(Stage* stage);

    void update(Point origin, Point bound);

    bool visible(Point pos) const;

    void visible(Point pos, bool is_visible);

private:
    Stage* stage_;
    bool needs_recalculation_;
    bpns::matrix<bool> visibility_;

    void compute(unsigned octant, Point origin, int x, Slope top, Slope bottom);

    bool blocks_light(int x, int y, unsigned octant, Point origin);

    void set_visible(int x, int y, unsigned octant, Point origin);
};

}  // namespace rln
