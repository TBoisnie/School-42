
#include <iostream>
#include <iomanip>
#include "../srcs/Complex.hpp"
#include "../srcs/Functions.hpp"
#include "../srcs/Matrix.hpp"
#include "../srcs/Vector.hpp"


int main( void )
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-- 08 - Trace ------------------------------------------------------------------" << std::endl;

    // #########################################################################
    // Subject (Float)
    // #########################################################################
    std::cout << "- Float ------------------------------- " << std::endl;
    {
        Matrix<> u(2, 2, {
            1, 0,
            0, 1
        });

        std::cout << u.trace() << std::endl;
    }
    {
        Matrix<> u(3, 3, {
            2, -5, 0,
            4, 3, 7,
            -2, 3, 4
        });

        std::cout << u.trace() << std::endl;
    }
    {
        Matrix<> u(3, 3, {
            -2, -8, 4,
            1, -23, 4,
            0, 6, 4
        });

        std::cout << u.trace() << std::endl;
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

        std::cout << u.trace() << std::endl;
    }
    {
        Matrix<Complex<>> u(3, 3, {
            { 2, 2 }, { -5, -5 }, { 0, 0 },
            { 4, 4 }, { 3, 3 }, { 7, 7 },
            { -2, -2 }, { 3, 3 }, { 4, 4 }
        });

        std::cout << u.trace() << std::endl;
    }
    {
        Matrix<Complex<>> u(3, 3, {
            { -2, -2 }, { -8, -8 }, { 4, 4 },
            { 1, 1 }, { -23, -23 }, { 4, 4 },
            { 0, 0 }, { 6, 6 }, { 4, 4 }
        });

        std::cout << u.trace() << std::endl;
    }
    return 0;
}
