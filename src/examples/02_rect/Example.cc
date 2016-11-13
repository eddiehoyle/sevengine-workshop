//
// Created by Eddie Hoyle on 13/11/16.
//

#include "Example.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>

namespace E02 {

Example::Example(QWidget *parent)
        : QOpenGLWidget(parent) {
    /// TODO
}

void Example::initializeGL() {
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &Example::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0.35, 0.35, 0.35, 1);
}

void Example::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Example::cleanup() {
    makeCurrent();
    doneCurrent();
}

}