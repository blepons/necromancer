#ifndef MATRIX_MATRIX_HPP_
#define MATRIX_MATRIX_HPP_

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace bpns {

template <class Allocator>
static void swap_allocator(Allocator& a, Allocator& b) noexcept(
    std::allocator_traits<Allocator>::propagate_on_container_swap::value ||
    std::allocator_traits<Allocator>::is_always_equal::value) {
    swap_allocator(
        a, b,
        std::integral_constant<
            bool, std::allocator_traits<Allocator>::
                      propagate_on_container_copy_assignment::value>());
}

template <class Allocator>
static void swap_allocator(Allocator& a, Allocator& b, std::true_type) noexcept(
    std::allocator_traits<Allocator>::propagate_on_container_swap::value ||
    std::allocator_traits<Allocator>::is_always_equal::value) {
    std::swap(a, b);
}

template <class Allocator>
static void swap_allocator(Allocator&, Allocator&, std::false_type) noexcept {}

template <class T, class Allocator>
class matrix_base {
public:
    using allocator_type = Allocator;
    using allocator_traits = std::allocator_traits<allocator_type>;
    using size_type = allocator_traits::size_type;
    using difference_type = allocator_traits::difference_type;

protected:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = allocator_traits::pointer;
    using const_pointer = allocator_traits::const_pointer;

    allocator_type allocator_;
    pointer data_;
    pointer data_end_;

    matrix_base() noexcept(noexcept(Allocator())) : matrix_base(Allocator()) {}

    explicit matrix_base(const allocator_type& alloc) noexcept
        : allocator_(alloc), data_(nullptr) {}

    ~matrix_base() {
        if (data_ != nullptr) {
            clear();
            allocator_.deallocate(data_, capacity());
        }
    }

    void deallocate() noexcept {
        if (data_ != nullptr) {
            clear();
            allocator_.deallocate(data_, capacity());
            data_ = nullptr;
        }
    }

    void copy_assign_allocator(const matrix_base& other) {
        copy_assign_allocator(
            other,
            std::integral_constant<
                bool, allocator_traits::propagate_on_container_copy_assignment::
                          value>());
    }

    void move_assign_allocator(matrix_base& other) noexcept(
        allocator_traits::propagate_on_container_move_assignment::value ||
        allocator_traits::is_always_equal::value) {
        move_assign_allocator(
            other,
            std::integral_constant<
                bool, allocator_traits::propagate_on_container_move_assignment::
                          value>());
    }

    void clear() noexcept {
        pointer ptr = data_end_;
        while (ptr != data_) {
            --ptr;
            std::allocator_traits<allocator_type>::destroy(allocator_, ptr);
        }
    }

    size_type capacity() const {
        return static_cast<size_type>(data_end_ - data_);
    }

private:
    void copy_assign_allocator(const matrix_base& other, std::true_type) {
        if (allocator_ != other.allocator_) {
            deallocate();
        }
        allocator_ = other.allocator_;
    }

    void copy_assign_allocator(const matrix_base&, std::false_type) {}

    void move_assign_allocator(matrix_base& other, std::true_type) {
        allocator_ = std::move(other.allocator_);
    }

    void move_assign_allocator(matrix_base&, std::false_type) {}
};

template <class T, class Allocator, bool IsConst>
class row_base;

template <class T, class Allocator = std::allocator<T>>
class matrix : private matrix_base<T, Allocator> {
private:
    using base = matrix_base<T, Allocator>;

public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = base::size_type;
    using difference_type = base::difference_type;
    using reference = base::reference;
    using const_reference = base::const_reference;
    using pointer = base::pointer;
    using const_pointer = base::const_pointer;

    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using row = row_base<T, Allocator, false>;

    using const_row = row_base<T, Allocator, true>;

private:
    static_assert(std::is_same<value_type, std::remove_cv_t<value_type>>(),
                  "bpns::matrix: T must be non-const and non-volatile");
    static_assert(
        std::is_same<value_type, typename allocator_type::value_type>(),
        "bpns::matrix: T must be the same as Allocator::value_type");

public:
    matrix() noexcept(noexcept(Allocator())) : rows_(0), columns_(0) {}

    explicit matrix(const Allocator& alloc) noexcept
        : base(alloc), rows_(0), columns_(0) {}

    matrix(size_type rows,
           size_type columns,
           const T& value = T(),
           const Allocator& alloc = Allocator())
        : base(alloc), rows_(rows), columns_(columns) {
        if (rows == 0 || columns == 0) {
            rows_ = 0;
            columns_ = 0;
        }
        auto n = rows_ * columns_;
        if (n > 0) {
            allocate(n);
            std::uninitialized_fill_n(data(), n, value);
        }
    }

    matrix(const matrix& other)
        : matrix(other,
                 std::allocator_traits<allocator_type>::
                     select_on_container_copy_construction(
                         other.get_allocator())) {}

    matrix(matrix&& other) noexcept : base(other.allocator_) {
        this->data_ = std::exchange(other.data_, nullptr);
        this->data_end_ = std::exchange(other.data_end_, nullptr);
        rows_ = std::exchange(other.rows_, 0);
        columns_ = std::exchange(other.columns_, 0);
    }

    matrix(const matrix& other, const Allocator& alloc)
        : base(alloc), rows_(other.rows_), columns_(other.columns_) {
        auto n = other.size();
        if (n > 0) {
            allocate(n);
            std::uninitialized_fill_n(data(), n, T());
        }
    }

    matrix(matrix&& other, const Allocator& alloc) : base(alloc) {
        if (other.get_allocator() == alloc) {
            this->data_ = std::exchange(other.data_, nullptr);
            this->data_end_ = std::exchange(other.data_end_, nullptr);
            rows_ = std::exchange(other.rows_, 0);
            columns_ = std::exchange(other.columns_, 0);
        } else {
            if (size() != other.size()) {
                clear();
                allocate(other.size());
                std::uninitialized_copy_n(
                    std::move_iterator<iterator>(other.begin()), other.size(),
                    begin());
            } else {
                std::copy_n(std::move_iterator<iterator>(other.begin()),
                            other.size(), begin());
            }
            rows_ = other.rows_;
            columns_ = other.columns_;
        }
    }

    matrix(std::initializer_list<std::initializer_list<T>> init,
           const Allocator& alloc = Allocator())
        : base(alloc), rows_(0), columns_(0) {
        size_type columns = init.size();
        size_type rows = 0;
        if (columns > 0) {
            rows = init[0].size();
            if (std::any_of(
                    init.begin() + 1, init.end(),
                    [rows](const auto& i) { return i.size() != rows; })) {
                throw std::logic_error(
                    "bpns::matrix::matrix: sizes of initializer lists differ");
            }
        }
        auto n = columns * rows;
        if (n > 0) {
            allocate(n);
            for (const auto& row : init) {
                std::uninitialized_copy_n(row.begin(), columns, data());
                ++rows_;
            }
            columns_ = columns;
        }
    }

    matrix& operator=(const matrix& other) {
        if (this != std::addressof(other)) {
            copy_assign(other);
        }
        return *this;
    }

    matrix& operator=(matrix&& other) noexcept(
        std::allocator_traits<
            allocator_type>::propagate_on_container_move_assignment::value ||
        std::allocator_traits<allocator_type>::is_always_equal::value) {
        move_assign(other);
        return *this;
    }

    allocator_type get_allocator() const noexcept { return this->allocator_; }

    iterator begin() noexcept { return static_cast<iterator>(data()); }

    const_iterator begin() const noexcept {
        return static_cast<const_iterator>(data());
    }

    iterator end() noexcept { return static_cast<iterator>(data() + size()); }

    const_iterator end() const noexcept {
        return static_cast<const_iterator>(data() + size());
    }

    reverse_iterator rbegin() noexcept { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const noexcept {
        return reverse_iterator(begin());
    }

    reverse_iterator rend() noexcept { return reverse_iterator(end()); }

    const_reverse_iterator rend() const noexcept {
        return reverse_iterator(end());
    }

    const_iterator cbegin() const noexcept { return begin(); }

    const_iterator cend() const noexcept { return end(); }

    const_reverse_iterator crbegin() const noexcept { return rbegin(); }

    const_reverse_iterator crend() const noexcept { return rend(); }

    bool empty() const noexcept { return size() == 0; }

    size_type rows() const noexcept { return rows_; }

    size_type columns() const noexcept { return columns_; }

    size_type size() const noexcept { return rows_ * columns_; }

    size_type max_size() const noexcept {
        return std::allocator_traits<allocator_type>::max_size(
            this->allocator_);
    }

    void resize(size_type r, size_type c, const T& v = T()) {
        const auto n = r * c;
        if (size() != n) {
            matrix tmp(this->allocator_);
            if (n > 0) {
                tmp.allocate(n);
                tmp.rows_ = r;
                tmp.columns_ = c;
                for (size_type i = 0; i < std::min(rows(), r); ++i) {
                    auto row = get_row(i);
                    auto tmp_row = tmp.get_row(i);
                    std::uninitialized_move_n(
                        row.begin(), std::min(columns(), c), tmp_row.begin());
                    std::uninitialized_fill_n(
                        tmp_row.begin() + std::min(columns(), c),
                        c - std::min(columns(), c), v);
                }
                for (size_type i = std::min(rows(), r); i < r; ++i) {
                    auto tmp_row = tmp.get_row(i);
                    std::uninitialized_fill_n(tmp_row.begin(), c, v);
                }
            }
            *this = std::move(tmp);
        } else if (r != rows()) {
            if (c > columns()) {
                for (size_type i = r; i > 0; --i) {
                    auto row = get_row(i);
                    std::copy_n(row.begin(), columns(), data() + i * columns());
                }
                const auto prev_rows = rows();
                const auto prev_columns = columns();
                rows_ = r;
                columns_ = c;
                for (size_type i = 0; i < r; ++i) {
                    auto row = get_row(i);
                    std::fill_n(row.begin() + prev_columns,
                                columns() - prev_columns, v);
                }
            } else {
                for (size_type i = 1; i < rows(); ++i) {
                    auto row = get_row(i);
                    std::copy_n(row.begin(), c, data() + i * c);
                }
                std::fill(data() + c * rows(), this->data_end_, v);
                rows_ = r;
                columns_ = c;
            }
        }
    }

    reference operator()(size_type row, size_type column) {
        return *(data() + row * columns() + column);
    }

    const_reference operator()(size_type row, size_type column) const {
        return *(data() + row * columns() + column);
    }

    reference at(size_type row, size_type column) {
        if (row >= rows()) {
            throw std::out_of_range("matrix::at: row >= rows()");
        }
        if (column >= columns()) {
            throw std::out_of_range("matrix::at: column >= columns()");
        }
        return *(data() + row * columns() + column);
    }

    const_reference at(size_type row, size_type column) const {
        if (row >= rows()) {
            throw std::out_of_range("matrix::at: row >= rows()");
        }
        if (column >= columns()) {
            throw std::out_of_range("matrix::at: column >= columns()");
        }
        return *(data() + row * columns() + column);
    }

    T* data() noexcept { return this->data_; }

    const T* data() const noexcept { return this->data_; }

    row get_row(size_type r) { return row(*this, r); }

    const_row get_row(size_type r) const { return const_row(*this, r); }

    row operator[](size_type r) { return row(*this, r); }

    const_row operator[](size_type r) const { return const_row(*this, r); }

    void clear() noexcept {
        base::clear();
        rows_ = 0;
        columns_ = 0;
    }

    void swap(matrix& other) noexcept(
        std::allocator_traits<
            allocator_type>::propagate_on_container_swap::value ||
        std::allocator_traits<allocator_type>::is_always_equal::value) {
        std::swap(this->data_, other.data_);
        std::swap(this->data_end_, other.data_end_);
        std::swap(rows_, other.rows_);
        std::swap(columns_, other.columns_);
        swap_allocator(this->allocator_, other.allocator_);
    }

private:
    size_type rows_;
    size_type columns_;

    void allocate(size_type n) {
        if (n > max_size()) {
            throw std::length_error("bpns::matrix::allocate: n > max_size()");
        }
        if (n > 0) {
            this->data_ = this->allocator_.allocate(n);
            this->data_end_ = this->data_ + n;
        }
    }

    void move_assign(matrix& other) {
        move_assign(
            other,
            std::integral_constant<
                bool, std::allocator_traits<allocator_type>::
                          propagate_on_container_move_assignment::value>());
    }

    void move_assign(matrix& other, std::false_type) {
        if (this->allocator_ == other.allocator_) {
            move_assign(std::move(other), std::true_type());
        } else {
            if (size() != other.size()) {
                clear();
                allocate(other.size());
                std::uninitialized_copy_n(
                    std::move_iterator<iterator>(other.begin()), other.size(),
                    begin());
            } else {
                std::copy_n(std::move_iterator<iterator>(other.begin()),
                            other.size(), begin());
            }
            rows_ = other.rows_;
            columns_ = other.columns_;
        }
    }

    void move_assign(matrix& other, std::true_type) {
        base::deallocate();
        base::move_assign_allocator(other);
        this->data_ = std::exchange(other.data_, nullptr);
        this->data_end_ = std::exchange(other.data_end_, nullptr);
        rows_ = std::exchange(other.rows_, 0);
        columns_ = std::exchange(other.columns_, 0);
    }

    void copy_assign(const matrix& other) {
        base::copy_assign_allocator(other);
        if (size() != other.size()) {
            clear();
            allocate(other.size());
            std::uninitialized_copy_n(other.begin(), other.size(), begin());
        } else {
            std::copy_n(other.begin(), other.size(), begin());
        }
        rows_ = other.rows_;
        columns_ = other.columns_;
    }
};

template <class T, class Allocator, bool IsConst>
class row_base {
public:
    using matrix_type = std::conditional_t<IsConst,
                                           const matrix<T, Allocator>,
                                           matrix<T, Allocator>>;
    using value_type = matrix_type::value_type;
    using size_type = matrix_type::size_type;
    using difference_type = matrix_type::difference_type;
    using reference = std::conditional_t<IsConst,
                                         typename matrix_type::const_reference,
                                         typename matrix_type::reference>;
    using const_reference = matrix_type::const_reference;
    using pointer = std::conditional_t<IsConst,
                                       typename matrix_type::const_pointer,
                                       typename matrix_type::pointer>;
    using const_pointer = matrix_type::const_pointer;

    using iterator = std::conditional_t<IsConst,
                                        typename matrix_type::const_pointer,
                                        typename matrix_type::pointer>;
    using const_iterator = matrix_type::const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    row_base(matrix_type& mx, size_type r) : matrix_(mx), row_(r) {}

    row_base(const row_base& other) noexcept = default;

    row_base& operator=(const row_base& other) noexcept = default;

    operator row_base<T, Allocator, true>() const {
        return row_base<T, Allocator, true>(matrix_.get(), row_);
    }

    iterator begin() noexcept {
        return static_cast<iterator>(matrix_.get().data() +
                                     matrix_.get().columns() * row_);
    }

    const_iterator begin() const noexcept {
        return static_cast<const_iterator>(matrix_.get().data() +
                                           matrix_.get().columns() * row_);
    }

    iterator end() noexcept {
        return static_cast<iterator>(matrix_.get().data() +
                                     matrix_.get().columns() * (row_ + 1));
    }

    const_iterator end() const noexcept {
        return static_cast<const_iterator>(
            matrix_.get().data() + matrix_.get().columns() * (row_ + 1));
    }

    reverse_iterator rbegin() noexcept { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const noexcept {
        return reverse_iterator(begin());
    }

    reverse_iterator rend() noexcept { return reverse_iterator(end()); }

    const_reverse_iterator rend() const noexcept {
        return reverse_iterator(end());
    }

    const_iterator cbegin() const noexcept { return begin(); }

    const_iterator cend() const noexcept { return end(); }

    const_reverse_iterator crbegin() const noexcept { return rbegin(); }

    const_reverse_iterator crend() const noexcept { return rend(); }

    reference operator[](difference_type n) { return matrix_(row_, n); }

    const_reference operator[](size_type n) const { return matrix_(row_, n); }

    bool empty() const noexcept { return (size() == 0); }

    size_type size() const noexcept { return matrix_.get().columns(); }

    reference at(size_type n) {
        if (n >= size()) {
            throw std::out_of_range("matrix::row::at: n >= size()");
        }
        return matrix_(row_, n);
    }

    const_reference at(size_type n) const {
        if (n >= size()) {
            throw std::out_of_range("matrix::row::at: n >= size()");
        }
        return matrix_(row_, n);
    }

    reference front() { return matrix_(row_, 0); }

    const_reference front() const { return matrix_(row_, 0); }

    reference back() { return matrix_(row_, matrix_.get().columns() - 1); }

    const_reference back() const {
        return matrix_(row_, matrix_.get().columns() - 1);
    }

    void swap(row_base& other) noexcept {
        std::swap(matrix_, other.matrix_);
        std::swap(row_, other.row_);
    }

private:
    std::reference_wrapper<matrix_type> matrix_;
    size_type row_;
};

template <class T, class Allocator>
inline bool operator==(const matrix<T, Allocator>& lhs,
                       const matrix<T, Allocator>& rhs) {
    return lhs.columns() == rhs.columns() && lhs.rows() == rhs.rows() &&
           std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

}  // namespace bpns

#endif  // !MATRIX_MATRIX_HPP_
