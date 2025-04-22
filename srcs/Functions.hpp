
#ifndef FUNCTIONS_HPP
# define FUNCTIONS_HPP

# include <cmath>
# include "Matrix.hpp"
# include "Utils.hpp"
# include "Vector.hpp"

# define PI 3.14159265359f

// #############################################################################
// Linear Combination
// #############################################################################
// https://en.wikipedia.org/wiki/Linear_combination
template<typename V = Vector<>, typename K = typename Vector<>::t_element>
V linear_combination(
    std::initializer_list<V const> const & vectors,
    std::initializer_list<K> const & coefs
)
{
    assert(0 < vectors.size());
    assert(vectors.size() == coefs.size());

    V result((*vectors.begin()).size());

    decltype(vectors.begin()) vector = vectors.begin();
    decltype(coefs.begin()) coef = coefs.begin();

    while (vector != vectors.end())
    {
        for (decltype(vector->size()) i = 1; i <= vector->size(); ++i)
        {
            result(i) = fused_multiply_add(*coef, (*vector)(i), result(i));
        }

        ++vector;
        ++coef;
    }

    return result;
}

// #############################################################################
// Linear Interpolation
// #############################################################################
// https://en.wikipedia.org/wiki/Linear_interpolation
template<typename K = float>
K lerp(K const & u, K const & v, float const t)
{
    static_assert(std::is_arithmetic<K>::value || is_complex_t<K>::value, "lerp(): Unsupported template type.");

    return fused_multiply_add(K(t), v - u, u);
}

template<typename K>
Vector<K> lerp(Vector<K> const & u, Vector<K> const & v, float const t)
{
    assert(u.size() == v.size());

    Vector<K> result(u.size());

    for (Vector<>::t_size i = 1; i <= result.size(); ++i)
    {
        result(i) = lerp(u(i), v(i), t);
    }

    return result;
}

template<typename K>
Matrix<K> lerp(Matrix<K> const & u, Matrix<K> const & v, float const t)
{
    assert(u.rows() == v.rows());
    assert(u.columns() == v.columns());

    Matrix<K> result(u.rows(), u.columns());

    for (Matrix<>::t_size i = 1; i <= result.rows(); ++i)
    {
        for (Matrix<>::t_size j = 1; j <= result.columns(); ++j)
        {
            result(i, j) = lerp(u(i, j), v(i, j), t);
        }
    }

    return result;
}

// #############################################################################
// Cosine
// #############################################################################
template<typename K>
float angle_cos(Vector<K> const & u, Vector<K> const & v)
{
    assert(u.norm() != 0.f);
    assert(v.norm() != 0.f);

    return u.dot(v) / (u.norm() * v.norm());
}

// #############################################################################
// Cross Product
// #############################################################################
template<typename K>
Vector<K> cross_product(Vector<K> const & u, Vector<K> const & v)
{
    assert(u.size() == 3);
    assert(u.size() == v.size());

    Vector<K> w(u.size());

    w(1) = fused_multiply_add(u(2), v(3), fused_multiply_add(-v(2), u(3), w(1)));
    w(2) = fused_multiply_add(u(3), v(1), fused_multiply_add(-v(3), u(1), w(2)));
    w(3) = fused_multiply_add(u(1), v(2), fused_multiply_add(-v(1), u(2), w(3)));

    return w;
}

// #############################################################################
// Projection
// #############################################################################
// https://www.youtube.com/watch?v=ih20l3pJoeU
Matrix<> projection(float const fov, float const ratio, float const near, float const far)
{
    Matrix<> proj(4, 4);

    float fov_radian = fov / 180.f * PI;
    float f = 1.f / std::tan(fov_radian / 2.f);
    float q = far / (far - near);

    proj(1, 1) = ratio * f;
    proj(2, 2) = f;
    proj(3, 3) = q;
    proj(3, 4) = 1.f;
    proj(4, 3) = -near * q;

    return proj;
}

#endif
