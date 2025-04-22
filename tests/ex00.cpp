
#include <iostream>
#include <iomanip>
#include "../srcs/Complex.hpp"
#include "../srcs/Functions.hpp"
#include "../srcs/Matrix.hpp"
#include "../srcs/Vector.hpp"


int main( void )
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-- 00 - Add / Sub / Scl --------------------------------------------------------" << std::endl;

    // #########################################################################
    // Subject (Float)
    // #########################################################################
    std::cout << "- Float ------------------------------- " << std::endl;
    {
        Vector<>       u({ 2, 3 });
        Vector<> const v({ 5, 7 });

        u.add(v);

        std::cout << u << std::endl;
    }
    {
        Vector<>       u({ 2, 3 });
        Vector<> const v({ 5, 7 });

        u.sub(v);

        std::cout << u << std::endl;
    }
    {
        Vector<> u({ 2, 3 });

        u.scl(2);

        std::cout << u << std::endl;
    }
    {
        Matrix<>       u(2, 2, {
            1, 2,
            3, 4
        });
        Matrix<> const v(2, 2, {
             7, 4,
            -2, 2
        });

        u.add(v);

        std::cout << u << std::endl;
    }
    {
        Matrix<>       u(2, 2, {
            1, 2,
            3, 4
        });
        Matrix<> const v(2, 2, {
             7, 4,
            -2, 2
        });

        u.sub(v);

        std::cout << u << std::endl;
    }
    {
        Matrix<> u(2, 2, {
            1, 2,
            3, 4
        });

        u.scl(2);

        std::cout << u << std::endl;
    }

    // #########################################################################
    // Bonus (Complex)
    // #########################################################################
    std::cout << "- Complex ----------------------------- " << std::endl;
    {
        Vector<Complex<>>       u({ { 2, 2 }, { 3, 3 } });
        Vector<Complex<>> const v({ { 5, 5 }, { 7, 7 } });

        u.add(v);

        std::cout << u << std::endl;
    }
    {
        Vector<Complex<>>       u({ { 2, 2 }, { 3, 3 } });
        Vector<Complex<>> const v({ { 5, 5 }, { 7, 7 } });

        u.sub(v);

        std::cout << u << std::endl;
    }
    {
        Vector<Complex<>> u({ { 2, 2 }, { 3, 3 } });

        u.scl(2);

        std::cout << u << std::endl;
    }
    {
        Matrix<Complex<>>       u(2, 2, {
            { 1, 1 }, { 2, 2 },
            { 3, 3 }, { 4, 4 }
        });
        Matrix<Complex<>> const v(2, 2, {
            { 7, 7 }, { 4, 4 },
            { -2, -2 }, { 2, 2 }
        });

        u.add(v);

        std::cout << u << std::endl;
    }
    {
        Matrix<Complex<>> u(2, 2, {
            { 1, 1 }, { 2, 2 },
            { 3, 3 }, { 4, 4 }
        });
        Matrix<Complex<>> const v(2, 2, {
            { 7, 7 }, { 4, 4 },
            { -2, -2 }, { 2, 2 }
        });

        u.sub(v);

        std::cout << u << std::endl;
    }
    {
        Matrix<Complex<>> u(2, 2, {
            { 1, 1 }, { 2, 2 },
            { 3, 3 }, { 4, 4 }
        });

        u.scl(2);

        std::cout << u << std::endl;
    }

    return 0;
}
