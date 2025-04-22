
#include <iostream>
#include <iomanip>
#include "../srcs/Complex.hpp"
#include "../srcs/Functions.hpp"
#include "../srcs/Matrix.hpp"
#include "../srcs/Vector.hpp"


int main( void )
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "-- 14 - Projection -------------------------------------------------------------" << std::endl;

    {
        float width = 720.f;
        float height = 480.f;

        float fov = 90.f; // Degree
        float ratio = width / height;
        float near = 1.f;
        float far = 10.f;

        std::cout << projection(fov, ratio, near, far) << std::endl;
    }

    return 0;
}
