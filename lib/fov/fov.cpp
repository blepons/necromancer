#include "fov.hpp"
#include "stage.hpp"

namespace rln {

// http://www.adammil.net/blog/v125_roguelike_vision_algorithms.html#mycode

struct Slope {
    Slope(int y, int x) : y(y), x(x) {}

    int y;
    int x;
};

auto operator<=>(const Slope& lhs, const Slope& rhs) {
    return lhs.y * rhs.x <=> rhs.y * lhs.x;
}

Fov::Fov(int view_distance)
    : stage_(nullptr),
      needs_recalculation_(true),
      visibility_(),
      view_distance_(view_distance) {}

void Fov::init(Stage* stage) {
    stage_ = stage;
    visibility_ = bpns::matrix<bool>(stage->bound_x(), stage_->bound_y());
}

bool Fov::visible(Point pos) const {
    return visibility_(pos.x, pos.y);
}

void Fov::visible(Point pos, bool is_visible) {
    visibility_(pos.x, pos.y) = is_visible;
}

void Fov::update(Point origin) {
    for (int x = 0; x < stage_->bound_x(); ++x) {
        for (int y = 0; y < stage_->bound_y(); ++y) {
            visible({x, y}, false);
        }
    }

    for (unsigned octant = 0; octant < 8; ++octant) {
        compute(octant, origin, 1, Slope(1, 1), Slope(0, 1));
    }

    visible(origin, true);
}

void Fov::compute(unsigned octant,
                  Point origin,
                  int x,
                  Slope top,
                  Slope bottom) {
    for (; x <= view_distance_; ++x) {
        int top_y;
        if (top.x == 1) {
            top_y = x;
        } else {
            top_y = ((x * 2 - 1) * top.y + top.x) / (top.x * 2);

            if (blocks_light(x, top_y, octant, origin)) {
                if (top >= Slope(top_y * 2 + 1, x * 2) &&
                    !blocks_light(x, top_y + 1, octant, origin)) {
                    ++top_y;
                }
            } else {
                int ax = x * 2;

                if (blocks_light(x + 1, top_y + 1, octant, origin)) {
                    ++ax;
                }
                if (top > Slope(top_y * 2 + 1, ax)) {
                    ++top_y;
                }
            }
        }

        int bottom_y;
        if (bottom.y == 0) {
            bottom_y = 0;
        } else {
            bottom_y = ((x * 2 - 1) * bottom.y + bottom.x) / (bottom.x * 2);

            if (bottom >= Slope(bottom_y * 2 + 1, x * 2) &&
                blocks_light(x, bottom_y, octant, origin) &&
                !blocks_light(x, bottom_y + 1, octant, origin)) {
                ++bottom_y;
            }
        }

        int was_opaque = -1;
        for (int y = top_y; y >= bottom_y; --y) {
            if (Point::euclidean_ceil(x, y) <= view_distance_) {
                bool is_opaque = blocks_light(x, y, octant, origin);

                if ((y != top_y || top >= Slope(y, x)) &&
                    (y != bottom_y || bottom <= Slope(y, x))) {
                    set_visible(x, y, octant, origin);
                }

                if (x != view_distance_) {
                    if (is_opaque) {
                        if (was_opaque == 0) {
                            int nx = x * 2;
                            int ny = y * 2 + 1;

                            if (blocks_light(x, y + 1, octant, origin)) {
                                --nx;
                            }

                            if (top > Slope(ny, nx)) {
                                if (y == bottom_y) {
                                    bottom = Slope(ny, nx);
                                    break;
                                } else {
                                    compute(octant, origin, x + 1, top,
                                            Slope(ny, nx));
                                }
                            } else {
                                if (y == bottom_y) {
                                    return;
                                }
                            }
                        }
                        was_opaque = 1;
                    } else {
                        if (was_opaque > 0) {
                            int nx = x * 2;
                            int ny = y * 2 + 1;

                            if (blocks_light(x + 1, y + 1, octant, origin)) {
                                ++nx;
                            }

                            if (bottom >= Slope(ny, nx)) {
                                return;
                            }
                            top = Slope(ny, nx);
                        }
                        was_opaque = 0;
                    }
                }
            }
        }

        if (was_opaque != 0) {
            break;
        }
    }
}

bool Fov::blocks_light(int x, int y, unsigned octant, Point origin) {
    int nx = origin.x;
    int ny = origin.y;
    switch (octant) {
        case 0:
            nx += x;
            ny -= y;
            break;
        case 1:
            nx += y;
            ny -= x;
            break;
        case 2:
            nx -= y;
            ny -= x;
            break;
        case 3:
            nx -= x;
            ny -= y;
            break;
        case 4:
            nx -= x;
            ny += y;
            break;
        case 5:
            nx -= y;
            ny += x;
            break;
        case 6:
            nx += y;
            ny += x;
            break;
        case 7:
            nx += x;
            ny += y;
            break;
    }
    return !stage_->tile_at({nx, ny}).transparent();
}

void Fov::set_visible(int x, int y, unsigned octant, Point origin) {
    int nx = origin.x;
    int ny = origin.y;
    switch (octant) {
        case 0:
            nx += x;
            ny -= y;
            break;
        case 1:
            nx += y;
            ny -= x;
            break;
        case 2:
            nx -= y;
            ny -= x;
            break;
        case 3:
            nx -= x;
            ny -= y;
            break;
        case 4:
            nx -= x;
            ny += y;
            break;
        case 5:
            nx -= y;
            ny += x;
            break;
        case 6:
            nx += y;
            ny += x;
            break;
        case 7:
            nx += x;
            ny += y;
            break;
    }
    visible({nx, ny}, true);
}

}  // namespace rln
