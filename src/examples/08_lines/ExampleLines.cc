//
// Created by Eddie Hoyle on 25/02/17.
//

#include "ExampleLines.hh"


#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>

#include <sev/Utilities.hh>
#include <sev/core/Transform.hh>
#include <sev/graphics/shader/ShaderManager.hh>
#include <sev/graphics/texture/TextureManager2D.hh>
#include <sev/graphics/render/QuadRender.hh>
#include <sev/graphics/render/LineRender.hh>

#include <QTimer>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <ctime> // Needed for the true randomization
#include <cstdlib>
#include <random>


namespace E08 {

static glm::vec2 clickPos = glm::vec2( 0, 0 );

ExampleLines::ExampleLines(QWidget *parent)
        : QOpenGLWidget( parent ) {

    QTimer* aTimer = new QTimer;
    QObject::connect( aTimer, SIGNAL( timeout() ), this, SLOT( animate() ) );
    aTimer->start( 15 );
}

ExampleLines::~ExampleLines() {
    cleanup();
}

void ExampleLines::animate() {
    update();
}

void ExampleLines::resizeGL( int width, int height ) {
}

void ExampleLines::initializeGL() {

    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &ExampleLines::cleanup );

    initializeOpenGLFunctions();

    glClearColor(1, 0.35, 0.35, 1);

    ShaderManager::instance();

}

void ExampleLines::paintGL() {

    ShaderManager::instance()->use( "texture" );
    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height() );
    ShaderManager::instance()->setUnif( "uf_Projection", false, projection );

    float thickness = 10;

    Line line0, line1, line2, line3;
    line0.set( glm::vec2( 0, 0 ), clickPos, 0, 255, 0, 255, thickness );
    line1.set( glm::vec2( width(), 0 ), clickPos, 0, 255, 0, 255, thickness );
    line2.set( glm::vec2( 0, height() ), clickPos, 0, 255, 0, 255, thickness );
    line3.set( glm::vec2( width(), height() ), clickPos, 0, 255, 0, 255, thickness );

    LineBuffer buffer;
    buffer.add( line0 );
    buffer.add( line1 );
    buffer.add( line2 );
    buffer.add( line3 );

    LineRender render( buffer );
    render.bind();

    ShaderManager::instance()->enable();

    render.draw();
    render.release();

    ShaderManager::instance()->disable();
    ShaderManager::instance()->release();
}

void ExampleLines::cleanup() {

}

void ExampleLines::mouseMoveEvent( QMouseEvent *event ) {
    clickPos.x = event->x();
    clickPos.y = height() - event->y();
}

}