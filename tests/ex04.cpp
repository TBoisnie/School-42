
#include <iostream>
#include <iomanip>
#include "../srcs/Complex.hpp"
#include "../srcs/Functions.hpp"
#include "../srcs/Matrix.hpp"
#include "../srcs/Vector.hpp"


int main( void )
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-- 04 - Norms ------------------------------------------------------------------" << std::endl;

    // #########################################################################
    // Subject (Float)
    // #########################################################################
    std::cout << "- Float ------------------------------- " << std::endl;
    {
        Vector<> u({ 0, 0, 0 });

        std::cout << u.norm_1() << " / " <<  u.norm() << " / " << u.norm_inf() << std::endl;
    }
    {
        Vector<> u({ 1, 2, 3 });

        std::cout << u.norm_1() << " / " <<  u.norm() << " / " << u.norm_inf() << std::endl;
    }
    {
        Vector<> u({ -1, -2 });

        std::cout << u.norm_1() << " / " <<  u.norm() << " / " << u.norm_inf() << std::endl;
    }

    // #########################################################################
    // Bonus (Complex)
    // #########################################################################
    std::cout << "- Complex ----------------------------- " << std::endl;
    {
        Vector<Complex<>> u({ { 0, 0 }, { 0, 0 }, { 0, 0 } });

        std::cout << u.norm_1() << " / " <<  u.norm() << " / " << u.norm_inf() << std::endl;
    }
    {
        Vector<Complex<>> u({ { 1, 1 }, { 2, 2 }, { 3, 3 } });

        std::cout << u.norm_1() << " / " <<  u.norm() << " / " << u.norm_inf() << std::endl;
    }
    {
        Vector<Complex<>> u({ { -1, -1 }, { -2, -2 } });

        std::cout << u.norm_1() << " / " <<  u.norm() << " / " << u.norm_inf() << std::endl;
    }

    return 0;
}