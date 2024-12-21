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
static void swap_allocator(Allocator& a, Allocator& b, std::true_type) noexcept(
    std::allocator_traits<Allocator>::propagate_on_container_swap::value ||
    std::allocator_traits<Allocator>::is_always_equal::value) {
    std::swap(a, b);
}

template <class Allocator>
static void swap_allocator(Allocator&, Allocator&, std::false_type) noexcept {}

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
        : allocator_(alloc), data_(nullptr), data_end_(nullptr) {}

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
            data_end_ = nullptr;
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

/*!
 * \brief Matrix class.
 */
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
    /*!
     * \brief Default constructor.
     *
     * Constructs an empty container with a default-constructed allocator.
     */
    matrix() noexcept(noexcept(Allocator())) : rows_(0), columns_(0) {}

    /*!
     * \brief Constructs an empty container with the given allocator `alloc`.
     *
     * \param alloc Allocator to use for all allocations of this container.
     */
    explicit matrix(const Allocator& alloc) noexcept
        : base(alloc), rows_(0), columns_(0) {}

    /*!
     * \brief Constructs `rows` x `columns` matrix with copies of element
     * `value`.
     *
     * \param rows The number of the rows.
     * \param columns The number of the columns.
     * \param value The value to initialize the container with.
     * \param alloc Allocator to use for all allocations of this container.
     */
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

    /*!
     * \brief Matrix copy constructor.
     *
     * \param other Another container to be used as source of elements.
     */
    matrix(const matrix& other)
        : matrix(other,
                 std::allocator_traits<allocator_type>::
                     select_on_container_copy_construction(
                         other.get_allocator())) {}

    /*!
     * \brief Matrix move constructor.
     *
     * \param other Another container to be used as source of elements.
     */
    matrix(matrix&& other) noexcept : base(other.allocator_) {
        this->data_ = std::exchange(other.data_, nullptr);
        this->data_end_ = std::exchange(other.data_end_, nullptr);
        rows_ = std::exchange(other.rows_, 0);
        columns_ = std::exchange(other.columns_, 0);
    }

    /*!
     * \brief Constructs the container with the contents of `other`, using
     * `alloc` as the allocator.
     *
     * \param other Another container to be used as source of elements.
     * \param alloc Allocator to use for all allocations of this container.
     */
    matrix(const matrix& other, const Allocator& alloc)
        : base(alloc), rows_(other.rows_), columns_(other.columns_) {
        auto n = other.size();
        if (n > 0) {
            allocate(n);
            std::uninitialized_copy_n(other.data(), n, data());
        }
    }

    /*!
     * \brief Allocator-extended move constructor.
     *
     * If `alloc != other.get_allocator()`, each element is move-assigned
     * individually.
     *
     * \param other Another container to be used as source of elements.
     * \param alloc Allocator to use for all allocations of this container.
     */
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

    /*!
     * \brief Initializer list constructor.
     *
     * \param init Initializer list to initialize the elements of
     *             the matrix with.
     * \param alloc Allocator to use for all allocations of this
     * container.
     */
    matrix(std::initializer_list<std::initializer_list<T>> init,
           const Allocator& alloc = Allocator())
        : base(alloc), rows_(0), columns_(0) {
        size_type rows = init.size();
        size_type columns = 0;
        if (rows > 0) {
            columns = (*init.begin()).size();
            if (std::any_of(
                    init.begin() + 1, init.end(),
                    [columns](const auto& i) { return i.size() != columns; })) {
                throw std::logic_error(
                    "bpns::matrix::matrix: sizes of initializer lists differ");
            }
        }
        auto n = columns * rows;
        if (n > 0) {
            allocate(n);
            for (const auto& row : init) {
                std::uninitialized_copy_n(row.begin(), columns,
                                          data() + columns * rows_);
                ++rows_;
            }
            columns_ = columns;
        }
    }

    /*!
     * \brief Copy-assignment operator.
     *
     * If
     * `std::allocator_traits<allocator_type>::propagate_on_container_copy_assignment::value`
     * is `true`, `*this` allocator is replaced by a copy of `other`.
     *
     * \param other Another container to be used as source of elements.
     */
    matrix& operator=(const matrix& other) {
        if (this != std::addressof(other)) {
            copy_assign(other);
        }
        return *this;
    }

    /*!
     * \brief Move-assignment operator.
     *
     * If
     * `std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value`
     * is `true`, `*this` allocator is replaced by a copy of `other`. Otherwise,
     * if
     * `*this` and `other` allocators don't compare equal, each element is
     * move-assigned individually.
     *
     * \param other Another container to be used as source of elements.
     */
    matrix& operator=(matrix&& other) noexcept(
        std::allocator_traits<
            allocator_type>::propagate_on_container_move_assignment::value ||
        std::allocator_traits<allocator_type>::is_always_equal::value) {
        move_assign(other);
        return *this;
    }

    /*!
     * \brief Returns the allocator object associated with the container.
     *
     * \return The allocator.
     */
    allocator_type get_allocator() const noexcept { return this->allocator_; }

    /*!
     * \brief Returns an iterator to the first element of the container.
     *
     * \return Iterator to the first element.
     */
    iterator begin() noexcept { return static_cast<iterator>(data()); }

    /*!
     * \brief Returns an iterator to the first element of the container.
     *
     * \return Iterator to the first element.
     */
    const_iterator begin() const noexcept {
        return static_cast<const_iterator>(data());
    }

    /*!
     * \brief Returns an iterator to the one-past-the-last element of the
     * container.
     *
     * \return Iterator to the element following the last element.
     */
    iterator end() noexcept { return static_cast<iterator>(data() + size()); }

    /*!
     * \brief Returns an iterator to the one-past-the-last element of the
     * container.
     *
     * \return Iterator to the element following the last element.
     */
    const_iterator end() const noexcept {
        return static_cast<const_iterator>(data() + size());
    }

    /*!
     * \brief Returns a reverse iterator to the first element of the reversed
     * container.
     *
     * \return Reverse iterator to the first element.
     */
    reverse_iterator rbegin() noexcept { return reverse_iterator(begin()); }

    /*!
     * \brief Returns a reverse iterator to the first element of the reversed
     * container.
     *
     * \return Reverse iterator to the first element.
     */
    const_reverse_iterator rbegin() const noexcept {
        return reverse_iterator(begin());
    }

    /*!
     * \brief Returns a reverse iterator to the one-past-the-last element of the
     * reversed container.
     *
     * \return Reverse iterator to the element following the last element.
     */
    reverse_iterator rend() noexcept { return reverse_iterator(end()); }

    /*!
     * \brief Returns a reverse iterator to the one-past-the-last element of the
     * reversed container.
     *
     * \return Reverse iterator to the element following the last element.
     */
    const_reverse_iterator rend() const noexcept {
        return reverse_iterator(end());
    }

    /*!
     * \brief Returns an iterator to the first element of the container.
     *
     * \return Iterator to the first element.
     */
    const_iterator cbegin() const noexcept { return begin(); }

    /*!
     * \brief Returns an iterator to the one-past-the-last element of the
     * container.
     *
     * \return Iterator to the element following the last element.
     */
    const_iterator cend() const noexcept { return end(); }

    /*!
     * \brief Returns a reverse iterator to the first element of the reversed
     * container.
     *
     * \return Reverse iterator to the first element.
     */
    const_reverse_iterator crbegin() const noexcept { return rbegin(); }

    /*!
     * \brief Returns a reverse iterator to the one-past-the-last element of the
     * reversed container.
     *
     * \return Reverse iterator to the element following the last element.
     */
    const_reverse_iterator crend() const noexcept { return rend(); }

    /*!
     * \brief Checks whether the container has no elements.
     *
     * \return true if the container is empty, false otherwise.
     */
    bool empty() const noexcept { return size() == 0; }

    /*!
     * \brief Returns the number of rows in the container.
     *
     * \return The number of rows in the container.
     */
    size_type rows() const noexcept { return rows_; }

    /*!
     * \brief Returns the number of columns in the container.
     *
     * \return The number of columns in the container.
     */
    size_type columns() const noexcept { return columns_; }

    /*!
     * \brief Returns the number of elements in the container.
     *
     * \return The number of elements in the container.
     */
    size_type size() const noexcept { return rows_ * columns_; }

    /*!
     * \brief Returns the maximum number of elements in the container is able to
     * hold due to limitations.
     *
     * \return Maximum number of elements in the container.
     */
    size_type max_size() const noexcept {
        return std::allocator_traits<allocator_type>::max_size(
            this->allocator_);
    }

    /*!
     * \brief Returns the number of elements that the container has allocated
     * the space for.
     *
     * \return The capacity of the currently allocated storage.
     */
    size_type capacity() const noexcept { return base::capacity(); }

    /*!
     * \brief Resizes the container to `r` x `c` matrix.
     *
     * If `r == rows()` and `c == columns()`, nothing happens.
     *
     * If `rows()` is greater than `r`, the container rows number is reduced
     * to `r`. If `rows()` is less than `r`, additional `r - rows()`
     * copies of `v` are appended to the right of each row.
     *
     * If `columns()` is greater than `c`, the container columns number is
     * reduced to `c`. If `columns()` is less than `c`, additional `r -
     * columns()` copies of `v` are appended to the bottom of each column.
     *
     * If `r * c == size()`, no reallocations are done.
     *
     * \param r New number of rows of the container.
     * \param c New number of columns of the container.
     * \param v The value to initialize the new elements with.
     * \throws std::length_error If `r * c` exceeds `max_size()`.
     */
    void resize(size_type r, size_type c, const T& v = T()) {
        const auto n = r * c;
        if (size() != n) {
            matrix tmp(this->allocator_);
            if (n > 0) {
                tmp.allocate(n);
                tmp.rows_ = r;
                tmp.columns_ = c;
                for (size_type i = 0; i < std::min(rows(), r); ++i) {
                    auto row = (*this)[i];
                    auto tmp_row = tmp[i];
                    std::uninitialized_move_n(
                        row.begin(), std::min(columns(), c), tmp_row.begin());
                    std::uninitialized_fill_n(
                        tmp_row.begin() + std::min(columns(), c),
                        c - std::min(columns(), c), v);
                }
                for (size_type i = std::min(rows(), r); i < r; ++i) {
                    auto tmp_row = tmp[i];
                    std::uninitialized_fill_n(tmp_row.begin(), c, v);
                }
            }
            *this = std::move(tmp);
        } else if (r != rows()) {
            if (c > columns()) {
                for (size_type i = r; i > 0; --i) {
                    auto row = (*this)[i];
                    std::copy_n(row.begin(), columns(), data() + i * columns());
                }
                // const auto prev_rows = rows();
                const auto prev_columns = columns();
                rows_ = r;
                columns_ = c;
                for (size_type i = 0; i < r; ++i) {
                    auto row = (*this)[i];
                    std::fill_n(row.begin() + prev_columns,
                                columns() - prev_columns, v);
                }
            } else {
                for (size_type i = 1; i < rows(); ++i) {
                    auto row = (*this)[i];
                    std::copy_n(row.begin(), c, data() + i * c);
                }
                std::fill(data() + c * rows(), this->data_end_, v);
                rows_ = r;
                columns_ = c;
            }
        }
    }

    /*!
     * \brief Returns a reference to the element at (`row`, `column`).
     *
     * Returns a reference to the element at index (`row`, `column`).
     * No bounds checking is performed.
     *
     * \param row Row index of the element to return.
     * \param column Column index of the element to return.
     * \return Reference to the element.
     */
    reference operator()(size_type row, size_type column) {
        return *(data() + row * columns() + column);
    }

    /*!
     * \brief Returns a reference to the element at (`row`, `column`).
     *
     * Returns a reference to the element at index (`row`, `column`).
     * No bounds checking is performed.
     *
     * \param row Row index of the element to return.
     * \param column Column index of the element to return.
     * \return Reference to the element.
     */
    const_reference operator()(size_type row, size_type column) const {
        return *(data() + row * columns() + column);
    }

    /*!
     * \brief Returns a reference to the element at (`row`, `column`) with bound
     * checking.
     *
     * Returns a reference to the element at index (`row`, `column`).
     * If `row` is not within the range [`0`, `rows()`) or `column`
     * is not within the range [`0`, `columns()`), std::out_of_range is thrown.
     *
     * \param row Row index of the element to return.
     * \param column Column index of the element to return.
     * \return Reference to the element.
     * \throws std::out_of_range If `row >= rows()` or `column >= columns()`.
     */
    reference at(size_type row, size_type column) {
        if (row >= rows()) {
            throw std::out_of_range("matrix::at: row >= rows()");
        }
        if (column >= columns()) {
            throw std::out_of_range("matrix::at: column >= columns()");
        }
        return *(data() + row * columns() + column);
    }

    /*!
     * \brief Returns a reference to the element at (`row`, `column`) with bound
     * checking.
     *
     * Returns a reference to the element at index (`row`, `column`).
     * If `row` is not within the range [`0`, `rows()`) or `column`
     * is not within the range [`0`, `columns()`), std::out_of_range is thrown.
     *
     * \param row Row index of the element to return.
     * \param column Column index of the element to return.
     * \return Reference to the element.
     * \throws std::out_of_range If `row >= rows()` or `column >= columns()`.
     */
    const_reference at(size_type row, size_type column) const {
        if (row >= rows()) {
            throw std::out_of_range("matrix::at: row >= rows()");
        }
        if (column >= columns()) {
            throw std::out_of_range("matrix::at: column >= columns()");
        }
        return *(data() + row * columns() + column);
    }

    /*!
     * \brief Returns a pointer to the underlying data.
     *
     * \return Pointer to the underlying element storage.
     */
    T* data() noexcept { return this->data_; }

    /*!
     * \brief Returns a pointer to the underlying data.
     *
     * \return Pointer to the underlying element storage.
     */
    const T* data() const noexcept { return this->data_; }

    /*!
     * \brief Returns a row object representing the row at index `r` with bound
     * checking.
     *
     * Returns a row at index `r`.
     * If `r` is not within the range [`0`, `rows()`), std::out_of_range is
     * thrown.
     *
     * \param r The index of the row to access.
     * \return row A row object representing the row at index `r`.
     * \throws std::out_of_range If `r >= rows()`.
     */
    row at(size_type r) {
        if (r >= rows()) {
            throw std::out_of_range("matrix::at: r >= rows()");
        }
        return row(*this, r);
    }

    /*!
     * \brief Returns a row object representing the row at index `r` with bound
     * checking.
     *
     * Returns a row at index `r`.
     * If `r` is not within the range [`0`, `rows()`), std::out_of_range is
     * thrown.
     *
     * \param r The index of the row to access.
     * \return row A row object representing the row at index `r`.
     * \throws std::out_of_range If `r >= rows()`.
     */
    const_row at(size_type r) const {
        if (r >= rows()) {
            throw std::out_of_range("matrix::at: r >= rows()");
        }
        return const_row(*this, r);
    }

    /*!
     * \brief Returns a row object representing the row at index `r`.
     *
     * No bounds checking is performed.
     *
     * \param r The index of the row to access.
     * \return row A row object representing the row at index `r`.
     */
    row operator[](size_type r) { return row(*this, r); }

    /*!
     * \brief Returns a row object representing the row at index `r`.
     *
     * No bounds checking is performed.
     *
     * \param r The index of the row to access.
     * \return row A row object representing the row at index `r`.
     */
    const_row operator[](size_type r) const { return const_row(*this, r); }

    /*!
     * \brief Erases all elements from the container.
     */
    void clear() noexcept {
        base::deallocate();
        rows_ = 0;
        columns_ = 0;
    }

    /*!
     * \brief Swaps the contents and capacity of the container with `other`.
     *
     * Exchanges the contents and capacity of the container with those of
     * `other`. If
     * `std::allocator_traits<allocator_type>::propagate_on_container_swap::value`
     * is `true`, the allocators are swapped. Otherwise, the allocators are not
     * swapped. In that case, if `get_allocator != other.get_allocator()`,
     * the behavior is undefined.
     */
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

/*!
 * \brief Matrix row class.
 */
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

    /*!
     * \brief Copy constructor.
     *
     * \param other Row.
     */
    row_base(const row_base& other) noexcept = default;

    /*!
     * \brief Copy-assignment operator.
     *
     * \param other Row.
     */
    row_base& operator=(const row_base& other) noexcept = default;

    /*!
     * \brief Converts row to `const_row`.
     *
     * \return Constant representation of the row.
     */
    operator row_base<T, Allocator, true>() const {
        return row_base<T, Allocator, true>(matrix_.get(), row_);
    }

    /*!
     * \brief Returns an iterator to the first element of the row.
     *
     * \return Iterator to the first element.
     */
    iterator begin() noexcept {
        return static_cast<iterator>(matrix_.get().data() +
                                     matrix_.get().columns() * row_);
    }

    /*!
     * \brief Returns an iterator to the first element of the row.
     *
     * \return Iterator to the first element.
     */
    const_iterator begin() const noexcept {
        return static_cast<const_iterator>(matrix_.get().data() +
                                           matrix_.get().columns() * row_);
    }

    /*!
     * \brief Returns an iterator to the one-past-the-last element of the
     * row.
     *
     * \return Iterator to the element following the last element.
     */
    iterator end() noexcept {
        return static_cast<iterator>(matrix_.get().data() +
                                     matrix_.get().columns() * (row_ + 1));
    }

    /*!
     * \brief Returns an iterator to the one-past-the-last element of the
     * row.
     *
     * \return Iterator to the element following the last element.
     */
    const_iterator end() const noexcept {
        return static_cast<const_iterator>(
            matrix_.get().data() + matrix_.get().columns() * (row_ + 1));
    }

    /*!
     * \brief Returns a reverse iterator to the first element of the reversed
     * row.
     *
     * \return Reverse iterator to the first element.
     */
    reverse_iterator rbegin() noexcept { return reverse_iterator(begin()); }

    /*!
     * \brief Returns a reverse iterator to the first element of the reversed
     * row.
     *
     * \return Reverse iterator to the first element.
     */
    const_reverse_iterator rbegin() const noexcept {
        return reverse_iterator(begin());
    }

    /*!
     * \brief Returns a reverse iterator to the one-past-the-last element of the
     * reversed row.
     *
     * \return Reverse iterator to the element following the last element.
     */
    reverse_iterator rend() noexcept { return reverse_iterator(end()); }

    /*!
     * \brief Returns a reverse iterator to the one-past-the-last element of the
     * reversed row.
     *
     * \return Reverse iterator to the element following the last element.
     */
    const_reverse_iterator rend() const noexcept {
        return reverse_iterator(end());
    }

    /*!
     * \brief Returns an iterator to the first element of the row.
     *
     * \return Iterator to the first element.
     */
    const_iterator cbegin() const noexcept { return begin(); }

    /*!
     * \brief Returns an iterator to the one-past-the-last element of the
     * row.
     *
     * \return Iterator to the element following the last element.
     */
    const_iterator cend() const noexcept { return end(); }

    /*!
     * \brief Returns a reverse iterator to the first element of the reversed
     * row.
     *
     * \return Reverse iterator to the first element.
     */
    const_reverse_iterator crbegin() const noexcept { return rbegin(); }

    /*!
     * \brief Returns a reverse iterator to the one-past-the-last element of the
     * reversed row.
     *
     * \return Reverse iterator to the element following the last element.
     */
    const_reverse_iterator crend() const noexcept { return rend(); }

    /*!
     * \brief Returns a reference to the element at column with index `n`.
     *
     * Returns a reference to the element at column with index `n`.
     * No bounds checking is performed.
     *
     * \param n Column of the element to return.
     * \return Reference to the element.
     */
    reference operator[](difference_type n) { return matrix_(row_, n); }

    /*!
     * \brief Returns a reference to the element at column with index `n`.
     *
     * Returns a reference to the element at column with index `n`.
     * No bounds checking is performed.
     *
     * \param n Column of the element to return.
     * \return Reference to the element.
     */
    const_reference operator[](size_type n) const { return matrix_(row_, n); }

    /*!
     * \brief Checks whether the row has no elements.
     *
     * \return true if the row is empty, false otherwise.
     */
    bool empty() const noexcept { return (size() == 0); }

    /*!
     * \brief Returns the number of columns in the row.
     *
     * \return The number of columns in the row.
     */
    size_type size() const noexcept { return matrix_.get().columns(); }

    /*!
     * \brief Returns the number of columns matrix has.
     *
     * \return The capacity of the currently allocated storage.
     */
    size_type capacity() const noexcept { return matrix_.get().columns(); }

    /*!
     * \brief Returns the row index of this row in the matrix.
     *
     * \return The row index.
     */
    size_type row() const noexcept { return row_; }

    /*!
     * \brief Returns a reference to the element at `n` with bound checking.
     *
     * Returns a reference to the element at index `n`.
     * If `n` is not within the range [`0`, `size()`), std::out_of_range is
     * thrown.
     *
     * \param n Position of the element to return.
     * \return Reference to the element.
     * \throws std::out_of_range If `n >= size()`.
     */
    reference at(size_type n) {
        if (n >= size()) {
            throw std::out_of_range("matrix::row::at: n >= size()");
        }
        return matrix_(row_, n);
    }

    /*!
     * \brief Returns a reference to the element at `n` with bound checking.
     *
     * Returns a reference to the element at index `n`.
     * If `n` is not within the range [`0`, `size()`), std::out_of_range is
     * thrown.
     *
     * \param n Position of the element to return.
     * \return Reference to the element.
     * \throws std::out_of_range If `n >= size()`.
     */
    const_reference at(size_type n) const {
        if (n >= size()) {
            throw std::out_of_range("matrix::row::at: n >= size()");
        }
        return matrix_(row_, n);
    }

    /*!
     * \brief Returns a reference to the first element of the row.
     *
     * Returns a reference to the first element.
     *
     * \return Reference to the first element.
     */
    reference front() { return matrix_(row_, 0); }

    /*!
     * \brief Returns a reference to the first element of the row.
     *
     * Returns a reference to the first element.
     *
     * \return Reference to the first element.
     */
    const_reference front() const { return matrix_(row_, 0); }

    /*!
     * \brief Returns a reference to the last element of the row.
     *
     * Returns a reference to the last element.
     *
     * \return Reference to the last element.
     */
    reference back() { return matrix_(row_, matrix_.get().columns() - 1); }

    /*!
     * \brief Returns a reference to the last element of the row.
     *
     * Returns a reference to the last element.
     *
     * \return Reference to the last element.
     */
    const_reference back() const {
        return matrix_(row_, matrix_.get().columns() - 1);
    }

    /*!
     * \brief Swaps the matrix and row index of the row with `other`.
     *
     * Exchanges the matrix and row index of the row with those of
     * `other`.
     */
    void swap(row_base& other) noexcept {
        std::swap(matrix_, other.matrix_);
        std::swap(row_, other.row_);
    }

private:
    std::reference_wrapper<matrix_type> matrix_;
    size_type row_;
};

/*!
 * \brief Compares two matrices for equality.
 *
 * \param lhs A matrix.
 * \param rhs A matrix.
 * \return `true` if the numbers of rows and columns and elements
 *          of matrices are equal, false otherwise.
 */
template <class T, class Allocator>
inline bool operator==(const matrix<T, Allocator>& lhs,
                       const matrix<T, Allocator>& rhs) {
    return lhs.columns() == rhs.columns() && lhs.rows() == rhs.rows() &&
           std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

/*!
 * \brief Compares two rows for equality.
 *
 * \param lhs A row.
 * \param rhs A row.
 * \return `true` if sizes and elements
 *          of rows are equal, false otherwise.
 */
template <class T, class Allocator, bool IsConstL, bool IsConstR>
inline bool operator==(const row_base<T, Allocator, IsConstL>& lhs,
                       const row_base<T, Allocator, IsConstR>& rhs) {
    return lhs.size() == rhs.size() &&
           std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

/*!
 * See `bpns::matrix::swap()`
 */
template <class T, class Allocator>
void swap(matrix<T, Allocator>& lhs,
          matrix<T, Allocator>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
    lhs.swap(rhs);
}

/*!
 * See `bpns::row_base::swap()`
 */
template <class T, class Allocator, bool IsConst>
void swap(
    row_base<T, Allocator, IsConst>& lhs,
    row_base<T, Allocator, IsConst>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
    lhs.swap(rhs);
}

}  // namespace bpns

#endif  // !MATRIX_MATRIX_HPP_
