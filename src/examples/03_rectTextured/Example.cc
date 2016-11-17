//
// Created by Eddie Hoyle on 13/11/16.
//

#include "Example.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>

#include <sev/Utilities.hh>
//#include "../../Util.hh"

namespace E03 {

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

    const char* vertexPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/texture.vert";
    const char* fragmentPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/texture.frag";

    const char* vertexShaderStr = readShaderFile( vertexPath );
    const char* fragmentShaderStr = readShaderFile( fragmentPath );

    m_shader = new Shader( vertexShaderStr, fragmentShaderStr );
    m_shader->bindAttr( 0, "in_Position" );
    m_shader->bindAttr( 1, "in_TextureUV" );
    checkError();

    const char* path = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/cat.png";
    m_texture = new Texture( GL_TEXTURE_2D, path, 200, 200 );

    m_render = new RenderRect( m_shader, m_texture );
}

void Example::paintGL()
{
    qDebug( "E03::Example::paintGL()" );

//    m_shader->use();
//
//    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
//                                       0.0f, ( float )height(),
//                                       -1.0f, 1.0f );
//    m_shader->setUnif( "uf_Projection", false, projection );
//
//    glm::vec4 rgba = glm::vec4( 0.4, 0.2, 0.2, 1.0 );
//    m_shader->setUnif( "uf_Color", rgba );
//
//    int size = 100;
//    int offsetX = ( width() / 2 ) - ( size / 2 );
//    int offsetY = ( height() / 2 )- ( size / 2 );
//
//    Quad a( size, size );
//    a.setTranslate( glm::vec2( offsetX, offsetY ) );
//
//    m_render->buffer( a );
//    m_render->draw();

    // ----------------------------------------------------------------------------- //

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

    Vertex a, b, c, d;
    float size = 100;
    float x = ( width() / 2 ) - ( size / 2 );
    float y = ( height() / 2 ) - ( size / 2 );

    Quad q = Quad( size, size );
    q.setTranslate( glm::vec2( x, y ) );

    Vertex vertices[4] = {
            q.bl, q.tl, q.tr, q.br
    };

    GLuint elements[6] = {
            0, 1, 2, 0, 2, 3
    };

    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ) * sizeof( Vertex ), vertices, GL_STATIC_DRAW );

    GLuint stride = sizeof( Vertex );
    glVertexAttribPointer( m_shader->getAttrHandle( "in_Position" ), 4, GL_FLOAT, GL_FALSE, stride, ( void * ) + 0 );
    glEnableVertexAttribArray( m_shader->getAttrHandle( "in_Position" ) );

//    glVertexAttribPointer( m_shader->getAttrHandle( "in_Position" ), 2, GL_FLOAT, GL_FALSE, stride, ( void * ) + 2 );
//    glEnableVertexAttribArray( m_shader->getAttrHandle( "in_Position" ) );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( vertices ) * sizeof( GLuint ), elements, GL_STATIC_DRAW );

//    glActiveTexture( GL_TEXTURE0);
//    glBindTexture( GL_TEXTURE_2D, m_shader->getUnifHandle( "uf_Texture" ) );
//    glUniform1i( m_shader->getUnifHandle( "uf_Texture" ), 0 );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( m_texture->getTarget(), m_texture->getHandle() );
//    glUniform1i( m_shader->getUnifHandle( "uf_Texture" ), 0 );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );



    glDrawElements( GL_TRIANGLES, sizeof( elements ), GL_UNSIGNED_INT, 0 );

    checkError();

    glDeleteBuffers( 1, &vbo );
    glDeleteBuffers( 1, &ebo );
    Texture::unbind( m_texture );

}

void Example::cleanup()
{
    // TODO
}

}