
#include <iostream>
#include <iomanip>
#include "../srcs/Complex.hpp"
#include "../srcs/Functions.hpp"
#include "../srcs/Matrix.hpp"
#include "../srcs/Vector.hpp"


int main( void )
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-- 07 - Mul Vec / Mat ----------------------------------------------------------" << std::endl;

    // #########################################################################
    // Subject (Float)
    // #########################################################################
    std::cout << "- Float ------------------------------- " << std::endl;
    {
        Matrix<> u(2, 2, {
            1, 0,
            0, 1
        });
        Vector<> v({ 4, 2 });

        std::cout << u.mul_vec(v) << std::endl;
    }
    {
        Matrix<> u(2, 2, {
            2, 0,
            0, 2
        });
        Vector<> v({ 4, 2 });

        std::cout << u.mul_vec(v) << std::endl;
    }
    {
        Matrix<> u(2, 2, {
            2, -2,
            -2, 2
        });
        Vector<> v({ 4, 2 });

        std::cout << u.mul_vec(v) << std::endl;
    }
    {
        Matrix<> u(2, 2, {
            1, 0,
            0, 1
        });
        Matrix<> v(2, 2, {
            1, 0,
            0, 1
        });

        std::cout << u.mul_mat(v) << std::endl;
    }
    {
        Matrix<> u(2, 2, {
            1, 0,
            0, 1
        });
        Matrix<> v(2, 2, {
            2, 1,
            4, 2
        });

        std::cout << u.mul_mat(v) << std::endl;
    }
    {
        Matrix<> u(2, 2, {
            3, -5,
            6, 8
        });
        Matrix<> v(2, 2, {
            2, 1,
            4, 2
        });

        std::cout << u.mul_mat(v) << std::endl;
    }

    // #########################################################################
    // Bonus (Complex)
    // #########################################################################
    std::cout << "- Complex ----------------------------- " << std::endl;
    {
        Matrix<Complex<>> u(2, 2, {
            { 1, 1 }, { 0, 0 },
            { 0, 0 }, { 1, 1 }
        });
        Vector<Complex<>> v({ { 4, 4 }, { 2, 2 } });

        std::cout << u.mul_vec(v) << std::endl;
    }
    {
        Matrix<Complex<>> u(2, 2, {
            { 2, 2 }, { 0, 0 },
            { 0, 0 }, { 2, 2 }
        });
        Vector<Complex<>> v({ { 4, 4 }, { 2, 2 } });

        std::cout << u.mul_vec(v) << std::endl;
    }
    {
        Matrix<Complex<>> u(2, 2, {
            { 2, 2 }, { -2, -2 },
            { -2, -2 }, { 2, 2 }
        });
        Vector<Complex<>> v({ { 4, 4 }, { 2, 2 } });

        std::cout << u.mul_vec(v) << std::endl;
    }
    {
        Matrix<Complex<>> u(2, 2, {
            { 1, 1 }, { 0, 0 },
            { 0, 0 }, { 1, 1 }
        });
        Matrix<Complex<>> v(2, 2, {
            { 1, 1 }, { 0, 0 },
            { 0, 0 }, { 1, 1 }
        });

        std::cout << u.mul_mat(v) << std::endl;
    }
    {
        Matrix<Complex<>> u(2, 2, {
            { 1, 1 }, { 0, 0 },
            { 0, 0 }, { 1, 1 }
        });
        Matrix<Complex<>> v(2, 2, {
            { 2, 2 }, { 1, 1 },
            { 4, 4 }, { 2, 2 }
        });

        std::cout << u.mul_mat(v) << std::endl;
    }
    {
        Matrix<Complex<>> u(2, 2, {
            { 3, 3 }, { -5, -5 },
            { 6, 6 }, { 8, 8 }
        });
        Matrix<Complex<>> v(2, 2, {
            { 2, 2 }, { 1, 1 },
            { 4, 4 }, { 2, 2 }
        });

        std::cout << u.mul_mat(v) << std::endl;
    }

    return 0;
}
