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
    qDebug( "E02::ExampleTriangle::paintGL()" );

    ShaderManager::instance()->use( "particle" );
    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height(),
                                       -1.0f, 1.0f );
    ShaderManager::instance()->setUnif( "uf_Projection", false, projection );

//    m_shader->use();

//    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
//                                       0.0f, ( float )height(),
//                                       -1.0f, 1.0f );
//    m_shader->setUnif( "uf_Projection", false, projection );
//
//    glm::vec4 rgba = glm::vec4( 0.4, 0.2, 0.2, 1.0 );
//    m_shader->setUnif( "uf_Color", rgba );

    int size = 100;
    int offsetX = ( width() / 2 ) - ( size / 2 );
    int offsetY = ( height() / 2 )- ( size / 2 );

    Transform transform( glm::vec2( 0.0f, 0.0f ), 0.0f, glm::vec2( 1.0f, 1.0f ) );
    transform.setPivot( glm::vec2( size / 2, size / 2 ) );
    transform.setPosition( offsetX, offsetY );

    Quad a( size, size );
    a.setMatrix( transform.getMatrix() );

    m_render->buffer( a );
    m_render->bind();
    m_render->draw();
    m_render->release();


}

void ExampleParticles::cleanup()
{
    // TODO
}

}