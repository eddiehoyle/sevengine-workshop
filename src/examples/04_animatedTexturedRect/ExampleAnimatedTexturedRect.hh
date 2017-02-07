//
// Created by Eddie Hoyle on 13/11/16.
//

#ifndef SEVENGINE_WORKSHOP_04_EXAMPLE_HH
#define SEVENGINE_WORKSHOP_04_EXAMPLE_HH

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

#include <sev/graphics/Texture.hh>
#include <sev/graphics/render/RenderRect.hh>
#include <sev/graphics/render/RenderQuad.hh>
#include <sev/graphics/shader/ShaderManager.hh>

namespace E04 {

class ExampleAnimatedTexturedRect
        : public QOpenGLWidget,
          protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit ExampleAnimatedTexturedRect( QWidget* parent = NULL );
    ~ExampleAnimatedTexturedRect();

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL( int width, int height ) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

public slots:
    void cleanup();
    void animate();

private:

    // Flame positions
    std::vector< std::pair< int, int > > m_positions;

};

}

#endif //SEVENGINE_WORKSHOP_04_EXAMPLE_HH
