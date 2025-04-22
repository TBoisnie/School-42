
#include <iostream>
#include <iomanip>
#include "../srcs/Complex.hpp"
#include "../srcs/Functions.hpp"
#include "../srcs/Matrix.hpp"
#include "../srcs/Vector.hpp"


int main( void )
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-- 01 - Linear Combination -----------------------------------------------------" << std::endl;

    // #########################################################################
    // Subject (Float)
    // #########################################################################
    std::cout << "- Float ------------------------------- " << std::endl;
    {
        Vector<> e1({ 1, 0, 0 });
        Vector<> e2({ 0, 1, 0 });
        Vector<> e3({ 0, 0, 1 });

        Vector<> v1({ 1, 2, 3 });
        Vector<> v2({ 0, 10, -100 });

        std::cout << linear_combination({ e1, e2, e3 }, { 10.f, -2.f, .5f }) << std::endl;
        std::cout << linear_combination({ v1, v2 }, { 10.f, -2.f }) << std::endl;
    }

    // #########################################################################
    // Bonus (Complex)
    // #########################################################################
    std::cout << "- Complex ----------------------------- " << std::endl;
    {
        Vector<Complex<>> e1({ { 1, 1 }, { 0, 0 }, { 0, 0 } });
        Vector<Complex<>> e2({ { 0, 0 }, { 1, 1 }, { 0, 0 } });
        Vector<Complex<>> e3({ { 0, 0 }, { 0, 0 }, { 1, 1 } });

        Vector<Complex<>> v1({ { 1, 1 }, { 2, 2 }, { 3, 3 } });
        Vector<Complex<>> v2({ { 0, 0 }, { 10, 10 }, { -100, -100 } });

        std::cout << linear_combination<Vector<Complex<>>, Complex<>>({ e1, e2, e3 }, { { 10, 10 }, { -2, -2 }, { .5, .5 } }) << std::endl;
        std::cout << linear_combination<Vector<Complex<>>, Complex<>>({ v1, v2 }, { 2.f, 10.f }) << std::endl;
    }

    return 0;
}
