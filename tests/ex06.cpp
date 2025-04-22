
#include <iostream>
#include <iomanip>
#include "../srcs/Complex.hpp"
#include "../srcs/Functions.hpp"
#include "../srcs/Matrix.hpp"
#include "../srcs/Vector.hpp"


int main( void )
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-- 06 - Cross Product ----------------------------------------------------------" << std::endl;

    // #########################################################################
    // Subject (Float)
    // #########################################################################
    std::cout << "- Float ------------------------------- " << std::endl;
    {
        Vector<> u({ 0, 0, 1 });
        Vector<> v({ 1, 0, 0 });

        std::cout << cross_product(u, v) << std::endl;
    }
    {
        Vector<> u({ 1, 2, 3 });
        Vector<> v({ 4, 5, 6 });

        std::cout << cross_product(u, v) << std::endl;
    }
    {
        Vector<> u({ 4, 2, -3 });
        Vector<> v({ -2, -5, 16 });

        std::cout << cross_product(u, v) << std::endl;
    }

    // #########################################################################
    // Bonus (Complex)
    // #########################################################################
    std::cout << "- Complex ----------------------------- " << std::endl;
    {
        Vector<Complex<>> u({ { 0, 0 }, { 0, 0 }, { 1, 1 } });
        Vector<Complex<>> v({ { 1, 1 }, { 0, 0 }, { 0, 0 } });

        std::cout << cross_product(u, v) << std::endl;
    }
    {
        Vector<Complex<>> u({ { 1, 1 }, { 2, 2 }, { 3, 3 } });
        Vector<Complex<>> v({ { 4, 4 }, { 5, 5 }, { 6, 6 } });

        std::cout << cross_product(u, v) << std::endl;
    }
    {
        Vector<Complex<>> u({ { 4, 4 }, { 2, 2 }, { -3, -3 } });
        Vector<Complex<>> v({ { -2, -2 }, { -5, -5 }, { 16, 16 } });

        std::cout << cross_product(u, v) << std::endl;
    }

    return 0;
}
