//
// Created by Eddie Hoyle on 13/11/16.
//

#include "ExampleRect.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>

#include <sev/Utilities.hh>
#include <sev/core/Transform.hh>

#include <QTimer>

namespace E02 {

ExampleRect::ExampleRect(QWidget *parent)
        : QOpenGLWidget( parent )
{
    QTimer* aTimer = new QTimer;
    connect( aTimer, SIGNAL( timeout() ), this, SLOT( animate() ) );
    aTimer->start(30);
}

ExampleRect::~ExampleRect()
{
    cleanup();
}

void ExampleRect::animate()
{
    /// TODO
}

void ExampleRect::resizeGL( int width, int height )
{
    // TODO
}

void ExampleRect::initializeGL() {

    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &ExampleRect::cleanup );

    initializeOpenGLFunctions();
//    printContextInformation( context(), format() );

    glClearColor(1, 0.35, 0.35, 1);

    const char* vertexPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/simple.vert";
    const char* fragmentPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/simple.frag";

    const char* vertexShaderStr = readShaderFile( vertexPath );
    const char* fragmentShaderStr = readShaderFile( fragmentPath );

//    m_shader = new Shader( vertexShaderStr, fragmentShaderStr );
//    m_shader->bindAttr( 0, "in_Position" );

    m_render = new RenderRect();
}

void ExampleRect::paintGL()
{
    qDebug( "E02::ExampleTriangle::paintGL()" );

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

void ExampleRect::cleanup()
{
    // TODO
}

}