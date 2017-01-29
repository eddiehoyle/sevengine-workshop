//
// Created by Eddie Hoyle on 13/11/16.
//

#ifndef SEVENGINE_WORKSHOP_06_EXAMPLE_HH
#define SEVENGINE_WORKSHOP_06_EXAMPLE_HH

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

#include <sev/graphics/Texture.hh>
#include <sev/graphics/render/RenderRect.hh>

namespace E06 {

class ExampleTextureAtlasFont
        : public QOpenGLWidget,
          protected QOpenGLFunctions
{
    Q_OBJECT

public:
    struct Character {
        GLuint     TextureID;  // ID handle of the glyph texture
        glm::ivec2 Size;       // Size of glyph
        glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
        GLuint     Advance;    // Offset to advance to next glyph
    };

    std::map<GLchar, Character> Characters;

public:
    explicit ExampleTextureAtlasFont( QWidget* parent = NULL );
    ~ExampleTextureAtlasFont();

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL( int width, int height ) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

public slots:
    void cleanup();
    void animate();

private:
//    Shader* m_shader;
    Texture2D* m_texture;
    RenderRect* m_render;

};

}

#endif //SEVENGINE_WORKSHOP_06_EXAMPLE_HH
