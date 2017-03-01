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
#include <sev/graphics/shader/ShaderManager.hh>
#include <sev/graphics/texture/TextureManager2D.hh>
#include <sev/graphics/render/QuadRender.hh>

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

    ShaderManager::instance();

    const char* path = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/cats.png";
    TextureManager2D::instance()->load( "cats", path );
}

void ExampleTexturedRect::paintGL()
{
    ShaderManager::instance()->use( "texture" );
    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height() );
    ShaderManager::instance()->setUnif( "uf_Projection", false, projection );
    ShaderManager::instance()->setUnif( "uf_Texture", 0 );

    TextureManager2D::instance()->bind( "cats", 0 );
    TextureManager2D::instance()->setResizeMode( GL_NEAREST, GL_NEAREST );
    TextureManager2D::instance()->setWrapMode( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );

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
    a.setColor( 255, 255, 255, 50 );

    Quad b( size, size );
    b.setUV( 0.5, 1.0, 0.5, 1.0 );
    b.setMatrix( transformB.getMatrix() );
    b.setColor( 255, 255, 255, 50 );

    Quad c( size, size );
    c.setUV( 0.5, 1.0, 0.0, 0.5 );
    c.setMatrix( transformC.getMatrix() );
    c.setColor( 255, 255, 255, 50 );

    Quad d( size, size );
    d.setUV( 0.0, 0.5, 0.5, 1.0 );
    d.setMatrix( transformD.getMatrix() );
    d.setColor( 255, 255, 255, 50 );

    QuadBuffer buffer = QuadBuffer();
    buffer.add( a );
    buffer.add( b );
    buffer.add( c );
    buffer.add( d );

    QuadRender render = QuadRender( buffer );
    render.bind();

    ShaderManager::instance()->enable();

    render.draw();
    render.release();

    buffer.clear();
    ShaderManager::instance()->disable();
    ShaderManager::instance()->release();
}

void ExampleTexturedRect::cleanup()
{
    TextureManager2D::instance()->unload( "bomb" );
}

}