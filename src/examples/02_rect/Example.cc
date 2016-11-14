//
// Created by Eddie Hoyle on 13/11/16.
//

#include "Example.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>

#include <sev/Utilities.hh>
//#include "../../Util.hh"

namespace E02 {

Example::Example(QWidget *parent)
        : QOpenGLWidget( parent )
{
    // TODO
}

Example::~Example()
{
    cleanup();
}

void Example::resizeGL( int width, int height )
{
    // TODO
}

void Example::initializeGL() {

    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &Example::cleanup );

    initializeOpenGLFunctions();
//    printContextInformation( context(), format() );

    glClearColor(1, 0.35, 0.35, 1);

    const char* vertexPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/simple.vert";
    const char* fragmentPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/simple.frag";

    const char* vertexShaderStr = readShaderFile( vertexPath );
    const char* fragmentShaderStr = readShaderFile( fragmentPath );

    m_shader = new Shader( vertexShaderStr, fragmentShaderStr );
    m_shader->bindAttr( 0, "in_Position" );

    const char* path = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/cat.png";
    m_texture = new Texture( GL_TEXTURE_2D, path, 256, 256 );

    m_render = new RenderRect( m_shader, m_texture );
}

void Example::paintGL()
{
    qDebug( "E02::Example::paintGL()" );

    m_shader->use();

    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height(),
                                       -1.0f, 1.0f );
    m_shader->setUnif( "uf_Projection", false, projection );

    glm::vec4 rgba = glm::vec4( 0.4, 0.2, 0.2, 1.0 );
    m_shader->setUnif( "uf_Color", rgba );

    int size = 100;
    int offsetX = ( width() / 2 ) - ( size / 2 );
    int offsetY = ( height() / 2 )- ( size / 2 );

    Quad a( size, size );
    a.setTranslate( glm::vec2( offsetX, offsetY ) );

    m_render->buffer( a );
    m_render->draw();

}

void Example::cleanup()
{
    // TODO
}

}