//
// Created by Eddie Hoyle on 13/11/16.
//

#ifndef SEVENGINE_WORKSHOP_05_EXAMPLE_HH
#define SEVENGINE_WORKSHOP_05_EXAMPLE_HH

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

#include <sev/core/Shader.hh>
#include <sev/graphics/Texture.hh>
#include <sev/graphics/render/RenderRect.hh>

namespace E05 {

class Example
        : public QOpenGLWidget,
          protected QOpenGLFunctions
{
//    Q_OBJECT

public:
    explicit Example( QWidget* parent = NULL );
    ~Example();

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL( int width, int height ) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

public slots:
    void cleanup();
    void animate();

private:
    Shader* m_shader;
    Texture2D* m_texture;
    RenderRect* m_render;

};

}

#endif //SEVENGINE_WORKSHOP_05_EXAMPLE_HH
