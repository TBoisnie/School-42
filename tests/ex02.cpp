
#include <iostream>
#include <iomanip>
#include "../srcs/Complex.hpp"
#include "../srcs/Functions.hpp"
#include "../srcs/Matrix.hpp"
#include "../srcs/Vector.hpp"


int main( void )
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-- 02 - Linear Interpolation ---------------------------------------------------" << std::endl;

    // #########################################################################
    // Subject (Float)
    // #########################################################################
    std::cout << "- Float ------------------------------- " << std::endl;
    {
        std::cout << lerp(0.f, 1.f, 0.f) << std::endl;
        std::cout << lerp(0.f, 1.f, 1.f) << std::endl;
        std::cout << lerp(0.f, 1.f, .5f) << std::endl;
        std::cout << lerp(21.f, 42.f, .3f) << std::endl;
        std::cout << std::endl;
    }
    {
        Vector<> u({ 2, 1 });
        Vector<> v({ 4, 2 });

        std::cout << lerp(u, v, .3) << std::endl;
    }
    {
        Matrix<> u(2, 2, {
            2, 1,
            3, 4
        });
        Matrix<> v(2, 2, {
            20, 10,
            30, 40
        });

        std::cout << lerp(u, v, .5) << std::endl;
    }

    // #########################################################################
    // Bonus (Complex)
    // #########################################################################
    std::cout << "- Complex ----------------------------- " << std::endl;
    {
        std::cout << lerp(Complex<>(0, 0), Complex<>(1, 1), 0) << std::endl;
        std::cout << lerp(Complex<>(0, 0), Complex<>(1, 1), 1) << std::endl;
        std::cout << lerp(Complex<>(0, 0), Complex<>(1, 1), .5) << std::endl;
        std::cout << lerp(Complex<>(21, 21), Complex<>(42, 42), .3) << std::endl;
        std::cout << std::endl;
    }
    {
        Vector<Complex<>> u({ { 2, 2 }, { 1, 1 } });
        Vector<Complex<>> v({ { 4, 4 }, { 2, 2 } });

        std::cout << lerp(u, v, .3) << std::endl;
    }
    {
        Matrix<Complex<>> u(2, 2, {
            { 2, 2 }, { 1, 1 },
            { 3, 3 }, { 4, 4 }
        });
        Matrix<Complex<>> v(2, 2, {
            { 20, 20 }, { 10, 10 },
            { 30, 30 }, { 40, 40 }
        });

        std::cout << lerp(u, v, .5) << std::endl;
    }

    return 0;
}
