
#include <iostream>
#include <iomanip>
#include "../srcs/Complex.hpp"
#include "../srcs/Functions.hpp"
#include "../srcs/Matrix.hpp"
#include "../srcs/Vector.hpp"


int main( void )
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-- 11 - Determinant ------------------------------------------------------------" << std::endl;

    // #########################################################################
    // Subject (Float)
    // #########################################################################
    std::cout << "- Float ------------------------------- " << std::endl;
    {
        Matrix<> u(2, 2, {
            1, -1,
            -1, 1,
        });

        std::cout << u.determinant() << std::endl;
    }
    {
        Matrix<> u(3, 3, {
            2, 0, 0,
            0, 2, 0,
            0, 0, 2
        });

        std::cout << u.determinant() << std::endl;
    }
    {
        Matrix<> u(3, 3, {
            8, 5, -2,
            4, 7, 20,
            7, 6, 1
        });

        std::cout << u.determinant() << std::endl;
    }
    {
        Matrix<> u(4, 4, {
            8, 5, -2, 4,
            4, 2.5, 20, 4,
            8, 5, 1, 4,
            28, -4, 17, 1
        });

        std::cout << u.determinant() << std::endl;
    }

    // #########################################################################
    // Bonus (Complex)
    // #########################################################################
    std::cout << "- Complex ----------------------------- " << std::endl;
    {
        Matrix<Complex<>> u(2, 2, {
            { 1, 1 }, { -1, -1 },
            { -1, -1 }, { 1, 1 }
        });

        std::cout << u.determinant() << std::endl;
    }
    {
        Matrix<Complex<>> u(3, 3, {
            { 2, 2 }, { 0, 0 }, { 0, 0 },
            { 0, 0 }, { 2, 2 }, { 0, 0 },
            { 0, 0 }, { 0, 0 }, { 2, 2 },
        });

        std::cout << u.determinant() << std::endl;
    }
    {
        Matrix<Complex<>> u(3, 3, {
            { 8, 8 }, { 5, 5 }, { -2, -2 },
            { 4, 4 }, { 7, 7 }, { 20, 20 },
            { 7, 7 }, { 6, 6 }, { 1, 1 }
        });

        std::cout << u.determinant() << std::endl;
    }
    {
        Matrix<Complex<>> u(4, 4, {
            { 8, 8 }, { 5, 5 }, { -2, -2 }, { 4, 4 },
            { 4, 4 }, { 2.5, 2.5 }, { 20, 20 }, { 4, 4 },
            { 8, 8 }, { 5, 5 }, { 1, 1 }, { 4, 4 },
            { 28, 28 }, { -4, -4 }, { 17, 17 }, { 1, 1 }
        });

        std::cout << u.determinant() << std::endl;
    }

    return 0;
}
