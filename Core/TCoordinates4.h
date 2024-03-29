#pragma once

#include <GL/glew.h>
#include <iostream>

namespace cagd
{
    //-------------------------------------
    // four dimensional texture coordinates
    //-------------------------------------
    class TCoordinate4
    {
    protected:
        GLfloat _data[4]; // (s, t, r, q)

    public:
        // default constructor
        TCoordinate4();

        // homework: special constructor
        TCoordinate4(GLfloat s, GLfloat t, GLfloat r = 0.0, GLfloat q = 1.0);

        // homework: get components by value
        GLfloat operator[](GLuint rhs) const;
        GLfloat s() const;
        GLfloat t() const;
        GLfloat r() const;
        GLfloat q() const;

        // homework: get components by reference
        GLfloat& operator[](GLuint rhs);
        GLfloat& s();
        GLfloat& t();
        GLfloat& r();
        GLfloat& q();
    };

    // default constructor
    inline TCoordinate4::TCoordinate4()
    {
        _data[0] = _data[1] = _data[2] = 0.0;
        _data[3] = 1.0;
    }

    inline TCoordinate4::TCoordinate4(GLfloat s, GLfloat t, GLfloat r, GLfloat q)
    {
        _data[0] = s;
        _data[1] = t;
        _data[2] = r;
        _data[3] = q;
    }

    inline GLfloat TCoordinate4::operator[](GLuint rhs) const
    {
        return _data[rhs];
    }

    inline GLfloat TCoordinate4::s() const
    {
        return _data[0];
    }

    inline GLfloat TCoordinate4::t() const
    {
        return _data[1];
    }

    inline GLfloat TCoordinate4::r() const
    {
        return _data[2];
    }

    inline GLfloat TCoordinate4::q() const
    {
        return _data[3];
    }

    GLfloat& TCoordinate4::operator[](GLuint rhs)
    {
        return _data[rhs];
    }

    inline GLfloat& TCoordinate4::s()
    {
        return _data[0];
    }

    inline GLfloat& TCoordinate4::t()
    {
        return _data[1];
    }

    inline GLfloat& TCoordinate4::r()
    {
        return _data[2];
    }

    inline GLfloat& TCoordinate4::q()
    {
        return _data[3];
    }

    // homework: output to stream
    inline std::ostream& operator <<(std::ostream& lhs, const TCoordinate4& rhs)
    {
        return lhs << rhs.s() << " " << rhs.t() << rhs.r() << " " << rhs.q();
    }

    // homework: input from stream
    inline std::istream& operator >>(std::istream& lhs, TCoordinate4& rhs)
    {
        return lhs >> rhs.s() >> rhs.t() >> rhs.r() >> rhs.q();
    }
}
