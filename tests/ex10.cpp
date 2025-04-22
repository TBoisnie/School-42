
#include <iostream>
#include <iomanip>
#include "../srcs/Complex.hpp"
#include "../srcs/Functions.hpp"
#include "../srcs/Matrix.hpp"
#include "../srcs/Vector.hpp"


int main( void )
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-- 10 - Row Echelon ------------------------------------------------------------" << std::endl;

    // #########################################################################
    // Subject (Float)
    // #########################################################################
    std::cout << "- Float ------------------------------- " << std::endl;
    {
        Matrix<> u(3, 3, {
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        });

        std::cout << u.row_echelon() << std::endl;
    }
    {
        Matrix<> u(2, 2, {
            1, 2,
            3, 4
        });

        std::cout << u.row_echelon() << std::endl;
    }
    {
        Matrix<> u(2, 2, {
            1, 2,
            2, 4
        });

        std::cout << u.row_echelon() << std::endl;
    }
    {
        Matrix<> u(3, 5, {
            8, 5, -2, 4, 28,
            4, 2.5, 20, 4, -4,
            8, 5, 1, 4, 17
        });

        std::cout << u.row_echelon() << std::endl;
    }

    // #########################################################################
    // Bonus (Complex)
    // #########################################################################
    std::cout << "- Complex ----------------------------- " << std::endl;
    {
        Matrix<Complex<>> u(3, 3, {
            { 1, 1 }, { 0, 0 }, { 0, 0 },
            { 0, 0 }, { 1, 1 }, { 0, 0 },
            { 0, 0 }, { 0, 0 }, { 1, 1 }
        });

        std::cout << u.row_echelon() << std::endl;
    }
    {
        Matrix<Complex<>> u(2, 2, {
            { 1, 1 }, { 2, 2 },
            { 3, 3 }, { 4, 4 }
        });

        std::cout << u.row_echelon() << std::endl;
    }
    {
        Matrix<Complex<>> u(2, 2, {
            { 1, 1 }, { 2, 2 },
            { 2, 2 }, { 4, 4 }
        });

        std::cout << u.row_echelon() << std::endl;
    }
    {
        Matrix<Complex<>> u(3, 5, {
            { 8, 8 }, { 5, 5 }, { -2, -2 }, { 4, 4 }, { 28, 28 },
            { 4, 4 }, { 2.5, 2.5 }, { 20, 20 }, { 4, 4 }, { -4, -4 },
            { 8, 8 }, { 5, 5 }, { 1, 1 }, { 4, 4 }, { 17, 17 }
        });

        std::cout << u.row_echelon() << std::endl;
    }

    return 0;
}
