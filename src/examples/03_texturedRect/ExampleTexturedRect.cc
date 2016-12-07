//
// Created by Eddie Hoyle on 13/11/16.
//

#include "ExampleTexturedRect.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>

#include <sev/Utilities.hh>
#include <sev/core/Transform.hh>

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/glm.hpp>

#include <QTimer>

namespace E03 {

ExampleTexturedRect::ExampleTexturedRect(QWidget *parent)
        : QOpenGLWidget( parent )
{
    QTimer* aTimer = new QTimer;
    connect( aTimer, SIGNAL( timeout() ), this, SLOT( animate() ) );
    aTimer->start(30);
}

ExampleTexturedRect::~ExampleTexturedRect()
{
    cleanup();
}

void ExampleTexturedRect::animate()
{
    /// TODO
}

void ExampleTexturedRect::resizeGL( int width, int height )
{
    // TODO
}

void ExampleTexturedRect::initializeGL() {

    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &ExampleTexturedRect::cleanup );

    initializeOpenGLFunctions();

    glClearColor(1, 0.35, 0.35, 1);

    const char* vertexPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/texture.vert";
    const char* fragmentPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/texture.frag";

    const char* vertexShaderStr = readShaderFile( vertexPath );
    const char* fragmentShaderStr = readShaderFile( fragmentPath );

    m_shader = new Shader( vertexShaderStr, fragmentShaderStr );

    const char* path = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/cats.png";
    m_texture = new Texture2D( path );
    m_texture->setResizeMode( GL_LINEAR, GL_LINEAR );
    m_texture->setWrapMode( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );

    m_render = new RenderRect( m_shader );
}

void ExampleTexturedRect::paintGL()
{
    m_shader->use();

    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height() );
    m_shader->setUnif( "uf_Projection", false, projection );

    int size = 100;

    Transform transformA( glm::vec2( 0.0f, 0.0f ), 45.0f, glm::vec2( 1.0f, 1.0f ) );
    transformA.setPivot( glm::vec2( size / 2, size / 2 ) );
    Transform transformB = transformA;
    Transform transformC = transformA;
    Transform transformD = transformA;

    float offsetX =  width() / 2;
    float offsetY =  height() / 2;
    transformA.setPosition( offsetX - ( size / 2 ),
                            offsetY - ( size / 2 ) );
    transformA.setAngle( -15.0f );

    transformB.setPosition( offsetX - ( size / 2 ),
                            offsetY + ( size / 2 ) );
    transformB.setAngle( 10.0f );

    transformC.setPosition( offsetX + ( size / 2 ),
                            offsetY - ( size / 2 ) );
    transformC.setAngle( 20.0f );

    transformD.setPosition( offsetX + ( size / 2 ),
                            offsetY + ( size / 2 ) );
    transformD.setAngle( -20.0f );

    Quad a( size, size );
    a.setUV( 0.0, 0.5, 0.0, 0.5 );
    a.setMatrix( transformA.getMatrix() );

    Quad b( size, size );
    b.setUV( 0.5, 1.0, 0.5, 1.0 );
    b.setMatrix( transformB.getMatrix() );

    Quad c( size, size );
    c.setUV( 0.5, 1.0, 0.0, 0.5 );
    c.setMatrix( transformC.getMatrix() );

    Quad d( size, size );
    d.setUV( 0.0, 0.5, 0.5, 1.0 );
    d.setMatrix( transformD.getMatrix() );

    Texture2D::bind( m_texture, GL_TEXTURE0 );

    m_render->buffer( a );
    m_render->buffer( b );
    m_render->buffer( c );
    m_render->buffer( d );

    m_render->allocate();
    m_render->draw();
    m_render->release();

    Texture2D::release( m_texture );
}

void ExampleTexturedRect::cleanup()
{
    // TODO
}

}