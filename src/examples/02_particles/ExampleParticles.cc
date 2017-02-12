//
// Created by Eddie Hoyle on 13/11/16.
//

#include "ExampleParticles.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

#include <iostream>
#include <sev/Utilities.hh>
#include <sev/core/Transform.hh>

#include <QTimer>
#include <sev/graphics/render/RenderParticle.hh>
#include <sev/graphics/shader/ShaderManager.hh>

namespace E02 {

ExampleParticles::ExampleParticles(QWidget *parent)
        : QOpenGLWidget( parent )
{
    QTimer* aTimer = new QTimer;
    connect( aTimer, SIGNAL( timeout() ), this, SLOT( animate() ) );
    aTimer->start(30);
}

ExampleParticles::~ExampleParticles()
{
    cleanup();
}

void ExampleParticles::animate()
{
    /// TODO
}

void ExampleParticles::resizeGL( int width, int height )
{
    // TODO
}

void ExampleParticles::initializeGL() {

    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &ExampleParticles::cleanup );

    initializeOpenGLFunctions();

    glClearColor(1, 0.35, 0.35, 1);

    ShaderManager::instance();
}

void ExampleParticles::paintGL()
{
    ShaderManager::instance()->use( "particle" );
    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height(),
                                       -1.0f, 1.0f );
    ShaderManager::instance()->setUnif( "uf_Projection", false, projection );

//    glm::vec4 rgba = glm::vec4( 1.0, 0.0, 0.0, 1.0 );
//    ShaderManager::instance()->setAttr( "in_Color", rgba );

    // ------------------------------------------------------------

    Particle p;
    p.setPosition( glm::vec2( 100, 100) );
    p.setSize( 100.0 );
    p.setColor( 0, 0, 0, 255 );

    BufferParticle buffer;
    buffer.add( p );

    RenderParticle render( buffer );
    render.bind();

    ShaderManager::instance()->enable();

    render.draw();
    render.release();

    buffer.clear();

    ShaderManager::instance()->disable();
    ShaderManager::instance()->release();
}

void ExampleParticles::cleanup()
{
    // TODO
}

}