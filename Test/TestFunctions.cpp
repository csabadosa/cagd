#include <cmath>
#include "TestFunctions.h"
#include "../Core/Constants.h"

using namespace cagd;
using namespace std;

GLdouble spiral_on_cone::u_min = -TWO_PI;
GLdouble spiral_on_cone::u_max = +TWO_PI;

DCoordinate3 spiral_on_cone::d0(GLdouble u)
{
    return DCoordinate3(u * cos(u), u * sin(u), u);
}

DCoordinate3 spiral_on_cone::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(c - u * s, s + u * c, 1.0);
}

DCoordinate3 spiral_on_cone::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(-2.0 * s - u * c, 2.0 * c - u * s, 0);
}

GLdouble torus_knot::u_min = 0;
GLdouble torus_knot::u_max = 6*PI;

DCoordinate3 torus_knot::d0(GLdouble u){
    return DCoordinate3((2+cos((2*u)/3))*cos(u), (2+cos((2*u)/3))*sin(u), sin((2*u)/3));
}

DCoordinate3 torus_knot::d1(GLdouble u){
    GLdouble s = sin(u), c = cos(u);
    GLdouble c3 = cos((2*u)/3), s3 = sin((2*u)/3);
    return DCoordinate3(-2*s - (2*s3*c)/3 - c3*s, -2*c - (2*s3*s)/3 + c3*c, (2*c3)/3);
}

DCoordinate3 torus_knot::d2(GLdouble u)
{
        GLdouble s = sin(u), c = cos(u);
        GLdouble c3 = cos((2*u)/3), s3 = sin((2*u)/3);
        return DCoordinate3(-2*c-(4*c3*c)/9 + (2*s3*s)/3 - c3*s, -2*c - 2*s3*s/3 + c3*c, - (4*s3)/9);
}

GLdouble lissajous::u_min = 0.0;
GLdouble lissajous::u_max = TWO_PI;
GLdouble lissajous::a = 2.0;
GLdouble lissajous::b = 2.0;
GLdouble lissajous::kx = 3.0;
GLdouble lissajous::ky = 2.0;

DCoordinate3 lissajous::d0(GLdouble u)
{
        return DCoordinate3(a*cos(u*kx), b*sin(u*ky), u);
}

DCoordinate3 lissajous::d1(GLdouble u)
{
        return DCoordinate3(-a*kx*sin(u*kx), b*ky*cos(u*ky), 1.0);
}

DCoordinate3 lissajous::d2(GLdouble u)
{
        return DCoordinate3(-a*kx*kx*cos(u*kx), -b*ky*ky*sin(u*ky), 0.0);
}

GLdouble rose::u_min = 0.0;
GLdouble rose::u_max = TWO_PI;
GLdouble rose::k = 2.0;

DCoordinate3 rose::d0(GLdouble u)
{
        GLdouble ck = cos(k * u);
        return DCoordinate3(ck * cos(u), ck*sin(u), u);
}

DCoordinate3 rose::d1(GLdouble u)
{
        GLdouble ck = cos(k * u);
        GLdouble sk = sin(k * u);
        return DCoordinate3(-k *sk * cos(u) - ck * sin(u), -k*sk*sin(u) + ck * cos(u), 1.0);
}

DCoordinate3 rose::d2(GLdouble u)
{
        GLdouble ck = cos(k * u);
        GLdouble sk = sin(k * u);
        return DCoordinate3(-k * k * ck * cos(u) - k * sk * sin(u)- (-k*sk * sin(u) + ck * cos(u)),
                            -k * k * ck * sin(u) - k * sk * cos(u) - k * sk * cos(u) - ck * sin(u),
                            0.0);
}

GLdouble hypotrochoid::u_min = 0.0;
GLdouble hypotrochoid::u_max = 3.0*TWO_PI;
GLdouble hypotrochoid::r = 3.0;
GLdouble hypotrochoid::R = 5.0;
GLdouble hypotrochoid::d = 5.0;


DCoordinate3 hypotrochoid::d0(GLdouble u)
{
        GLdouble Rmr = R-r;
        GLdouble c = cos((Rmr/r)*u);
        GLdouble s = sin((Rmr/r)*u);
        return DCoordinate3(Rmr*cos(u) + d*c, Rmr*sin(u) - d*s, u);
}

DCoordinate3 hypotrochoid::d1(GLdouble u)
{
        GLdouble Rmr = R-r;
        GLdouble c = cos((Rmr/r)*u);
        GLdouble s = sin((Rmr/r)*u);
        return DCoordinate3(Rmr*(-sin(u)) - d*(Rmr/r)*s, Rmr*cos(u) - d*(Rmr/r)*c, 1.0);
}

DCoordinate3 hypotrochoid::d2(GLdouble u)
{
        GLdouble Rmr = R-r;
        GLdouble c = cos((Rmr/r)*u);
        GLdouble s = sin((Rmr/r)*u);
        return DCoordinate3(Rmr*(-cos(u)) - d*((Rmr*Rmr)/(r*r))*c, Rmr*(-sin(u)) + d*((Rmr*Rmr)/(r*r))*s, 0.0);
}

GLdouble circle::u_max = TWO_PI;
GLdouble circle::u_min = 0.0;

DCoordinate3 circle::d0(GLdouble u)
{
        return DCoordinate3(cos(u), sin(u), u);
}

DCoordinate3 circle::d1(GLdouble u)
{
        return DCoordinate3(-sin(u), cos(u), 1.0);
}

DCoordinate3 circle::d2(GLdouble u)
{
        return DCoordinate3(-cos(u), -sin(u), 0.0);
}



