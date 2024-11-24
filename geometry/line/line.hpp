#pragma once

#include <cstdlib>
#include "point.hpp"

namespace geom {

class LineIterator {
public:
    LineIterator(Point from, Point to)
        : current_(from),
          to_(to),
          dx_(std::abs(to.x - from.x)),
          dy_(std::abs(to.y - from.y)),
          sx_(to.x > from.x ? 1 : -1),
          sy_(to.y > from.y ? 1 : -1),
          error_(dx_ - dy_),
          done_(false) {}

    Point operator*() const { return current_; }

    LineIterator& operator++() {
        if (current_ == to_) {
            done_ = true;
            return *this;
        }
        if (2 * error_ > -dy_) {
            error_ -= dy_;
            current_.x += sx_;
        }
        if (current_ == to_) {
            return *this;
        }
        if (2 * error_ < dx_) {
            error_ += dx_;
            current_.y += sy_;
        }
        return *this;
    }

    auto operator==(const LineIterator&) const { return done_; }

private:
    Point current_;
    Point to_;
    int dx_;
    int dy_;
    int sx_;
    int sy_;
    int error_;
    bool done_;
};

class Line {
public:
    Line(Point from, Point to) : from_(from), to_(to) {}

    LineIterator begin() const { return LineIterator(from_, to_); }

    LineIterator end() const { return LineIterator(to_, to_); }

private:
    Point from_;
    Point to_;
};

}  // namespace geom
