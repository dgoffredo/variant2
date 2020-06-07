#pragma once

#include <cassert>
#include <type_traits>
#include <utility>

// A `variant2_t` is a variant type, i.e. a discriminated union, of two
// distinct types `T1` and `T2`. A `variant2_t<T1, T2>` holds _either_ a `T1`
// _or_ a `T2`, but never both and never neither.
// Construct a `variant2_t` with a `T1` or a `T2`, and access the value using
// the `visit` member functions. Change the value using assignment.
template <typename T1, typename T2>
class variant2_t {
    static_assert(!std::is_same<T1, T2>::value,
                  "variant2_t type arguments must be distinct");

    enum selector_t {
        FIRST,
        SECOND
    };
 
    selector_t which;

    union {
        T1 first;
        T2 second;
    };

  public:
    variant2_t(const T1& first)
    : which(FIRST)
    , first(first) {}

    variant2_t(const T2& second)
    : which(SECOND)
    , second(second) {}

    variant2_t(T1&& first)
    : which(FIRST)
    , first(std::move(first)) {}

    variant2_t(T2&& second)
    : which(SECOND)
    , second(std::move(second)) {}

    variant2_t(const variant2_t& other) {
        switch (other.which) {
        case FIRST:
            new (this) variant2_t(other.first);
            break;
        default:
            assert(other.which == SECOND);
            new (this) variant2_t(other.second);
        }
    }

    variant2_t(variant2_t&& other) {
        switch (other.which) {
        case FIRST:
            new (this) variant2_t(std::move(other.first));
            break;
        default:
            assert(other.which == SECOND);
            new (this) variant2_t(std::move(other.second));
        }
    }

    variant2_t& operator=(T1 value) {
        this->~variant2_t();
        new (this) variant2_t(std::move(value));
        return *this;
    }

    variant2_t& operator=(T2 value) {
        this->~variant2_t();
        new (this) variant2_t(std::move(value));
        return *this;
    }

    variant2_t& operator=(const variant2_t& other) {
        this->~variant2_t();
        new (this) variant2_t(other);
    }

    variant2_t& operator=(variant2_t&& other) {
        this->~variant2_t();
        new (this) variant2_t(std::move(other));
    }

    ~variant2_t() {
        switch (which) {
        case FIRST:
            first.~T1();
            break;
        default:
            assert(which == SECOND);
            second.~T2();
        }
    }

    template <typename visitor_func_t>
    void visit(visitor_func_t&& func) const {
        switch (which) {
        case FIRST:
            func(first);
            break;
        default:
            assert(which == SECOND);
            func(second);
        }
    }

    template <typename first_visitor_func_t, typename second_visitor_func_t>
    void visit(first_visitor_func_t&& func1, second_visitor_func_t&& func2) const {
        switch (which) {
        case FIRST:
            func1(first);
            break;
        default:
            assert(which == SECOND);
            func2(second);
        }
    }

    // These are the same as the two `visit` above, but without the `const`.
    template <typename visitor_func_t>
    void visit(visitor_func_t&& func) {
        switch (which) {
        case FIRST:
            func(first);
            break;
        default:
            assert(which == SECOND);
            func(second);
        }
    }

    template <typename first_visitor_func_t, typename second_visitor_func_t>
    void visit(first_visitor_func_t&& func1, second_visitor_func_t&& func2) {
        switch (which) {
        case FIRST:
            func1(first);
            break;
        default:
            assert(which == SECOND);
            func2(second);
        }
    }
};
