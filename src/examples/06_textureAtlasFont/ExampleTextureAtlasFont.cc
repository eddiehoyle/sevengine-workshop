//
// Created by Eddie Hoyle on 13/11/16.
//

#include "ExampleTextureAtlasFont.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>

#include <sev/Utilities.hh>
#include <sev/core/Transform.hh>

#include <sev/graphics/font/Char.hh>
#include <sev/graphics/font/FontParser.hh>
#include <QTimer>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <ft2build.h>
#include <sev/graphics/shader/ShaderManager.hh>
#include <sev/graphics/texture/TextureManager2D.hh>
#include <sev/graphics/render/QuadRender.hh>
#include FT_FREETYPE_H
#include FT_TYPES_H

namespace E06 {

ExampleTextureAtlasFont::ExampleTextureAtlasFont(QWidget *parent)
        : QOpenGLWidget( parent ), m_charSet()
{
    QTimer* aTimer = new QTimer;
    connect( aTimer, SIGNAL( timeout() ), this, SLOT( animate() ) );
    aTimer->start(30);
}

ExampleTextureAtlasFont::~ExampleTextureAtlasFont()
{
    cleanup();
}

void ExampleTextureAtlasFont::animate()
{
    update();
}

void ExampleTextureAtlasFont::resizeGL( int width, int height )
{
    // TODO
}

void ExampleTextureAtlasFont::initializeGL() {

    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &ExampleTextureAtlasFont::cleanup );

    initializeOpenGLFunctions();

    glClearColor(1, 0.35, 0.35, 1);

    ShaderManager::instance();

    const std::string path = "/Users/eddiehoyle/Code/cpp/game/sevengine/resources/font/font.png";
    TextureManager2D::instance()->load( "font", path, true );


    const std::string fontPath = "/Users/eddiehoyle/Code/cpp/game/sevengine/resources/font/font.fnt";
    font::load( fontPath, m_charSet );

}

void ExampleTextureAtlasFont::paintGL() {

//    std::cerr << "ExampleTextureAtlasFont::paintGL()" << std::endl;


    ShaderManager::instance()->use( "texture" );
    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height(),
                                       -1.0f, 1.0f );
    ShaderManager::instance()->setUnif( "uf_Projection", false, projection );
    ShaderManager::instance()->setUnif( "uf_Texture", 0 );

    // Tell 'uf_Texture' sampler in fragment shader to use the texture bound to GL_TEXTURE0
    TextureManager2D::instance()->bind( "font", 0 );
    TextureManager2D::instance()->setResizeMode( GL_LINEAR, GL_LINEAR );
    TextureManager2D::instance()->setWrapMode( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );

    // ----------------------------------------------------------------

    font::Char a = font::getChar( m_charSet, ( int )'b' );
    font::Char b = font::getChar( m_charSet, ( int )'b' );
    font::Char c = font::getChar( m_charSet, ( int )'c' );

    font::printChar( a );

    Quad quad( a.width, a.height );
    quad.setUV( a.uvs[0], a.uvs[1], a.uvs[2], a.uvs[3] );

    Transform t;
    t.setPosition( glm::vec2( 0, 0 ) );
    quad.setMatrix( t.getMatrix() );

    BufferQuad buffer;
    buffer.add( quad );

    QuadRender render = QuadRender( buffer );
    render.bind();

    ShaderManager::instance()->enable();

    render.draw();
    render.release();

    buffer.clear();
    ShaderManager::instance()->disable();
    ShaderManager::instance()->release();
}

void ExampleTextureAtlasFont::cleanup()
{
//    TextureManager2D::instance()->unload( "font" );
}

}