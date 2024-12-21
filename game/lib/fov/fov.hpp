#pragma once

#include "matrix.hpp"
#include "point.hpp"

namespace rln {

class Stage;
struct Slope;

// TODO
class Fov {
public:
    Fov(int view_distance);

    void init(Stage* stage);

    void update(Point origin);

    bool visible(Point pos) const;

    void visible(Point pos, bool is_visible);

private:
    Stage* stage_;
    bool needs_recalculation_;
    bpns::matrix<bool> visibility_;
    int view_distance_;

    void compute(unsigned octant, Point origin, int x, Slope top, Slope bottom);

    bool blocks_light(int x, int y, unsigned octant, Point origin);

    void set_visible(int x, int y, unsigned octant, Point origin);
};

}  // namespace rln
