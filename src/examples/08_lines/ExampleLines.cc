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
#include <QTimer>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <ctime> // Needed for the true randomization
#include <cstdlib>
#include <random>


namespace E08 {

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

}

void ExampleLines::cleanup() {

}

}