//
// Created by Eddie Hoyle on 13/11/16.
//

#include "Example.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>

#include <sev/Utilities.hh>
#include <sev/core/Transform.hh>


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

    m_render = new RenderRect( m_shader );
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

    Transform transform( glm::vec2( 0.0f, 0.0f ), 0.0f, glm::vec2( 1.0f, 1.0f ) );
    transform.setPivot( glm::vec2( size / 2, size / 2 ) );
    transform.setPosition( offsetX, offsetY );

    Quad a( size, size );
    a.setMatrix( transform.getMatrix() );

    m_render->buffer( a );
    m_render->draw();

}

void Example::cleanup()
{
    // TODO
}

}