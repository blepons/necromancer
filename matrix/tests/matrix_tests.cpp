#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "matrix.hpp"
#include <algorithm>
#include <utility>
#include <string>

using namespace bpns;

TEST_CASE("matrix constructors", "[matrix][constructor]") {
    SECTION("defaut constructor") {
        matrix<std::string> m;

        REQUIRE(m.size() == 0);
        REQUIRE(m.capacity() == 0);
        REQUIRE(m.rows() == 0);
        REQUIRE(m.columns() == 0);
    }

    SECTION("constructor with init value and dimensions") {
        matrix<std::string> m(4, 6, ":)");

        REQUIRE(m.size() == 4 * 6);
        REQUIRE(m.capacity() >= 4 * 6);
        REQUIRE(m.rows() == 4);
        REQUIRE(m.columns() == 6);
        REQUIRE(std::ranges::all_of(m, [](const auto& item) { return item == ":)"; }));

        matrix<int> empty1(4, 0);
        matrix<int> empty2(0, 1);
        matrix<int> empty3(0, 1);

        REQUIRE(empty1.size() == 0);
        REQUIRE(empty1.capacity() == 0);
        REQUIRE(empty1.rows() == 0);
        REQUIRE(empty1.columns() == 0);

        REQUIRE(empty2.size() == 0);
        REQUIRE(empty2.capacity() == 0);
        REQUIRE(empty2.rows() == 0);
        REQUIRE(empty2.columns() == 0);

        REQUIRE(empty3.size() == 0);
        REQUIRE(empty3.capacity() == 0);
        REQUIRE(empty3.rows() == 0);
        REQUIRE(empty3.columns() == 0);

        REQUIRE_THROWS([](){
            matrix<int> a(1, -1);
        }());
    }

    SECTION("initializer list constructor") {
        matrix<std::string> m = {{"1", "2", "3", "4"}, {"5", "6", "7", "8"}, {"9", "10", "11", "12"}};
        std::vector<std::string> elems = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};

        REQUIRE(m.size() == 12);
        REQUIRE(m.capacity() >= 12);
        REQUIRE(m.rows() == 3);
        REQUIRE(m.columns() == 4);
        REQUIRE(std::ranges::equal(m, elems));

        REQUIRE_THROWS([](){
            matrix<int> a = {{1, 2, 3}, {1, 2}};
        }());

        matrix<int> empty1 = std::initializer_list<std::initializer_list<int>>{};
        matrix<int> empty2 = {{}, {}};

        REQUIRE(empty1.size() == 0);
        REQUIRE(empty1.capacity() == 0);
        REQUIRE(empty1.rows() == 0);
        REQUIRE(empty1.columns() == 0);

        REQUIRE(empty2.size() == 0);
        REQUIRE(empty2.capacity() == 0);
        REQUIRE(empty2.rows() == 0);
        REQUIRE(empty2.columns() == 0);
    }

    SECTION("copy constructor") {
        matrix<std::string> m = {{"1", "2", "3", "4"}, {"5", "6", "7", "8"}, {"9", "10", "11", "12"}};
        matrix<std::string> cp(m);

        REQUIRE(cp.size() == m.size());
        REQUIRE(cp.capacity() >= m.size());
        REQUIRE(cp.rows() == m.rows());
        REQUIRE(cp.columns() == m.columns());

        REQUIRE(std::ranges::equal(m, cp));

        matrix<int> empty;
        matrix<int> empty_copy(empty);

        REQUIRE(empty_copy.size() == 0);
        REQUIRE(empty_copy.capacity() == 0);
        REQUIRE(empty_copy.rows() == 0);
        REQUIRE(empty_copy.columns() == 0);
    }

    SECTION("move constructor") {
        matrix<std::string> m = {{"1", "2", "3", "4"}, {"5", "6", "7", "8"}, {"9", "10", "11", "12"}};
        matrix<std::string> cp(m);
        matrix<std::string> mv(std::move(m));

        REQUIRE(mv.size() == cp.size());
        REQUIRE(mv.capacity() >= cp.size());
        REQUIRE(mv.rows() == cp.rows());
        REQUIRE(mv.columns() == cp.columns());

        REQUIRE(std::ranges::equal(mv, cp));
    }
}

TEST_CASE("matrix assignment operators", "[matrix][assignment]") {
    SECTION("copy assignment") {
        matrix<std::string> m = {{"1", "2", "3", "4"}, {"5", "6", "7", "8"}, {"9", "10", "11", "12"}};
        matrix<std::string> cp = {{"0"}};
        cp = m;

        REQUIRE(cp.size() == m.size());
        REQUIRE(cp.capacity() >= m.size());
        REQUIRE(cp.rows() == m.rows());
        REQUIRE(cp.columns() == m.columns());

        REQUIRE(std::ranges::equal(m, cp));

        matrix<int> empty;
        matrix<int> empty_copy = {{1}};
        empty_copy = empty;

        REQUIRE(empty_copy.size() == 0);
        REQUIRE(empty_copy.capacity() == 0);
        REQUIRE(empty_copy.rows() == 0);
        REQUIRE(empty_copy.columns() == 0);

        matrix<int> self_copy_assignment = {{1, 2, 3}};
        matrix<int> cp2(self_copy_assignment);
        self_copy_assignment = self_copy_assignment;

        REQUIRE(self_copy_assignment.size() == cp2.size());
        REQUIRE(self_copy_assignment.capacity() >= cp2.size());
        REQUIRE(self_copy_assignment.rows() == cp2.rows());
        REQUIRE(self_copy_assignment.columns() == cp2.columns());
        REQUIRE(std::ranges::equal(self_copy_assignment, cp2));

        matrix<int> same_size1 = {{1, 2}, {3, 4}};
        matrix<int> same_size2(2, 2);
        same_size2 = same_size1;

        REQUIRE(std::ranges::equal(same_size2, same_size1));
    }

    SECTION("move assignment") {
        matrix<std::string> m = {{"1", "2", "3", "4"}, {"5", "6", "7", "8"}, {"9", "10", "11", "12"}};
        matrix<std::string> m_copy(m);
        matrix<std::string> cp1 = {{"0"}};
        cp1 = std::move(m);

        REQUIRE(cp1.size() == m_copy.size());
        REQUIRE(cp1.capacity() >= m_copy.size());
        REQUIRE(cp1.rows() == m_copy.rows());
        REQUIRE(cp1.columns() == m_copy.columns());

        REQUIRE(std::ranges::equal(m_copy, cp1));

        matrix<int> empty;
        matrix<int> cp2 = {{1}};
        cp2 = std::move(empty);

        REQUIRE(cp2.size() == 0);
        REQUIRE(cp2.capacity() == 0);
        REQUIRE(cp2.rows() == 0);
        REQUIRE(cp2.columns() == 0);

    }
}

TEST_CASE("matrix element access", "[matrix][element_access]") {
    SECTION("at") {
        matrix<std::string> m = {{"1", "2"}, {"3", "4"}};
        std::vector<std::string> second_row = {"3", "4"};

        REQUIRE(m.at(0, 1) == "2");
        REQUIRE_THROWS(m.at(2, 2));
        REQUIRE_THROWS(m.at(1, 2));
        REQUIRE(std::ranges::equal(m.at(1), second_row));
        REQUIRE_THROWS(m.at(3));

        auto& const_m = std::as_const(m);
        REQUIRE(const_m.at(0, 1) == "2");
        REQUIRE_THROWS(const_m.at(2, 2));
        REQUIRE_THROWS(const_m.at(1, 2));
        REQUIRE(std::ranges::equal(const_m.at(1), second_row));
        REQUIRE_THROWS(const_m.at(3));
    }

    SECTION("operator_at") {
        matrix<std::string> m = {{"1", "2"}, {"3", "4"}};
        std::vector<std::string> second_row = {"3", "4"};

        REQUIRE(m(0, 1) == "2");
        REQUIRE(std::ranges::equal(m[1], second_row));

        auto& const_m = std::as_const(m);

        REQUIRE(const_m(0, 1) == "2");
        REQUIRE(std::ranges::equal(const_m[1], second_row));

    }

    SECTION("data") {
        matrix<std::string> m = {{"1", "2"}, {"3", "4"}};

        REQUIRE(*(m.data() + 2) == "3");

        auto& const_m = std::as_const(m);

        REQUIRE(*(const_m.data() + 2) == "3");
    }
}

TEST_CASE("matrix capacity", "[matrix][capacity]") {
    SECTION("empty") {
        matrix<int> m;

        REQUIRE(m.empty());
        REQUIRE(m.size() == 0);
        REQUIRE(m.rows() == 0);
        REQUIRE(m.columns() == 0);

        m.resize(2, 2);

        REQUIRE(!m.empty());
    }

    SECTION("rows") {
        matrix<int> m = {{1}, {2}, {3}};

        REQUIRE(m.rows() == 3);
    }

    SECTION("columns") {
        matrix<int> m = {{1, 2}, {3, 4}, {5, 6}};

        REQUIRE(m.columns() == 2);
    }

    SECTION("size") {
        matrix<int> m = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}};

        REQUIRE(m.size() == m.rows() * m.columns());
    }

    SECTION("max_size") {

    }

    SECTION("capacity") {
        matrix<int> m = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}};

        REQUIRE(m.capacity() >= m.size());
    }
}

TEST_CASE("matrix modifiers", "[matrix][modifiers]") {
    SECTION("clear") {
        matrix<int> m = {{1, 2}, {3, 4}};
        m.clear(); 

        REQUIRE(m.empty());
        REQUIRE(m.size() == 0);
        REQUIRE(m.rows() == 0);
        REQUIRE(m.columns() == 0);
    }

    SECTION("resize") {
        matrix<std::string> m = {{"1", "2", "3"}, {"4", "5", "6"}, {"7", "8", "9"}};
        matrix<std::string> cp(m);

        m.resize(3, 3);

        REQUIRE(m.rows() == 3);
        REQUIRE(m.columns() == 3);
        REQUIRE(m == cp);

        m.resize(2, 2);

        REQUIRE(m.rows() == 2);
        REQUIRE(m.columns() == 2);
        REQUIRE(m == matrix<std::string>{{"1", "2"}, {"4", "5"}});

        m.resize(4, 1, "x");

        REQUIRE(m.rows() == 4);
        REQUIRE(m.columns() == 1);
        REQUIRE(m == matrix<std::string>{{"1"}, {"4"}, {"x"}, {"x"}});

        m.resize(1, 4, "y");

        REQUIRE(m.rows() == 1);
        REQUIRE(m.columns() == 4);
        REQUIRE(m == matrix<std::string>{{"1", "y", "y", "y"}});

        m.resize(4, 4, "z");

        REQUIRE(m.rows() == 4);
        REQUIRE(m.columns() == 4);
        REQUIRE(m == matrix<std::string>{{"1", "y", "y", "y"},{"z", "z", "z", "z"},{"z", "z", "z", "z"},{"z", "z", "z", "z"}});

        m.resize(0, 0);

        REQUIRE(m.empty());
    }

    SECTION("swap") {
        matrix<std::string> two_by_two = {{"1", "2"}, {"3", "4"}};
        matrix<std::string> three_by_one = {{"a"}, {"b"}, {"c"}};

        auto two_by_two_copy(two_by_two);
        auto three_by_one_copy(three_by_one);

        two_by_two.swap(three_by_one);

        REQUIRE(two_by_two == three_by_one_copy);
        REQUIRE(three_by_one == two_by_two_copy);
    }
}

TEST_CASE("matrix non-member functions", "[matrix][non_member_functions]") {
    SECTION("operator_cmp") {
        matrix<int> m1 = {{1, 2}, {3, 4}};
        matrix<int> m2 = {{1, 2, 3, 4}};
        matrix<int> m3 = {{1, 2}, {3, 4}, {5, 6}};
        matrix<int> m4 = {{9, 8}, {7, 6}};
        matrix<int> m5 = {{1, 2}, {3, 4}};

        REQUIRE(m1 != m2);
        REQUIRE(m1 != m3);
        REQUIRE(m1 != m4);
        REQUIRE(m1 == m5);
    }

    SECTION("swap") {
        matrix<std::string> two_by_two = {{"1", "2"}, {"3", "4"}};
        matrix<std::string> three_by_one = {{"a"}, {"b"}, {"c"}};

        auto two_by_two_copy(two_by_two);
        auto three_by_one_copy(three_by_one);

        swap(two_by_two, three_by_one);

        REQUIRE(two_by_two == three_by_one_copy);
        REQUIRE(three_by_one == two_by_two_copy);
    }
}

TEST_CASE("row") {
    SECTION("access") {
        matrix m = {{1, 2}, {3, 4}};
        auto row = m[1];
        
        REQUIRE(row.row() == 1);
        REQUIRE(std::ranges::equal(row, std::vector{3, 4}));
    }

    SECTION("conversions") {
        matrix m = {{1, 2}, {3, 4}};
        auto row = m[1];
        auto row_const = std::as_const(m)[1];
        matrix<int>::row cp1(row);
        matrix<int>::const_row cp2(row_const);
        matrix<int>::const_row cp3(row);

        REQUIRE(cp1.row() == 1);
        REQUIRE(cp2.row() == 1);
        REQUIRE(cp3.row() == 1);
        REQUIRE(row == cp1);
        REQUIRE(row == cp2);
        REQUIRE(row == cp3);
    }

    SECTION("element access") {
        matrix m = {{1, 2, 3, 4}, {5, 6, 7, 8}};
        auto row = m[0];

        REQUIRE(row[2] == 3);
        REQUIRE(row.at(2) == 3);
        REQUIRE(std::as_const(row)[2] == 3);
        REQUIRE(std::as_const(row).at(2) == 3);
        REQUIRE(m[1][3] == 8);
        REQUIRE(row.front() == 1);
        REQUIRE(std::as_const(row).front() == 1);
        REQUIRE(row.back() == 4);
        REQUIRE(std::as_const(row).back() == 4);
        REQUIRE_THROWS(row.at(4));
        REQUIRE_THROWS(std::as_const(row).at(4));

        auto row_const = std::as_const(m)[1];

        REQUIRE(row_const[1] == 6);
        REQUIRE(row_const.front() == 5);
        REQUIRE(row_const.back() == 8);
        REQUIRE_THROWS(row_const.at(4));
    }

    SECTION("capacity") {
        matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        auto row = m[1];

        REQUIRE(row.size() == 3);
        REQUIRE(row.capacity() == 3);
        REQUIRE(row.row() == 1);
        REQUIRE(!row.empty());
    }

    SECTION("modifiers") {
        matrix m = {{1, 2}, {3, 4}};
        auto first = std::as_const(m)[0];
        auto second = std::as_const(m)[1];
        first.swap(second);

        REQUIRE(std::ranges::equal(first, std::vector{3, 4}));
        REQUIRE(std::ranges::equal(second, std::vector{1, 2}));
    }

    SECTION("non-member functions") {
        matrix m1 = {{1, 2}, {3, 4}};
        matrix m2 = {{1, 2, 3}, {4, 5, 6}};
        matrix m3 = {{0, 0}, {3, 4}};

        auto r1 = m1[0];
        auto r2 = m1[1];
        auto r3 = m2[0];
        auto r4 = m3[1];

        REQUIRE(r1 != r3);
        REQUIRE(r1 != r4);
        REQUIRE(r2 == r4);

        swap(r1, r3);

        REQUIRE(std::ranges::equal(r1, std::vector{1, 2, 3}));
        REQUIRE(std::ranges::equal(r3, std::vector{1, 2}));
    }
}
