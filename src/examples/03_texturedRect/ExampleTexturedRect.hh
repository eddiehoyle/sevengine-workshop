//
// Created by Eddie Hoyle on 13/11/16.
//

#ifndef SEVENGINE_WORKSHOP_03_EXAMPLE_HH
#define SEVENGINE_WORKSHOP_03_EXAMPLE_HH

//#include "../AbstractExample.hh"


#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

#include <sev/graphics/Texture.hh>

namespace E03 {

class ExampleTexturedRect
        : public QOpenGLWidget,
          protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit ExampleTexturedRect( QWidget* parent = NULL );
    ~ExampleTexturedRect();

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL( int width, int height ) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

public slots:
    void cleanup();
    void animate();

};

}

#endif //SEVENGINE_WORKSHOP_EXAMPLE_HH
