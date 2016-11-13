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

namespace E01 {
    class Example;
}

namespace E01 {

class Example
        : public QOpenGLWidget,
          protected QOpenGLFunctions
{

public:
    explicit Example( QWidget* parent = NULL );

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL( int width, int height ) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

private:
    void printContextInformation();

public slots:
    void cleanup();

private:
    Shader* m_shader;

};

}


#endif //SEVENGINE_WORKSHOP_01_EXAMPLE_HH
