//
// Created by Eddie Hoyle on 13/11/16.
//

#ifndef SEVENGINE_WORKSHOP_02_EXAMPLE_HH
#define SEVENGINE_WORKSHOP_02_EXAMPLE_HH

//#include "../AbstractExample.hh"


#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

namespace E02 {
    class Example;
}

namespace E02 {

class Example
        : public QOpenGLWidget,
          protected QOpenGLFunctions {

public:
    explicit Example(QWidget *parent = NULL);

    void initializeGL() Q_DECL_OVERRIDE;

    void paintGL() Q_DECL_OVERRIDE;

public slots:

    void cleanup();

};

}

#endif //SEVENGINE_WORKSHOP_EXAMPLE_HH
