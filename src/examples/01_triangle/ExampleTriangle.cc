//
// Created by Eddie Hoyle on 13/11/16.
//

#include "ExampleTriangle.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>
#include <glm/glm.hpp>

#include <sev/Utilities.hh>
#include <sev/core/Shader.hh>
#include <sev/graphics/Vertex.hh>

#include "../../Util.hh"

#include <QTimer>

namespace E01 {

ExampleTriangle::ExampleTriangle(QWidget *parent)
        : QOpenGLWidget( parent )
{
    QTimer* aTimer = new QTimer;
    connect( aTimer, SIGNAL( timeout() ), this, SLOT( animate() ) );
    aTimer->start(30);
}

ExampleTriangle::~ExampleTriangle()
{
    cleanup();
}

void ExampleTriangle::animate()
{
    /// TODO
}

void ExampleTriangle::resizeGL( int width, int height )
{
    // TODO
}

void ExampleTriangle::initializeGL()
{
    qDebug( "E01::ExampleTriangle::initializeGL()" );
    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &ExampleTriangle::cleanup );

    initializeOpenGLFunctions();
    printContextInformation( context(), format() );

    glClearColor(1, 0.35, 0.35, 1);

    const char* vertexPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/simple.vert";
    const char* fragmentPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/simple.frag";

    const char* vertexShaderStr = readShaderFile( vertexPath );
    const char* fragmentShaderStr = readShaderFile( fragmentPath );

    m_shader = new Shader( vertexShaderStr, fragmentShaderStr );
    m_shader->bindAttr( 0, "in_Position" );
}

void ExampleTriangle::paintGL() {

    qDebug( "E01::ExampleTriangle::paintGL()" );

    m_shader->use();

    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height(),
                                       -1.0f, 1.0f );
    m_shader->setUnif( "uf_Projection", false, projection );

    glm::vec4 rgba = glm::vec4( 0.4, 0.2, 0.2, 1.0 );
    m_shader->setUnif( "uf_Color", rgba );

    GLuint vbo, ebo;
    glGenBuffers( 1, &vbo );
    glGenBuffers( 1, &ebo );

    Vertex v1, v2, v3;
    GLubyte r, g, b, a;
    float size = 100;
    float cx = width() / 2;
    float cy = height() / 2;
    v1.set( cx - size, cy - size, 0.0, 0.0f, r, g, b, a );
    v2.set( cx, cy + size, 0.0, 0.0f, r, g, b, a );
    v3.set( cx + size, cy - size, 0.0, 0.0f, r, g, b, a );
    Vertex vertices[3] = {
            v1, v2, v3
    };

    GLuint elements[3] = {
            0, 1, 2,
    };

    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, 3 * sizeof( Vertex ), vertices, GL_STATIC_DRAW );

    GLuint stride = sizeof( Vertex );
    glVertexAttribPointer( m_shader->getAttrHandle( "in_Position" ), 2, GL_FLOAT, GL_FALSE, stride, ( void * ) + 0 );
    glVertexAttribPointer( m_shader->getAttrHandle( "in_TextureUV" ), 2, GL_FLOAT, GL_FALSE, stride, ( void * ) + 2 );

    glEnableVertexAttribArray( m_shader->getAttrHandle( "in_Position" ) );
    glEnableVertexAttribArray( m_shader->getAttrHandle( "in_TextureUV" ) );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof( GLuint ), elements, GL_STATIC_DRAW );

    checkError();

    glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0 );

    glDeleteBuffers( 1, &vbo );
    glDeleteBuffers( 1, &ebo );
}

void ExampleTriangle::cleanup()
{
    // TODO
}

}