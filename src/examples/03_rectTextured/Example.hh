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

#include <sev/core/Shader.hh>
#include <sev/graphics/Texture.hh>
#include <sev/graphics/render/RenderRect.hh>

//namespace E02 {
//    class Example;
//}

namespace E03 {


class Example
        : public QOpenGLWidget,
          protected QOpenGLFunctions
{

public:
    explicit Example( QWidget* parent = NULL );
    ~Example();

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL( int width, int height ) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

public slots:
    void cleanup();

private:
    Shader* m_shader;
    Texture* m_texture;
    RenderRect* m_render;

};

}

#endif //SEVENGINE_WORKSHOP_EXAMPLE_HH
