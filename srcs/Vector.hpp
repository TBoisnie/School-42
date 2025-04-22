
#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cassert>
# include <initializer_list>
# include <sstream>
# include <type_traits>
# include <vector>
# include "Utils.hpp"


template<typename K = float>
class Vector
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

    using t_container = std::vector<K>;
    using t_size = typename t_container::size_type;

    using t_self = Vector<K>;

    // - Attributes ------------------------------------------------------------
    // - Constructors & Destructor & Copy --------------------------------------
    Vector(t_size const size)
        : m_elements(size)
    {
        assert(0 < this->size());
    }

    Vector(std::initializer_list<t_element> const & elements)
        : m_elements(elements)
    {
        assert(0 < this->size());
    }

    Vector(t_self const & other)
    {
        *this = other;
    }

    ~Vector()
    {
        // Do nothing
    }

    t_self & operator=(t_self const & other)
    {
        if (this == &other)
            return *this;

        m_elements = other.m_elements;

        return *this;
    }

    // - Operators -------------------------------------------------------------
    t_reference operator()(t_size const index)
    {
        return m_elements[_getPosition(index)];
    }

    t_reference_const operator()(t_size const index) const
    {
        return m_elements[_getPosition(index)];
    }

    // - Methods ---------------------------------------------------------------
    t_self & add(t_self const & other)
    {
        assert(size() == other.size());

        for (t_size i = 1; i <= size(); ++i)
        {
            (*this)(i) += other(i);
        }

        return *this;
    }

    t_self & sub(t_self const & other)
    {
        assert(size() == other.size());

        for (t_size i = 1; i <= size(); ++i)
        {
            (*this)(i) -= other(i);
        }

        return *this;
    }

    t_self & scl(t_element const scale)
    {
        for (auto & element : m_elements)
        {
            element *= scale;
        }

        return *this;
    }

    // https://en.wikipedia.org/wiki/Dot_product
    template<typename T = K, typename = std::enable_if_t<!is_complex_t<T>::value>>
    t_element dot(Vector<K> const & other) const
    {
        assert(size() == other.size());

        t_element result = t_element();

        for (t_size i = 1; i <= size(); ++i)
            result = fused_multiply_add((*this)(i), other(i), result);

        return result;
    }

    // https://en.wikipedia.org/wiki/Dot_product#Complex_vectors
    template<typename T = K, typename = std::enable_if_t<is_complex_t<T>::value>>
    typename T::t_element dot(Vector<T> const & other) const
    {
        assert(size() == other.size());

        t_element result = t_element();
        for (t_size i = 1; i <= size(); ++i)
            result = fused_multiply_add((*this)(i), other(i).conj(), result);

        return result.re();
    }

    // https://en.wikipedia.org/wiki/Norm_(mathematics)#Taxicab_norm_or_Manhattan_norm
    float norm_1() const
    {
        float result = 0.0f;

        for (auto const & element : m_elements)
            result += static_cast<float>(abs(element));

        return result;
    }

    // https://en.wikipedia.org/wiki/Norm_(mathematics)#Euclidean_norm
    float norm() const
    {
        float result = 0.0f;

        for (auto const & element : m_elements)
            result = fused_multiply_add(
                static_cast<float>(abs(element)),
                static_cast<float>(abs(element)),
                result
            );

        return std::pow(result, .5f);
    }

    // https://en.wikipedia.org/wiki/Norm_(mathematics)#p-norm
    float norm_inf() const
    {
        float result = 0.0f;

        for (auto const & element : m_elements)
            result = std::max(static_cast<float>(abs(element)), result);

        return abs(result);
    }

    // - Getters & Setters -----------------------------------------------------
    t_size size() const
    {
        return m_elements.size();
    }

    // - Friends ---------------------------------------------------------------
    template<typename T>
    friend std::ostream & operator<<(std::ostream & os, Vector<T> const & vector);

// #############################################################################
// Protected
// #############################################################################
protected:
    // - Types -----------------------------------------------------------------
    // - Attributes ------------------------------------------------------------
    t_container m_elements;

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
    // - Constructors & Destructor & Copy --------------------------------------
    // - Operators -------------------------------------------------------------
    // - Methods ---------------------------------------------------------------
    // - Getters & Setters -----------------------------------------------------
    t_size _getPosition(t_size const index) const
    {
        assert(1 <= index && index <= size());
        return index - 1;
    }
};

// #############################################################################
// Overloadings
// #############################################################################
template<typename T>
std::ostream & operator<<(std::ostream & os, Vector<T> const & vector)
{
    os << "[ ";
    for (auto const & element : vector.m_elements)
    {
        os << element << " ";
    }
    os << "]\n";

    return os;
}

#endif
