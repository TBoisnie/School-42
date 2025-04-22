
#ifndef UTILS_HPP
# define UTILS_HPP

# include <cmath>
# include <type_traits>
# include "Complex.hpp"

template<typename K>
class Complex;

// #############################################################################
// Is Complex Trait
// #############################################################################
// https://stackoverflow.com/questions/41438493/how-to-identifying-whether-a-template-argument-is-stdcomplex
template<typename T>
struct is_complex_t : public std::false_type {};

template<typename T>
struct is_complex_t<Complex<T>> : public std::true_type {};

template<typename T>
constexpr bool is_complex() { return is_complex_t<T>::value; }


// #############################################################################
// Fused Multiply Add (FMA)
// #############################################################################
template<typename K = float>
K fused_multiply_add(K const & x, K const & y, K const & z)
{
    static_assert(std::is_arithmetic<K>::value, "fused_multiply_add(): Unsupported template type.");

    return std::fma(x, y, z);
}

template<typename K>
Complex<K> fused_multiply_add(
    Complex<K> const & u,
    Complex<K> const & v,
    Complex<K> const & z
)
{
    return Complex<K>(
        fused_multiply_add(u.re(), v.re(), fused_multiply_add(-u.im(), v.im(), z.re())),
        fused_multiply_add(u.re(), v.im(), fused_multiply_add( u.im(), v.re(), z.im()))
    );
}

// #############################################################################
// Abs
// #############################################################################
template<typename T>
T abs(T const value)
{
    return std::max(-value, value);
}

template<typename T>
T abs(Complex<T> const & value)
{
    return std::pow(value.re() * value.re() + value.im() * value.im(), 0.5f);
}

#endif
