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

    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &ExampleFreeTypeFont::cleanup );

    initializeOpenGLFunctions();

    glClearColor(1, 0.35, 0.35, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    const char* vertexPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/texture.vert";
    const char* fragmentPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/texture.frag";

    const char* vertexShaderStr = readShaderFile( vertexPath );
    const char* fragmentShaderStr = readShaderFile( fragmentPath );

    m_shader = new Shader( vertexShaderStr, fragmentShaderStr );

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