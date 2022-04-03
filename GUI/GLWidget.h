#pragma once

#include <GL/glew.h>
#include <QOpenGLWidget>
#include "../Parametric/ParametricCurves3.h"

namespace cagd
{
    class GLWidget: public QOpenGLWidget
    {
        Q_OBJECT

    private:

        // variables defining the projection matrix
        double       _aspect;            // aspect ratio of the rendering window
        double       _fovy;              // field of view in direction y
        double       _z_near, _z_far;    // distance of near and far clipping planes

        // variables defining the model-view matrix
        double       _eye[3], _center[3], _up[3];

        // variables needed by transformations
        int         _angle_x, _angle_y, _angle_z;
        double      _zoom;
        double      _trans_x, _trans_y, _trans_z;

        // your other declarations
        // a number that can be used to switch between different test-cases
        int  _homework_id = 0;

        // a simple test-function that does not need dynamical memory allocation, e.g.,
        // _testingDCoordinates(), _testingTemplateMatrices(), etc.
        void _privateTestFunction();

        // starting from the second laboratory assignment...
        bool _createSomeGeometricObjectByDynamicalMemoryAllocation();
        bool _renderExistingGeometricObject();
        void _deleteExistingDynamicallyAllocatedGeometricObject();

        GLuint                       _pc_count = 6;
        RowMatrix<ParametricCurve3*> _pc;
        RowMatrix<GenericCurve3*>    _image_of_pc;
        int                          _selected_pc = 0;
        double                       _scale = 1.0;
        bool                         _show_tangents = false;
        bool                         _show_acceleration_vectors = false;

        bool _createAllParametricCurvesAndTheirImages();
        void _destroyAllExistingParametricCurvesAndTheirImages();
        bool _renderSelectedParametricCurve();


    public:
        // special and default constructor
        // the format specifies the properties of the rendering window
        GLWidget(QWidget* parent = 0);

        // redeclared virtual functions
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);

        // destructor that frees all dynamically allocated memory objects
        virtual ~GLWidget();

    public slots:
        // public event handling methods/slots
        void set_angle_x(int value);
        void set_angle_y(int value);
        void set_angle_z(int value);

        void set_zoom_factor(double value);

        void set_trans_x(double value);
        void set_trans_y(double value);
        void set_trans_z(double value);

        void setParametricCurveIndex(int index);
        void setVisibilityOfTangents(int visibility);
        void setVisibilityOfAccelerationVectors(int visibility);
        void setTheNumberOfSubdivisionPointsAlongTheSelectedParametricCurve(int div_point_count);
        void setScaleDerivative(double scale = 1);
        // it is used by the GLWidget in order to accept/handle the signals of other widgets,
        // e.g., in the constructor of the MainWindow one can introduce a new connection:
        // connect(address_of_another_widget, SIGNAL(signal_name(/*formal type-list*/)),
        //         _gl_widget, SLOT(publicEnventHandler(/*either empty or the same formal type-list*/)));
       /* void publicEventHandler(/*formal parameterlist that is either empty,
                                  or coincides with the type-list signature of
                                  the signal the has to be accpeted);*/
    private slots:
        // it is used by the GLWidget in order to accept/handle its own signals, e.g.,
        // in the constructor of GLWidget one can define a new private connection:
        // connect(this, SIGNAL(signal_name(/*formal type-list*/)),
        //         this, SLOT(_privateEventHandler(/*either empty or the same formal type-list*/)));
        /*void _privateEventHandler(/*formal parameterlist that is either empty,
                                    or coincides with the type-list signature of
                                    the signal the has to be accpeted);*/

    signals:
        // if required, one can declare new signals for the GLWidget, that can be emitted
        // for other widgets, by using the command
        //
        // emit somethingHasChanged(/*values of parameters that follow the formal type-list*/);
        //
        // in a GLWidget-related method...
        //
        // then, in the constructor of the MainWindow one can define a new connection:
        // connect(_gl_widget,
        //          SIGNAL(somethingHasChanged(/*formal type-list*/)),
        //         _side_widget->name_of_child_widget,
        //          SLOT(publicEnventHandler(/*either empty or the same formal type-list*/)));
        void somethingHasChanged(/*formal type-list*/);
};
}
