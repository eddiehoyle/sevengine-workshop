//
// Created by Eddie Hoyle on 13/11/16.
//

#include "Example.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>
#include <glm/glm.hpp>

#include <sev/Utilities.hh>
#include <sev/core/Shader.hh>
#include <sev/graphics/Vertex.hh>

namespace E01 {

Example::Example(QWidget *parent)
        : QOpenGLWidget(parent) {

    /// TODO
}

void Example::resizeGL( int width, int height )
{
    /// TODO
}

void Example::initializeGL() {
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &Example::cleanup);

    // Initialize OpenGL Backend
    initializeOpenGLFunctions();

    glClearColor(0.35, 0.35, 0.35, 1);

    const char* vertexPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/simple.vert";
    const char* fragmentPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/simple.frag";

    const char* vertexShaderStr = readShaderFile( vertexPath );
    const char* fragmentShaderStr = readShaderFile( fragmentPath );

    m_shader = new Shader( vertexShaderStr, fragmentShaderStr );
    m_shader->bindAttr( 0, "in_Position" );
    qDebug( "init" );
}

void Example::paintGL() {

    qDebug( "E01::Example::paintGL()" );

    glMatrixMode( GL_PROJECTION );
    glViewport( 0, 0, width(), height() );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_shader->use();

    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height(),
                                       -1.0f, 1.0f );
    m_shader->setUnif( "uf_Projection", false, projection );

    glm::vec4 rgba = glm::vec4( 1.0, 0.0, 0.0, 1.0 );
    m_shader->setUnif( "uf_Color", rgba );

    GLuint vbo, vao;
    glGenBuffers( 1, &vbo );
    glGenBuffers( 1, &vao );

    Vertex a, b, c;
    a.set( 0.0f,   0.0f,   0.0f, 0.0f );
    a.set( 50.0f,   100.0f, 0.0f, 0.0f );
    a.set( 100.0f, 0.0f,   0.0f, 0.0f );
    Vertex vertices[3] = {
            a, b, c
    };

//    GLfloat vertices[6] = {
//            0.0f,   0.0f,
//            50.0f,  100.0f,
//            100.0f, 0.0f,
//    };

    GLuint elements[3] = {
            0, 1, 2
    };

    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( Vertex ) * 3, vertices, GL_STATIC_DRAW );

    glVertexAttribPointer( m_shader->getAttrHandle( "in_Position" ), 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void * ) + 0 );
    glEnableVertexAttribArray( m_shader->getAttrHandle( "in_Position" ) );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vao );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( GLshort ) * 3, elements, GL_STATIC_DRAW );

    glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0 );

    checkError();

    glDeleteBuffers( 1, &vbo );
    glDeleteBuffers( 1, &vao );

    printContextInformation();

}

void Example::cleanup() {
    makeCurrent();
    doneCurrent();
}

void Example::printContextInformation()
{
    QString glType;
    QString glVersion;
    QString glProfile;


    // Get Version Information
    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
    switch (format().profile())
    {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
    }
#undef CASE

    // qPrintable() will print our QString w/o quotes around it.
    qDebug( "%s %s %s",
            glType.toStdString().c_str(),
            glVersion.toStdString().c_str(),
            glProfile.toStdString().c_str() );
}

}