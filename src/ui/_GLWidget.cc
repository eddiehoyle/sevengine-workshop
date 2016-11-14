//
// Created by Eddie Hoyle on 12/11/16.
//

#include "_GLWidget.hh"
#include <sev/core/Shader.hh>
#include <sev/graphics/Vertex.hh>
#include <sev/Utilities.hh>
#include <sev/graphics/render/RenderRect.hh>

//GLWidget::GLWidget( QWidget* parent )
//        : QOpenGLWidget( parent )
//{
//    /// TODO
//}
//
//void GLWidget::initializeGL()
//{
//    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup );
//
//    initializeOpenGLFunctions();
//    glClearColor(0.35, 0.35, 0.35, 1);
//}
//
//void GLWidget::paintGL()
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//
//void GLWidget::cleanup()
//{
//    makeCurrent();
//    doneCurrent();
//}


GLWidget::GLWidget( QWidget *parent )
        : QOpenGLWidget( parent )
{

}

GLWidget::~GLWidget()
{
    cleanup();
}

void GLWidget::cleanup()
{
    // TODO
}


void GLWidget::initializeGL()
{
    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup );

    initializeOpenGLFunctions();
    printContextInformation();

    glClearColor(1, 0.35, 0.35, 1);

    const char* vertexPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/simple.vert";
    const char* fragmentPath = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/simple.frag";

    const char* vertexShaderStr = readShaderFile( vertexPath );
    const char* fragmentShaderStr = readShaderFile( fragmentPath );

    m_shader = new Shader( vertexShaderStr, fragmentShaderStr );
    m_shader->bindAttr( 0, "in_Position" );

    m_texture = new Texture( GL_TEXTURE_2D, "", 256, 256 );

    m_render = new RenderRect( m_shader, m_texture );
}


void GLWidget::paintGL()
{
//    qDebug( "E01::Example::paintGL()" );
//
//    glViewport( 0, 0, width(), height() );
//
//    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//
//    m_shader->use();
//
//    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
//                                       0.0f, ( float )height(),
//                                       -1.0f, 1.0f );
//    m_shader->setUnif( "uf_Projection", false, projection );
//
//    glm::vec4 rgba = glm::vec4( 1.0, 0.0, 0.0, 1.0 );
//    m_shader->setUnif( "uf_Color", rgba );
//
//    Quad a( 100, 100 );
//
//    m_render->buffer( a );
//    m_render->draw();

    // -------------------------------------------------------------------- //

    m_shader->use();

    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height(),
                                       -1.0f, 1.0f );
    m_shader->setUnif( "uf_Projection", false, projection );

    glm::vec4 rgba = glm::vec4( 0.4, 0.2, 0.2, 1.0 );
    m_shader->setUnif( "uf_Color", rgba );

    GLuint vbo, ebo;
    glGenBuffers( 1, &vbo );
    glGenBuffers( 1, &ebo );

    Vertex a, b, c;
    float size = 100;
    float cx = width() / 2;
    float cy = height() / 2;
    a.set( cx - size, cy - size, 0.0, 0.0f );
    b.set( cx, cy + size, 0.0, 0.0f );
    c.set( cx + size, cy - size, 0.0, 0.0f );
    Vertex vertices[3] = {
            a, b, c
    };

    GLuint elements[3] = {
            0, 1, 2,
    };

    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, 3 * sizeof( Vertex ), vertices, GL_STATIC_DRAW );

    GLuint stride = sizeof( Vertex );
    glVertexAttribPointer( m_shader->getAttrHandle( "in_Position" ), 2, GL_FLOAT, GL_FALSE, stride, ( void * ) + 0 );
    glEnableVertexAttribArray( m_shader->getAttrHandle( "in_Position" ) );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof( GLuint ), elements, GL_STATIC_DRAW );

    checkError();

    glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0 );

    glDeleteBuffers( 1, &vbo );
    glDeleteBuffers( 1, &ebo );
    Texture::unbind( m_texture );
}

void GLWidget::resizeGL(int w, int h)
{
    // TODO
}

void GLWidget::printContextInformation()
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