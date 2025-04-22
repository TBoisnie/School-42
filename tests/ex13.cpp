
#include <iostream>
#include <iomanip>
#include "../srcs/Complex.hpp"
#include "../srcs/Functions.hpp"
#include "../srcs/Matrix.hpp"
#include "../srcs/Vector.hpp"


int main( void )
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-- 13 - Rank -------------------------------------------------------------------" << std::endl;

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

        std::cout << u.rank() << std::endl;
    }
    {
        Matrix<> u(3, 4, {
            1, 2, 0, 0,
            2, 4, 0, 0,
            -1, 2, 1, 1
        });

        std::cout << u.rank() << std::endl;
    }
    {
        Matrix<> u(4, 3, {
            8, 5, -2,
            4, 7, 20,
            7, 6, 1,
            21, 18, 7
        });

        std::cout << u.rank() << std::endl;
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

        std::cout << u.rank() << std::endl;
    }
    {
        Matrix<Complex<>> u(3, 4, {
            { 1, 1 }, { 2, 2 }, { 0, 0 }, { 0, 0 },
            { 2, 2 }, { 4, 4 }, { 0, 0 }, { 0, 0 },
            { -1, -1 }, { 2, 2 }, { 1, 1 }, { 1, 1 },
        });

        std::cout << u.rank() << std::endl;
    }
    {
        Matrix<Complex<>> u(4, 3, {
            { 8, 8 }, { 5, 5 }, { -2, -2 },
            { 4, 4 }, { 7, 7 }, { 20, 20 },
            { 7, 7 }, { 6, 6 }, { 1, 1 },
            { 21, 21 }, { 18, 18 }, { 7, 7 },
        });

        std::cout << u.rank() << std::endl;
    }

    return 0;
}
