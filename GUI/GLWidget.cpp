#include "GLWidget.h"

#if !defined(__APPLE__)
#include <GL/glu.h>
#endif

#include <fstream>
#include <iostream>
using namespace std;

#include <Core/Exceptions.h>
#include <Core/DCoordinates3.h>
#include <Core/Matrices.h>
#include <Core/RealSquareMatrices.h>
#include "../Test/TestFunctions.h"

namespace cagd
{
    //--------------------------------
    // special and default constructor
    //--------------------------------
    GLWidget::GLWidget(QWidget *parent): QOpenGLWidget(parent)
    {
    }

    //--------------------------------------------------------------------------------------
    // this virtual function is called once before the first call to paintGL() or resizeGL()
    //--------------------------------------------------------------------------------------
    void GLWidget::initializeGL()
    {
        // creating a perspective projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = static_cast<double>(width()) / static_cast<double>(height());
        _z_near = 1.0;
        _z_far  = 1000.0;
        _fovy   = 45.0;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // setting the model view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        _eye[0] = _eye[1] = 0.0; _eye[2] = 6.0;
        _center[0] = _center[1] = _center[2] = 0.0;
        _up[0] = _up[2] = 0.0; _up[1] = 1.0;

        gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

        // enabling the depth test
        glEnable(GL_DEPTH_TEST);

        // setting the background color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // initial values of transformation parameters
        _angle_x = _angle_y = _angle_z = 0.0;
        _trans_x = _trans_y = _trans_z = 0.0;
        _zoom = 1.0;

        // ...

        try
        {
            // initializing the OpenGL Extension Wrangler library
            GLenum error = glewInit();

            if (error != GLEW_OK)
            {
                throw Exception("Could not initialize the OpenGL Extension Wrangler Library!");
            }

            if (!glewIsSupported("GL_VERSION_2_0"))
            {
                throw Exception("Your graphics card is not compatible with OpenGL 2.0+! "
                                "Try to update your driver or buy a new graphics adapter!");
            }

            // create and store your geometry in display lists or vertex buffer objects
            RowMatrix<ParametricCurve3::Derivative> derivative(3);

            if (!_createAllParametricCurvesAndTheirImages())
            {
                throw Exception("Could not create all parametric curves!");
            }

//            _pc = nullptr;
//            _pc = new (nothrow) ParametricCurve3(derivative, spiral_on_cone::u_min, spiral_on_cone::u_max);

//            if(_pc)
//            {
//                //error
//            }

//            GLuint div_point_count = 200;
//            GLenum usage_flag = GL_STATIC_DRAW;

//            _image_of_pc = nullptr;
//            _image_of_pc = _pc->GenerateImage(div_point_count, usage_flag);

//            if(!_image_of_pc)
//            {
//                throw Exception("Could not generate the image of the parametric curve!");
//            }

//            if(! _image_of_pc->UpdateVertexBufferObjects(usage_flag))
//            {
//                throw Exception("Could not create the vertex buffer object of the parametric curve!");
//            }

            glEnable(GL_POINT_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

            glEnable(GL_LINE_SMOOTH);
            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

            glEnable(GL_POLYGON_SMOOTH);
            glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

            glEnable(GL_DEPTH_TEST);


        }
        catch (Exception &e)
        {
            cout << e << endl;
        }
    }

    //-----------------------
    // the rendering function
    //-----------------------
    void GLWidget::paintGL()
    {
        // clears the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // stores/duplicates the original model view matrix
        glPushMatrix();

            // applying transformations
            glRotatef(_angle_x, 1.0, 0.0, 0.0);
            glRotatef(_angle_y, 0.0, 1.0, 0.0);
            glRotatef(_angle_z, 0.0, 0.0, 1.0);
            glTranslated(_trans_x, _trans_y, _trans_z);
            glScaled(_zoom, _zoom, _zoom);

            // render your geometry (this is oldest OpenGL rendering technique, later we will use some advanced methods)

//            glColor3f(1.0f, 1.0f, 1.0f);
//            glBegin(GL_LINES);
//                glVertex3f(0.0f, 0.0f, 0.0f);
//                glVertex3f(1.1f, 0.0f, 0.0f);

//                glVertex3f(0.0f, 0.0f, 0.0f);
//                glVertex3f(0.0f, 1.1f, 0.0f);

//                glVertex3f(0.0f, 0.0f, 0.0f);
//                glVertex3f(0.0f, 0.0f, 1.1f);
//            glEnd();

//            glBegin(GL_TRIANGLES);
//                // attributes
//                glColor3f(1.0f, 0.0f, 0.0f);
//                // associated with position
//                glVertex3f(1.0f, 0.0f, 0.0f);

//                // attributes
//                glColor3f(0.0, 1.0, 0.0);
//                // associated with position
//                glVertex3f(0.0, 1.0, 0.0);

//                // attributes
//                glColor3f(0.0f, 0.0f, 1.0f);
//                // associated with position
//                glVertex3f(0.0f, 0.0f, 1.0f);
//            glEnd();

                switch(_homework_id)
                {
                case 0:
                    _renderSelectedParametricCurve();
                    break;
                }

            //_privateTestFunction();
        // pops the current matrix stack, replacing the current matrix with the one below it on the stack,
        // i.e., the original model view matrix is restored
        glPopMatrix();
    }

    //----------------------------------
   // your simple private test function
   //----------------------------------
   void GLWidget::_privateTestFunction()
   {
       // create log-files for your test-cases
       // the output files will be generated inside the folder build-QtFramework-...-{Debug|Release}
       fstream log("output.txt", ios_base::out);

        log << "Testing vector- or matrix-related operations..." << endl;
        log << "-----------------------------------------------" << endl;

       // e.g.,
       DCoordinate3 i(1, 0, 0), j(0, 1, 0);
       DCoordinate3 k = i^j;                // the result should be (0, 0, 1)
       log << "testing cross product: " << k << endl;

       // e.g.,
       log << "testing the special constructor of the template class Matrix" << endl;
       Matrix<int> M(3, 5);
       log << M << endl;


       log <<" i + j : "<< i+j << endl;
       log <<" i - j : "<< i-j << endl;
       i += j;
       log <<" i += j : "<< i << endl;
       i -= j;
       log <<" i -= j : "<< i << endl;
       DCoordinate3 a(k);
       log <<"copy constructor k: "<< a<< endl;

       Matrix<GLuint> b(2,3);
       RowMatrix<GLuint> c(3);
       ColumnMatrix<GLuint> d(2);
       log << "2x3 matrix: "<<b << endl;
       log << "size 3 rowmatrix: "<< c << endl;
       log << "size 2 columnmatrix: "<< d << endl;

       b(0,0) = 2;
       c(0) = 1;
       c(1) = 2;
       c(2) = 3;
       log << "Modified rowmatrix: "<< c << endl;
       b.SetRow(0,c);
       log << "Matrix first row modified by rowmatrix: " << b << endl;
       b.ResizeRows(1);
       log << "Resized matrix: " << b << endl;
       c.ResizeRows(2);
       log << "Resized rowmatrix" << c << endl;

       fstream input("input.txt", ios_base::in);
       Matrix<GLuint> m;
       input >> m;
       log<<"input matrix: "<< m << endl;
       m.ResizeRows(2);
       if(m.SetColumn(0,d))
            log << "Modified input matrix: " << m << endl;
       else
           log << "Not set matrix!" << endl;

       TriangularMatrix<GLuint> e;
       input >> e;
       log << "Input triangular matrix: "<< e << endl;

       e(0,0) = 10;
       log << "Modified triangular matrix: " << e << endl;

       e.ResizeRows(4);
       log << "Resized triangular matrix: " << e << endl;

       RealSquareMatrix f;
       input >> f;
       input.close();
       log << "Input RealMatrix: " << f << endl;
       f.ResizeColumns(2);
       log << "Resized RealMarix: " << f << endl;
       f.ResizeRows(3);
       log << "Resized RealMarix: " << f << endl;

       // if you detect errors, throw some meaningful exceptions, which will be catched
       // by the try-catch-block that appears in the method GLWidget::initializeGL()
       // if (/*error*/)
       // {
       //    throw Exception("Could not perform the ... operation!");
       // }

       // etc.

       // you should also test ALL input stream operators!

       log.close();
   }

    //----------------------------------------------------------------------------
    // when the main window is resized one needs to redefine the projection matrix
    //----------------------------------------------------------------------------
    void GLWidget::resizeGL(int w, int h)
    {
        // setting the new size of the rendering context
        glViewport(0, 0, w, h);

        // redefining the projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = static_cast<double>(w) / static_cast<double>(h);

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // switching back to the model view matrix
        glMatrixMode(GL_MODELVIEW);

        update();
    }

    //-----------------------------------
    // implementation of the public slots
    //-----------------------------------

    void GLWidget::set_angle_x(int value)
    {
        if (_angle_x != value)
        {
            _angle_x = value;
            update();
        }
    }

    void GLWidget::set_angle_y(int value)
    {
        if (_angle_y != value)
        {
            _angle_y = value;
            update();
        }
    }

    void GLWidget::set_angle_z(int value)
    {
        if (_angle_z != value)
        {
            _angle_z = value;
            update();
        }
    }

    void GLWidget::set_zoom_factor(double value)
    {
        if (_zoom != value)
        {
            _zoom = value;
            update();
        }
    }

    void GLWidget::set_trans_x(double value)
    {
        if (_trans_x != value)
        {
            _trans_x = value;
            update();
        }
    }

    void GLWidget::set_trans_y(double value)
    {
        if (_trans_y != value)
        {
            _trans_y = value;
            update();
        }
    }

    void GLWidget::set_trans_z(double value)
    {
        if (_trans_z != value)
        {
            _trans_z = value;
            update();
        }
    }

    bool GLWidget::_createAllParametricCurvesAndTheirImages()
    {
        _pc.ResizeColumns(_pc_count);
        RowMatrix<ParametricCurve3::Derivative> d(3);

        d[0] = spiral_on_cone::d0;
        d[1] = spiral_on_cone::d1;
        d[2] = spiral_on_cone::d2;

        _pc[0] = new (nothrow) ParametricCurve3(d, spiral_on_cone::u_min, spiral_on_cone::u_max);

        d[0] = torus_knot::d0;
        d[1] = torus_knot::d1;
        d[2] = torus_knot::d2;

        _pc[1] = new (nothrow) ParametricCurve3(d, torus_knot::u_min, torus_knot::u_max);

        d[0] = lissajous::d0;
        d[1] = lissajous::d1;
        d[2] = lissajous::d2;

        _pc[2] = new (nothrow) ParametricCurve3(d, lissajous::u_min, lissajous::u_max);

        d[0] = rose::d0;
        d[1] = rose::d1;
        d[2] = rose::d2;

        _pc[3] = new (nothrow) ParametricCurve3(d, rose::u_min, rose::u_max);

        d[0] = hypotrochoid::d0;
        d[1] = hypotrochoid::d1;
        d[2] = hypotrochoid::d2;

        _pc[4] = new (nothrow) ParametricCurve3(d, hypotrochoid::u_min, hypotrochoid::u_max);

        d[0] = circle::d0;
        d[1] = circle::d1;
        d[2] = circle::d2;

        _pc[5] = new (nothrow) ParametricCurve3(d, circle::u_min, circle::u_max);

//        if (!_pc[0])
//        {
//           _destroyAllExistingParametricCurvesAndTheirImages();
//           return false;
//        }

        // a képek és azok csúcspont-pufferobjektumainak egységes létrehozása
        _image_of_pc.ResizeColumns(_pc_count);
        for (GLuint i = 0; i < _pc_count; i++)
        {
            _image_of_pc[i] = _pc[i]->GenerateImage(200, GL_STATIC_DRAW);

            if (!_image_of_pc[i] || !_image_of_pc[i]->UpdateVertexBufferObjects(_scale, GL_STATIC_DRAW))
            {
                _destroyAllExistingParametricCurvesAndTheirImages();
                return false;
            }
        }

        return true;
    }

    void GLWidget::_destroyAllExistingParametricCurvesAndTheirImages()
    {
        for (GLuint i = 0; i < _pc_count; i++)
        {
             if (_pc[i])
             {
                 delete _pc[i]; _pc[i] = nullptr;
             }

             if (_image_of_pc[i])
             {
                 delete _image_of_pc [i]; _image_of_pc[i] = nullptr;
             }
        }
    }

    bool GLWidget::_renderSelectedParametricCurve()
    {
        if (!_image_of_pc[_selected_pc])
        {
             return false;
        }

        glColor3f(1.0f,0.0f,0.0f);
        _image_of_pc[_selected_pc]->RenderDerivatives(0, GL_LINE_STRIP);

        if (_show_tangents)
        {
            glColor3f(0.0f,0.5f,0.0f);
            _image_of_pc[_selected_pc]->RenderDerivatives(1, GL_LINES);
            _image_of_pc[_selected_pc]->RenderDerivatives(1, GL_POINTS);
        }

        if (_show_acceleration_vectors)
        {
            glColor3f(0.1f,0.5f,0.9f);
            _image_of_pc[_selected_pc]->RenderDerivatives(2, GL_LINES);
            _image_of_pc[_selected_pc]->RenderDerivatives(2, GL_POINTS);
        }

        return true;
    }

    GLWidget::~GLWidget()
    {
        if (_homework_id == 0)
        {
            _destroyAllExistingParametricCurvesAndTheirImages();
        }
    }

    void GLWidget::setParametricCurveIndex(int index)
    {
        _selected_pc = index;
        update();
    }

    void GLWidget::setVisibilityOfTangents(int visibility)
    {
        if (visibility != 0)
            _show_tangents = true;
        else
            _show_tangents = false;
        update();
    }

    void GLWidget::setVisibilityOfAccelerationVectors(int visibility)
    {
        if (visibility != 0)
            _show_acceleration_vectors = true;
        else
            _show_acceleration_vectors = false;
        update();
    }

    void GLWidget::setTheNumberOfSubdivisionPointsAlongTheSelectedParametricCurve(int div_point_count)
    {
        try
        {
            if (_pc[_selected_pc] && _image_of_pc[_selected_pc] && div_point_count != _image_of_pc[_selected_pc]->GetPointCount())
            {
                // régi kép törlése
                delete _image_of_pc[_selected_pc];

                // új osztópontrendszerhez tartozó kép előállítása
                _image_of_pc[_selected_pc] = _pc[_selected_pc]->GenerateImage(div_point_count, GL_STATIC_DRAW);

                if (!_image_of_pc[_selected_pc])
                {
                    throw Exception("Could not generate the new image!");
                    exit(-1);
                }

                // az új kép csúcspont-pufferobjektumainak felépítése
                if (!_image_of_pc[_selected_pc]->UpdateVertexBufferObjects(_scale, GL_STATIC_DRAW))
                {
                    delete _image_of_pc[_selected_pc];
                    throw Exception("Could not update vertex buffer object!");
                }
            }
            update();
        }
        catch (Exception &e)
        {
            cout << e << endl;
        }
    }

    void GLWidget::setScaleDerivative(double scale)
    {
        if(_scale != scale)
        {
            _scale = scale;
            _image_of_pc[_selected_pc]->UpdateVertexBufferObjects(_scale, GL_STATIC_DRAW);
            update();
        }
    }
}
