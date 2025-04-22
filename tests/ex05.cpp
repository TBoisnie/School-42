
#include <iostream>
#include <iomanip>
#include "../srcs/Complex.hpp"
#include "../srcs/Functions.hpp"
#include "../srcs/Matrix.hpp"
#include "../srcs/Vector.hpp"


int main( void )
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-- 05 - Angle Cos --------------------------------------------------------------" << std::endl;

    // #########################################################################
    // Subject (Float)
    // #########################################################################
    std::cout << "- Float ------------------------------- " << std::endl;
    {
        Vector<> u({ 1, 0 });
        Vector<> v({ 1, 0 });

        std::cout << angle_cos(u, v) << std::endl;
    }
    {
        Vector<> u({ 1, 0 });
        Vector<> v({ 0, 1 });

        std::cout << angle_cos(u, v) << std::endl;
    }
    {
        Vector<> u({ -1, 1 });
        Vector<> v({ 1, -1 });

        std::cout << angle_cos(u, v) << std::endl;
    }
    {
        Vector<> u({ 2, 1 });
        Vector<> v({ 4, 2 });

        std::cout << angle_cos(u, v) << std::endl;
    }
    {
        Vector<> u({ 1, 2, 3 });
        Vector<> v({ 4, 5, 6 });

        std::cout << angle_cos(u, v) << std::endl;
    }

    // #########################################################################
    // Bonus (Complex)
    // #########################################################################
    std::cout << "- Complex ----------------------------- " << std::endl;
    {
        Vector<Complex<>> u({ { 1, 1 }, { 0, 0 } });
        Vector<Complex<>> v({ { 1, 1 }, { 0, 0 } });

        std::cout << angle_cos(u, v) << std::endl;
    }
    {
        Vector<Complex<>> u({ { 1, 1 }, { 0, 0 } });
        Vector<Complex<>> v({ { 0, 0 }, { 1, 1 } });

        std::cout << angle_cos(u, v) << std::endl;
    }
    {
        Vector<Complex<>> u({ { -1, -1 }, { 1, 1 } });
        Vector<Complex<>> v({ { 1, 1 }, { -1, -1 } });

        std::cout << angle_cos(u, v) << std::endl;
    }
    {
        Vector<Complex<>> u({ { 2, 2 }, { 1, 1 } });
        Vector<Complex<>> v({ { 4, 4 }, { 2, 2 } });

        std::cout << angle_cos(u, v) << std::endl;
    }
    {
        Vector<Complex<>> u({ { 1, 1 }, { 2, 2 }, { 3, 3 } });
        Vector<Complex<>> v({ { 4, 4 }, { 5, 5 }, { 6, 6 } });

        std::cout << angle_cos(u, v) << std::endl;
    }

    return 0;
}
