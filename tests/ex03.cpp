
#include <iostream>
#include <iomanip>
#include "../srcs/Complex.hpp"
#include "../srcs/Functions.hpp"
#include "../srcs/Matrix.hpp"
#include "../srcs/Vector.hpp"


int main( void )
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-- 03 - Dot --------------------------------------------------------------------" << std::endl;

    // #########################################################################
    // Subject (Float)
    // #########################################################################
    std::cout << "- Float ------------------------------- " << std::endl;
    {
        Vector<> u({ 0, 0 });
        Vector<> v({ 1, 1 });

        std::cout << u.dot(v) << std::endl;
    }
    {
        Vector<> u({ 1, 1 });
        Vector<> v({ 1, 1 });

        std::cout << u.dot(v) << std::endl;
    }
    {
        Vector<> u({ -1, 6 });
        Vector<> v({ 3, 2 });

        std::cout << u.dot(v) << std::endl;
    }

    // #########################################################################
    // Bonus (Complex)
    // #########################################################################
    std::cout << "- Complex ----------------------------- " << std::endl;
    {
        Vector<Complex<>> u({ { 0, 0 }, { 0, 0 } });
        Vector<Complex<>> v({ { 1, 1 }, { 1, 1 } });

        std::cout << u.dot(v) << std::endl;
    }
    {
        Vector<Complex<>> u({ { 1, 1 }, { 1, 1 } });
        Vector<Complex<>> v({ { 1, 1 }, { 1, 1 } });

        std::cout << u.dot(v) << std::endl;
    }
    {
        Vector<Complex<>> u({ { -1, -1 }, { 6, 6 } });
        Vector<Complex<>> v({ { 3, 3 }, { 2, 2 } });

        std::cout << u.dot(v) << std::endl;
    }

    return 0;
}