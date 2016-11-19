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

    const char* path = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/cat.png";
    m_texture = new Texture( GL_TEXTURE_2D, path, 100, 200 );

    m_render = new RenderRect( m_shader );
}

void Example::paintGL()
{
    qDebug( "E03::Example::paintGL()" );

    m_shader->use();

//    glActiveTexture( GL_TEXTURE0 );
//    glBindTexture( m_texture->getTarget(), m_texture->getHandle() );
//    glUniform1i( m_shader->getUnifHandle( "uf_Texture" ), 0 );



    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height(),
                                       -1.0f, 1.0f );
    m_shader->setUnif( "uf_Projection", false, projection );

//    glm::vec4 rgba = glm::vec4( 0.4, 0.2, 0.2, 1.0 );
//    m_shader->setUnif( "uf_Color", rgba );

    int size = 100;
    int offsetX = ( width() / 2 ) - ( size / 2 );
    int offsetY = ( height() / 2 )- ( size / 2 );

    Quad a( size, size );
    Quad b( 50, 100 );
    a.setTranslate( glm::vec2( offsetX, offsetY ) );
    a.setTranslate( glm::vec2( 30, 60) );

    Texture::bind( m_texture );

    m_render->buffer( a );
    m_render->buffer( b );
    m_render->allocate();
    m_render->draw();
    m_render->release();

    Texture::unbind( m_texture );


    // ----------------------------------------------------------------------------- //

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
//    GLuint vbo, ebo;
//    glGenBuffers( 1, &vbo );
//    glGenBuffers( 1, &ebo );
//
//    Vertex a, b, c, d;
//    float size = 100;
//    float x = ( width() / 2 ) - ( size / 2 );
//    float y = ( height() / 2 ) - ( size / 2 );
//
//    Quad q = Quad( size, size );
//    q.setTranslate( glm::vec2( x, y ) );
//
//    Vertex vertices[4] = {
//            q.bl, q.tl, q.tr, q.br
//    };
//
//    GLuint elements[6] = {
//            0, 1, 2, 0, 2, 3
//    };
//
//    glActiveTexture( GL_TEXTURE0 );
//    glBindTexture( m_texture->getTarget(), m_texture->getHandle() );
//    glUniform1i( m_shader->getUnifHandle( "uf_Texture" ), 0 );
//
//    glBindBuffer( GL_ARRAY_BUFFER, vbo );
//    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ) * sizeof( Vertex ), vertices, GL_STATIC_DRAW );
//
//    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
//    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( vertices ) * sizeof( GLuint ), elements, GL_STATIC_DRAW );
//
//    glEnableVertexAttribArray( m_shader->getAttrHandle( "in_Position" ) );
//    glEnableVertexAttribArray( m_shader->getAttrHandle( "in_TextureUV" ) );
//
//    GLuint stride = sizeof( Vertex );
//    glVertexAttribPointer( m_shader->getAttrHandle( "in_Position" ), 2, GL_FLOAT, GL_FALSE, stride, BufferOffset( 0 ) );
//    glVertexAttribPointer( m_shader->getAttrHandle( "in_TextureUV" ), 2, GL_FLOAT, GL_FALSE, stride, BufferOffset( 8 ) );
//
////    std::cerr << "in_Position: " << m_shader->getAttrHandle( "in_Position" ) << std::endl;
////    std::cerr << "in_TextureUV: " << m_shader->getAttrHandle( "in_TextureUV" ) << std::endl;
//
//
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//
//    glDrawElements( GL_TRIANGLES, sizeof( elements ), GL_UNSIGNED_INT, 0 );
//
//    checkError();
//
//    glDeleteBuffers( 1, &vbo );
//    glDeleteBuffers( 1, &ebo );
//    glDisableVertexAttribArray( m_shader->getAttrHandle( "in_Position" ) );
//    glDisableVertexAttribArray( m_shader->getAttrHandle( "in_TextureUV" ) );
//    glUseProgram( 0 );
//    Texture::unbind( m_texture );

}

void Example::cleanup()
{
    // TODO
}

}