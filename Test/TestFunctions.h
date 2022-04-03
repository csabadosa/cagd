#pragma once

#include "../Core/DCoordinates3.h"

namespace cagd
{
    namespace spiral_on_cone
    {
        extern GLdouble u_min, u_max;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    namespace torus_knot
    {
            extern GLdouble u_min, u_max;

            DCoordinate3 d0(GLdouble);
            DCoordinate3 d1(GLdouble);
            DCoordinate3 d2(GLdouble);
    }

    namespace lissajous
    {
            extern GLdouble u_min, u_max, a, b, kx, ky;
            DCoordinate3 d0(GLdouble);
            DCoordinate3 d1(GLdouble);
            DCoordinate3 d2(GLdouble);
    }

    namespace rose
    {
            extern GLdouble u_min, u_max, k;
            DCoordinate3 d0(GLdouble);
            DCoordinate3 d1(GLdouble);
            DCoordinate3 d2(GLdouble);
    }

    namespace hypotrochoid
    {
            extern GLdouble u_min, u_max, r, R, d;
            DCoordinate3 d0(GLdouble);
            DCoordinate3 d1(GLdouble);
            DCoordinate3 d2(GLdouble);
    }

    namespace circle
    {
            extern GLdouble u_min, u_max;
            DCoordinate3 d0(GLdouble);
            DCoordinate3 d1(GLdouble);
            DCoordinate3 d2(GLdouble);
    }
}
