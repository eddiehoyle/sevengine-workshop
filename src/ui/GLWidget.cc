//
// Created by Eddie Hoyle on 12/11/16.
//

#include "GLWidget.hh"

GLWidget::GLWidget( QWidget* parent )
        : QOpenGLWidget( parent )
{
    /// TODO
}

void GLWidget::initializeGL()
{
    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup );

    initializeOpenGLFunctions();
    glClearColor(0.35, 0.35, 0.35, 1);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWidget::cleanup()
{
    makeCurrent();
    doneCurrent();
}