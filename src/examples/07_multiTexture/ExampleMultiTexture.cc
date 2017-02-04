//
// Created by Eddie Hoyle on 31/01/17.
//

#include "ExampleMultiTexture.hh"

#include <QTimer>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <sev/core/Transform.hh>


namespace E07 {

ExampleMultiTexture::ExampleMultiTexture(QWidget *parent)
        : QOpenGLWidget( parent ),
          m_bomb( 0 ),
          m_cat( 0 ) {

    QTimer* aTimer = new QTimer;
    QObject::connect( aTimer, SIGNAL( timeout() ), this, SLOT( animate() ) );
    aTimer->start( 15 );
}

ExampleMultiTexture::~ExampleMultiTexture() {

    cleanup();

    if ( m_bomb ) {
        delete m_bomb;
    }
}

void ExampleMultiTexture::animate() {
    update();
}

void ExampleMultiTexture::resizeGL( int width, int height ) {
    // TODO
}

void ExampleMultiTexture::initializeGL() {

    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &ExampleMultiTexture::cleanup );

    initializeOpenGLFunctions();

    glClearColor(1, 0.35, 0.35, 1);

    ShaderManager::instance();

    // Old way
    const char* bombPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/bomb.png";
    m_bomb = new Texture2D( bombPath );
    m_bomb->setResizeMode( GL_NEAREST, GL_NEAREST );
    m_bomb->setWrapMode( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );

    // Old way
    const char* catPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/cat.png";
    m_cat = new Texture2D( catPath );
    m_cat->setResizeMode( GL_NEAREST, GL_NEAREST );
    m_cat->setWrapMode( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );

}

void ExampleMultiTexture::paintGL() {

    ShaderManager::instance()->use( "texture" );
    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height() );
    ShaderManager::instance()->setUnif( "uf_Projection", false, projection );

    // Textures need to be bound to units for each draw tick.
    // Not sure why this is yet...
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, m_bomb->getHandle() );

    glActiveTexture( GL_TEXTURE0 + 1 );
    glBindTexture( GL_TEXTURE_2D, m_cat->getHandle() );

    // --------------------------------------------------------------------------------

    int size = 100;
    Transform transform( glm::vec2( 0, 0 ), 0.0f, glm::vec2( 1.0f, 1.0f ) );
    transform.setPivot( glm::vec2( size / 2, size / 2 ) );
    transform.setAngle( 0.0f );
    transform.setPosition( glm::vec2( 100, 100 ));
    transform.setScale( 1.0f, 1.0f );

    // --------------------------------------------------------------------------------

    // Bomb
    Quad bombQuad( size, size );
    bombQuad.setUV( 0.0, 1.0, 0.0, 1.0 );
    bombQuad.setMatrix( transform.getMatrix() );

    BufferQuad bombBuffer = BufferQuad();
    bombBuffer.add( bombQuad );

    RenderQuad bombRender = RenderQuad( bombBuffer );
    bombRender.bind();

    ShaderManager::instance()->enable();

    // Tell 'uf_Texture' sampler in fragment shader to use the texture bound to GL_TEXTURE0
    ShaderManager::instance()->setUnif( "uf_Texture", 0 );

    bombRender.draw();
    bombBuffer.clear();

    // --------------------------------------------------------------------------------


    // Cat
    Quad catQuad( size, size );
    catQuad.setUV( 0.0, 1.0, 0.0, 1.0 );

    Transform catTransform = transform;
    catTransform.setPosition( glm::vec2( 200, 100 ) );
    catQuad.setMatrix( catTransform.getMatrix() );

    BufferQuad catBuffer;
    catBuffer.add( catQuad );

    RenderQuad catRender = RenderQuad( catBuffer );
    catRender.bind();

    ShaderManager::instance()->enable();

    // Tell 'uf_Texture' sampler in fragment shader to use the texture bound to GL_TEXTURE1
    ShaderManager::instance()->setUnif( "uf_Texture", 1 );

    catRender.draw();
    catBuffer.clear();

    // --------------------------------------------------------------------------------

    ShaderManager::instance()->disable();
    ShaderManager::instance()->release();
    Texture2D::release( m_bomb );
    Texture2D::release( m_cat );

}

void ExampleMultiTexture::cleanup()
{
    qDebug( "Cleaning up" );
}

}