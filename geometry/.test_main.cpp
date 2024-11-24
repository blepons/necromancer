#include <iostream>
#include <random>
#include <utility>
#include "line.hpp"
#include "matrix.hpp"

static constexpr auto rows = 20;
static constexpr auto columns = 80;

int main() {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<std::mt19937::result_type> dist_r(0,
                                                                    rows - 1);
    std::uniform_int_distribution<std::mt19937::result_type> dist_c(
        0, columns - 1);

    for (auto i = 0; i < 10; ++i) {
        bpns::matrix<bool> map(rows, columns, false);

        auto start = Point(dist_r(rng), dist_c(rng));
        auto end = Point(dist_r(rng), dist_c(rng));

        geom::Line line(start, end);

        std::cout << map.rows() << " " << map.columns() << std::endl;
        std::cout << "(" << start.x << ", " << start.y << ") -> (" << end.x
                  << ", " << end.y << ")\n";

        for (const auto& el : line) {
            // std::cout << "(" << el.x << ", " << el.y << ") ";
            // std::cout.flush();
            map.at(el.x, el.y) = true;
        }
        // std::cout << std::endl;

        for (auto i = 0; i < map.rows(); ++i) {
            for (auto j = 0; j < map.columns(); ++j) {
                if (Point(i, j) == start) {
                    std::cout << (map.at(i, j) ? "S" : "s");
                } else if (Point(i, j) == end) {
                    std::cout << (map.at(i, j) ? "E" : "e");
                } else {
                    std::cout << (map.at(i, j) ? "#" : ".");
                }
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;

        for (auto i = 0; i < map.rows(); ++i) {
            const auto row = std::as_const(map).get_row(i);
            for (const auto& item : row) {
                std::cout << (item ? "#" : ".");
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
}
