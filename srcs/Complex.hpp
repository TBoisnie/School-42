
#ifndef COMPLEX_HPP
# define COMPLEX_HPP

# include <cassert>
# include <initializer_list>
# include <iostream>
# include "Utils.hpp"


template<typename K = float>
class Complex
{
// #############################################################################
// Public
// #############################################################################
public:
    // - Types -----------------------------------------------------------------
    using t_element = K;

    using t_pointer   = K *;
    using t_reference = K &;
    using t_pointer_const   = K const *;
    using t_reference_const = K const &;

    using t_self = Complex<K>;

    // - Attributes ------------------------------------------------------------
    // - Constructors & Destructor & Copy --------------------------------------
    Complex(t_element const re = t_element(), t_element const im = t_element())
        : m_re(re), m_im(im)
    {
        // Do nothing
    }

    Complex(std::initializer_list<t_element> const & values)
        : Complex()
    {
        assert(values.size() <= 2);

        decltype(values.begin()) value = values.begin();

        if (value != values.end()) m_re = *value++;
        if (value != values.end()) m_im = *value++;
    }

    Complex(t_self const & other)
    {
        *this = other;
    }

    ~Complex()
    {
        // Do nothing
    }

    t_self & operator=(t_self const & other)
    {
        if (this == &other)
            return *this;

        m_re = other.re();
        m_im = other.im();

        return *this;
    }

    // - Operators -------------------------------------------------------------
    t_self operator-() const
    {
        return t_self(-re(), -im());
    }

    t_self & operator+=(t_self const & other)
    {
        m_re += other.re();
        m_im += other.im();

        return *this;
    }

    t_self & operator-=(t_self const & other)
    {
        return *this += -other;
    }

    t_self & operator*=(t_self const & other)
    {
        *this = fused_multiply_add(*this, other, t_self());

        return *this;
    }

    t_self & operator*=(t_element const scale)
    {
        m_re *= scale;
        m_im *= scale;

        return *this;
    }

    t_self & operator/=(t_self const & other)
    {
        *this  = fused_multiply_add(*this, other.conj(), t_self());
        *this /= fused_multiply_add(other, other.conj(), t_self()).re();

        return *this;
    }

    t_self & operator/=(t_element const & div)
    {
        t_element null_element = t_element();

        assert(div != null_element);

        m_re /= div;
        m_im /= div;

        return *this;
    }

    t_self operator+(t_self const & rhs) const
    {
        t_self result = *this;

        result += rhs;

        return result;
    }

    t_self operator-(t_self const & rhs) const
    {
        t_self result = *this;

        result -= rhs;

        return result;
    }

    t_self operator*(t_self const & rhs) const
    {
        t_self result = *this;

        result *= rhs;

        return result;
    }

    t_self operator*(t_element const & rhs) const
    {
        t_self result = *this;

        result *= rhs;

        return result;
    }

    t_self operator/(t_self const & rhs) const
    {
        t_self result = *this;

        result /= rhs;

        return result;
    }

    t_self operator/(t_element const & rhs) const
    {
        t_self result = *this;

        result /= rhs;

        return result;
    }

    bool operator==(t_self const & other) const
    {
        return re() == other.re() && im() == other.im();
    }

    bool operator!=(t_self const & other) const
    {
        return !(*this == other);
    }

    // - Methods ---------------------------------------------------------------
    t_self conj() const
    {
        return t_self(re(), -im());
    }

    // - Getters & Setters -----------------------------------------------------
    t_element re() const
    {
        return m_re;
    }

    t_element im() const
    {
        return m_im;
    }

    // - Friends ---------------------------------------------------------------
    template<typename T>
    friend std::ostream & operator<<(std::ostream & os, Complex<T> const & complex);

// #############################################################################
// Protected
// #############################################################################
protected:
    // - Types -----------------------------------------------------------------
    // - Attributes ------------------------------------------------------------
    // - Constructors & Destructor & Copy --------------------------------------
    // - Operators -------------------------------------------------------------
    // - Methods ---------------------------------------------------------------
    // - Getters & Setters -----------------------------------------------------


// #############################################################################
// Private
// #############################################################################
private:
    // - Types -----------------------------------------------------------------
    // - Attributes ------------------------------------------------------------
    t_element m_re;
    t_element m_im;

    // - Constructors & Destructor & Copy --------------------------------------
    // - Operators -------------------------------------------------------------
    // - Methods ---------------------------------------------------------------
    // - Getters & Setters -----------------------------------------------------
};

// #############################################################################
// Overloadings
// #############################################################################
template<typename T>
std::ostream & operator<<(std::ostream & os, Complex<T> const & complex)
{
    os << complex.re() << std::showpos << complex.im() << "i" << std::noshowpos;
    return os;
}

#endif
