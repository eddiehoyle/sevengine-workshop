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

#include <sev/graphics/Texture.hh>
#include <sev/graphics/render/RenderRect.hh>

//namespace E02 {
//    class ExampleTriangle;
//}

namespace E02 {


class ExampleRect
        : public QOpenGLWidget,
          protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit ExampleRect( QWidget* parent = NULL );
    ~ExampleRect();

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL( int width, int height ) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

public slots:
    void cleanup();
    void animate();

private:
    Shader* m_shader;
    Texture* m_texture;
    RenderRect* m_render;

};

}

#endif //SEVENGINE_WORKSHOP_EXAMPLE_HH