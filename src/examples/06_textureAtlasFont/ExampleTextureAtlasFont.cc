//
// Created by Eddie Hoyle on 13/11/16.
//

#include "ExampleTextureAtlasFont.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>

#include <sev/Utilities.hh>
#include <sev/core/Transform.hh>

#include <sev/graphics/text/Glyph.hh>
#include <sev/graphics/text/FontParser.hh>
#include <QTimer>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <ft2build.h>
#include <sev/graphics/shader/ShaderManager.hh>
#include <sev/graphics/texture/TextureManager2D.hh>
#include <sev/graphics/render/QuadRender.hh>
#include <sev/graphics/text/Block.hh>
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

//    font::Char h = font::fromChar( m_charSet, 'h' );
//    font::Char e = font::fromChar( m_charSet, 'e' );
//    font::Char y = font::fromChar( m_charSet, 'y' );
//
//    Quad hQuad( h.width, h.height );
//    Quad eQuad( e.width, e.height );
//    Quad yQuad( y.width, y.height );
//
//    hQuad.setUV( h.uvs[0], h.uvs[1], h.uvs[2], h.uvs[3] );
//    eQuad.setUV( e.uvs[0], e.uvs[1], e.uvs[2], e.uvs[3] );
//    yQuad.setUV( y.uvs[0], y.uvs[1], y.uvs[2], y.uvs[3] );
//
//    Transform hTransform;
//    Transform eTransform;
//    Transform yTransform;
//
//    hTransform.setPosition( glm::vec2( 120, 100 ) );
//    eTransform.setPosition( glm::vec2( 150, 110 ) );
//    eTransform.setAngle( 10 );
//    yTransform.setPosition( glm::vec2( 190, 90 ) );
//    yTransform.setAngle(-15);
//
//    hQuad.setMatrix( hTransform.getMatrix() );
//    eQuad.setMatrix( eTransform.getMatrix() );
//    yQuad.setMatrix( yTransform.getMatrix() );
//
//
//    BufferQuad buffer;
//    buffer.add( hQuad );
//    buffer.add( eQuad );
//    buffer.add( yQuad );

    // ----------------------------------------------------------------

    TextBlock block;
    block.setLineWidth( 25 );
    block.setLineHeight( 50 );
    block.setGlyphScale( 1.0 );
    block.setSpaceScale( 3.0 );
    block.setText( "TEST WORDS" );

    Transform transform;
    transform.setPosition( 050, 50 );

    Quads quads;
    block.getQuads( m_charSet, quads );

    BufferQuad buffer;
    buffer.add( quads );

    QuadRender render = QuadRender( buffer );
    render.bind();

    ShaderManager::instance()->enable();

    render.draw();
    render.release();

    block.setMatrix( transform.getMatrix() );
    buffer.clear();
    ShaderManager::instance()->disable();
    ShaderManager::instance()->release();
}

void ExampleTextureAtlasFont::cleanup() {
    TextureManager2D::instance()->unload( "font" );
}

}