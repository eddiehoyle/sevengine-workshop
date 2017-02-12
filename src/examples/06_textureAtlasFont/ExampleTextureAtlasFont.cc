//
// Created by Eddie Hoyle on 13/11/16.
//

#include "ExampleTextureAtlasFont.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>

#include <sev/Utilities.hh>
#include <sev/core/Transform.hh>

#include <QTimer>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <ft2build.h>
#include <sev/graphics/shader/ShaderManager.hh>
#include FT_FREETYPE_H
#include FT_TYPES_H

namespace E06 {

ExampleTextureAtlasFont::ExampleTextureAtlasFont(QWidget *parent)
        : QOpenGLWidget( parent )
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

    const char* path = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/simpleFont.png";
//    m_texture = new Texture2D( path );
//    m_texture->setResizeMode( GL_NEAREST, GL_NEAREST );
//    m_texture->setWrapMode( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );

}

void ExampleTextureAtlasFont::paintGL()
{
    // TODO
}

void ExampleTextureAtlasFont::cleanup()
{
    // TODO
}

}