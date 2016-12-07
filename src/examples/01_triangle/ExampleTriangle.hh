//
// Created by Eddie Hoyle on 13/11/16.
//

#ifndef SEVENGINE_WORKSHOP_01_EXAMPLE_HH
#define SEVENGINE_WORKSHOP_01_EXAMPLE_HH

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

#include <sev/core/Shader.hh>

//namespace E01 {
//    class ExampleTriangle;
//}

namespace E01 {

class ExampleTriangle
        : public QOpenGLWidget,
          protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit ExampleTriangle( QWidget* parent = NULL );
    ~ExampleTriangle();

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL( int width, int height ) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

public slots:
    void cleanup();
    void animate();

private:
    Shader* m_shader;

};

}


#endif //SEVENGINE_WORKSHOP_01_EXAMPLE_HH
