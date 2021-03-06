//
// Created by Eddie Hoyle on 13/11/16.
//

#ifndef SEVENGINE_WORKSHOP_02_EXAMPLE_HH
#define SEVENGINE_WORKSHOP_02_EXAMPLE_HH


#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

#include <sev/graphics/Texture.hh>
//#include <sev/graphics/render/RenderRect.hh>

namespace E02 {


class ExampleParticles
        : public QOpenGLWidget,
          protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit ExampleParticles( QWidget* parent = NULL );
    ~ExampleParticles();

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL( int width, int height ) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

public slots:
    void cleanup();
    void animate();

};

}

#endif //SEVENGINE_WORKSHOP_EXAMPLE_HH
