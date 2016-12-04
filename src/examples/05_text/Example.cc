//
// Created by Eddie Hoyle on 13/11/16.
//

#include "Example.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>

#include <sev/Utilities.hh>
#include <sev/core/Transform.hh>

#include <QTimer>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_TYPES_H

namespace E05 {

Example::Example(QWidget *parent)
        : QOpenGLWidget( parent )
{
//    QTimer* aTimer = new QTimer;
//    connect( aTimer, SIGNAL( timeout() ), this, SLOT( animate() ) );
//    aTimer->start(30);
}

Example::~Example()
{
    cleanup();
}

void Example::animate()
{
    update();
}

void Example::resizeGL( int width, int height )
{
    // TODO
}

void Example::initializeGL() {

    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &Example::cleanup );

    FT_Library library;
    FT_Face face;

    int error;

    error = FT_Init_FreeType( &library );
    if ( error ) {
        std::cerr << "Failed to init freetype: " << error << std::endl;
    } else {
        std::cerr << "FT init successful" << std::endl;
    }

    error = FT_New_Face( library,
                         "/Library/Fonts/Arial.ttf",
                         0,
                         &face );
    if ( error == FT_Err_Unknown_File_Format )
    {
        std::cerr << "Error loading face: FT_Err_Unknown_File_Format" << std::endl;
    }
    else if ( error )
    {
        std::cerr << "Error loading face: " << error << std::endl;
    } else {
        std::cerr << "FT face init successful" << std::endl;

    }

    // ----------------------------------------------------------------------------------------

    initializeOpenGLFunctions();

    glClearColor(1, 0.35, 0.35, 1);

    const char* vertexPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/texture.vert";
    const char* fragmentPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/texture.frag";

    const char* vertexShaderStr = readShaderFile( vertexPath );
    const char* fragmentShaderStr = readShaderFile( fragmentPath );

    m_shader = new Shader( vertexShaderStr, fragmentShaderStr );

    const char* path = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/bomb.png";
    m_texture = new Texture2D( path );
    m_texture->setResizeMode( GL_NEAREST, GL_NEAREST );
    m_texture->setWrapMode( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );

    m_render = new RenderRect( m_shader );
}

void Example::paintGL()
{
    m_shader->use();

    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height() );
    m_shader->setUnif( "uf_Projection", false, projection );

    int size = 100;
    Transform transform( glm::vec2( 0.0f, 0.0f ), 0.0f, glm::vec2( 1.0f, 1.0f ) );
    transform.setPivot( glm::vec2( size / 2, size / 2 ) );

    Quad a( size, size );
    a.setUV( 0.0, 1.0, 0.0, 1.0 );
    a.setMatrix( transform.getMatrix() );

    Texture2D::bind( m_texture, GL_TEXTURE0 );

    m_render->buffer( a );
    m_render->allocate();
    m_render->draw();
    m_render->release();

    Texture2D::release( m_texture );
}

void Example::cleanup()
{
    // TODO
}

}