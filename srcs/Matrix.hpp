
#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <algorithm>
# include <cassert>
# include <initializer_list>
# include <iostream>
# include <sstream>
# include <stdexcept>
# include <vector>
# include "Vector.hpp"


template<typename K = float>
class Matrix
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

    using t_self = Matrix<K>;


    // - Attributes ------------------------------------------------------------
    // - Constructors & Destructor & Copy --------------------------------------
    Matrix(t_size const rows, t_size const columns)
        : m_rows(rows), m_columns(columns), m_elements(rows * columns)
    {
        assert(0 < this->rows() && 0 < this->columns());
    }

    Matrix(t_size const rows, t_size const columns, std::initializer_list<t_element> const & elements)
        : m_rows(rows), m_columns(columns), m_elements(elements)
    {
        assert(0 < this->rows() && 0 < this->columns());
        assert(this->rows() * this->columns() == m_elements.size());
    }

    Matrix(t_self const & other)
        : m_rows(other.rows()), m_columns(other.columns())
    {
        *this = other;
    }

    ~Matrix()
    {
        // Do nothing
    }

    t_self & operator=(t_self const & other)
    {
        if (this == &other)
            return *this;

        assert(rows() == other.rows());
        assert(columns() == other.columns());

        m_elements = other.m_elements;

        return *this;
    }

    // - Operators -------------------------------------------------------------
    t_reference operator()(t_size const row, t_size const column)
    {
        return m_elements[_getPosition(row, column)];
    }

    t_reference_const operator()(t_size const row, t_size const column) const
    {
        return m_elements[_getPosition(row, column)];
    }

    // - Methods ---------------------------------------------------------------
    t_self & add(t_self const & other)
    {
        assert(rows() == other.rows());
        assert(columns() == other.columns());

        for (t_size i = 1; i <= rows(); ++i)
        {
            for (t_size j = 1; j <= columns(); ++j)
            {
                (*this)(i, j) += other(i, j);
            }
        }

        return *this;
    }

    t_self & sub(t_self const & other)
    {
        assert(rows() == other.rows());
        assert(columns() == other.columns());

        for (t_size i = 1; i <= rows(); ++i)
        {
            for (t_size j = 1; j <= columns(); ++j)
            {
                (*this)(i, j) -= other(i, j);
            }
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

    // https://en.wikipedia.org/wiki/Matrix_multiplication
    Vector<t_element> mul_vec(Vector<t_element> const & v)
    {
        assert(columns() == v.size());

        Vector<t_element> result(rows());

        for (t_size i = 1; i <= rows(); ++i)
        {
            for (t_size j = 1; j <= columns(); ++j)
            {
                result(i) = fused_multiply_add((*this)(i, j), v(j), result(i));
            }
        }

        return result;
    }

    // https://en.wikipedia.org/wiki/Matrix_multiplication
    t_self mul_mat(t_self const & other)
    {
        assert(columns() == other.rows());

        t_self result(rows(), other.columns());

        for (t_size k = 1; k <= other.columns(); ++k)
        {
            for (t_size i = 1; i <= rows(); ++i)
            {
                for (t_size j = 1; j <= columns(); ++j)
                {
                    result(i, k) = fused_multiply_add((*this)(i, j), other(j, k), result(i, k));
                }
            }
        }

        return result;
    }

    // https://en.wikipedia.org/wiki/Trace_(linear_algebra)
    t_element trace() const
    {
        assert(isSquare());

        t_element result = t_element();

        for (t_size i = 1; i <= rows(); ++i)
        {
            result += (*this)(i, i);
        }

        return result;
    }

    // https://en.wikipedia.org/wiki/Transpose
    t_self transpose() const
    {
        t_self result(columns(), rows());

        for (t_size i = 1; i <= rows(); ++i)
        {
            for (t_size j = 1; j <= columns(); ++j)
            {
                result(j, i) = (*this)(i, j);
            }
        }

        return result;
    }

    //https://en.wikipedia.org/wiki/Row_echelon_form
    t_self row_echelon() const
    {
        t_self result(*this);

        t_element null_element = t_element();

        t_size lead = 1;

        for (t_size r = 1; r <= rows(); ++r)
        {
            if (lead > columns())
                break ;

            t_size i = r;

            while (result(i, lead) == null_element)
            {
                i += 1;

                if (i > rows())
                {
                    i = r;
                    lead += 1;

                    if (lead > columns())
                        return result;
                }
            }

            result._swapRows(i, r);

            if (result(r, lead) != null_element)
            {
                result._divRow(r, result(r, lead));
            }

            for (i = 1; i <= rows(); ++i)
            {
                if (i != r)
                {
                    result._subMulRow(i, r, result(i, lead));
                }
            }

            lead += 1;
        }

        return result;
    }

    // https://en.wikipedia.org/wiki/Determinant
    // https://en.wikipedia.org/wiki/LU_decomposition
    t_element determinant() const
    {
        assert(isSquare());

        if (rows() == 1)
        {
            return (*this)(1, 1);
        }

        if (rows() == 2)
        {
            return (*this)(1, 1) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 1);
        }

        if (rows() == 3)
        {
            return
                  (*this)(1, 1) * ((*this)(2, 2) * (*this)(3, 3) - (*this)(2, 3) * (*this)(3, 2))
                - (*this)(1, 2) * ((*this)(2, 1) * (*this)(3, 3) - (*this)(2, 3) * (*this)(3, 1))
                + (*this)(1, 3) * ((*this)(2, 1) * (*this)(3, 2) - (*this)(2, 2) * (*this)(3, 1))
            ;
        }

        int sign = 1;
        t_element det = t_element();

        for (t_size j = 1; j <= columns(); ++j)
        {
            det += (*this)(1, j) * sign * _copySubMatrix(1, j).determinant();
            sign *= -1;
        }

        return det;
    }

    // https://en.wikipedia.org/wiki/Invertible_matrix
    t_self inverse() const
    {
        assert(isSquare());

        t_element null_element = t_element();
        t_element det = determinant();

        if (det == null_element)
            throw std::runtime_error("Matrix::inverse(): Can not get inverse of a singular matrix (determinant = 0).");

        return _adjugate().transpose().scl(t_element(1) / det);
    }

    // https://en.wikipedia.org/wiki/Rank_(linear_algebra)
    t_size rank() const
    {
        t_self simplified(row_echelon());

        t_element null_element = t_element();
        t_size r = 0;

        for (t_size i = 1; i <= rows(); ++i)
        {
            for (t_size j = 1; j <= columns(); ++j)
            {
                if (simplified(i, j) != null_element)
                {
                    r += 1;
                    break ;
                }
            }
        }

        return r;
    }

    // - Getters & Setters -----------------------------------------------------
    t_size rows() const
    {
        return m_rows;
    }

    t_size columns() const
    {
        return m_columns;
    }

    bool isSquare() const
    {
        return rows() == columns();
    }

    // - Friends ---------------------------------------------------------------
    template<typename T>
    friend std::ostream & operator<<(std::ostream & os, Matrix<T> const & matrix);

// #############################################################################
// Protected
// #############################################################################
protected:
    // - Types -----------------------------------------------------------------
    // - Attributes ------------------------------------------------------------
    t_size const m_rows;
    t_size const m_columns;
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
    t_size _getPosition(t_size const row, t_size const column) const
    {
        assert(1 <= row && row <= rows());
        assert(1 <= column && column <= columns());

        return (row - 1) * columns() + (column - 1);
    }

    void _swapRows(t_size const x, t_size const y)
    {
        if (x == y)
            return ;

        auto x_begin = m_elements.begin() + _getPosition(x, 1);
        auto y_begin = m_elements.begin() + _getPosition(y, 1);

        std::swap_ranges(x_begin, x_begin + columns(), y_begin);
    }

    void _divRow(t_size const i, t_element divider)
    {
        for (t_size j = 1; j <= columns(); ++j)
        {
            (*this)(i, j) /= divider;
        }
    }

    void _subMulRow(t_size const x, t_size const y, t_element multiplier)
    {
        for (t_size j = 1; j <= columns(); ++j)
        {
            (*this)(x, j) = fused_multiply_add((*this)(y, j), -multiplier, (*this)(x, j));
        }
    }

    t_self _copySubMatrix(t_size const skip_row, t_size const skip_column) const
    {
        t_size new_rows    = rows()    - 1 * (0 < skip_row && skip_row <= rows());
        t_size new_columns = columns() - 1 * (0 < skip_column && skip_column <= columns());

        t_self mat(new_rows, new_columns);

        for (t_size i = 1; i <= rows(); ++i)
        {
            if (i == skip_row)
                continue ;

            for (t_size j = 1; j <= columns(); ++j)
            {
                if (j == skip_column)
                    continue ;

                t_size new_i = i - 1 * (i > skip_row);
                t_size new_j = j - 1 * (j > skip_column);

                mat(new_i, new_j) = (*this)(i, j);
            }
        }

        return mat;
    }

    // https://en.wikipedia.org/wiki/Adjugate_matrix
    t_self _adjugate() const
    {
        t_self mat(rows(), columns());

        int sign = 1;
        for (t_size i = 1; i <= rows(); ++i)
        {
            for (t_size j = 1; j <= columns(); ++j)
            {
                mat(i, j) = _copySubMatrix(i, j).determinant() * sign;
                sign *= -1;
            }
        }

        return mat;
    }
};

// #############################################################################
// Overloadings
// #############################################################################
template<typename T>
std::ostream & operator<<(std::ostream & os, Matrix<T> const & matrix)
{
    using t_size = typename Matrix<T>::t_size;

    for (t_size i = 1; i <= matrix.rows(); ++i)
    {
        os << "[ ";
        for (t_size j = 1; j <= matrix.columns(); ++j)
        {
            os << matrix(i, j) << " ";
        }
        os << "]\n";
    }

    return os;
}

#endif
