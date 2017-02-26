//
// Created by Eddie Hoyle on 25/02/17.
//

#ifndef SEVENGINE_WORKSHOP_EXAMPLELINES_HH
#define SEVENGINE_WORKSHOP_EXAMPLELINES_HH

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

#include <sev/graphics/Texture.hh>
#include <sev/graphics/shader/ShaderManager.hh>

namespace E08 {

class ExampleLines
        : public QOpenGLWidget,
          protected QOpenGLFunctions {

Q_OBJECT

public:
    explicit ExampleLines( QWidget *parent = NULL );
    ~ExampleLines();
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL( int width, int height ) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

public slots:

    void cleanup();
    void animate();

};

}

#endif //SEVENGINE_WORKSHOP_EXAMPLELINES_HH
