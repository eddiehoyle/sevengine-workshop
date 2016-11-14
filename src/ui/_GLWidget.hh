//
// Created by Eddie Hoyle on 12/11/16.
//

#ifndef SEVENGINE_WORKSHOP_OPENGLWIDGET_HH
#define SEVENGINE_WORKSHOP_OPENGLWIDGET_HH

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

#include <sev/core/Shader.hh>
#include <sev/graphics/render/RenderRect.hh>
#include <sev/graphics/Texture.hh>
//
//
//class GLWidget
//        : public QOpenGLWidget,
//          protected QOpenGLFunctions
//{
//
//public:
//    explicit GLWidget( QWidget* parent = NULL );
//
//    void initializeGL() Q_DECL_OVERRIDE;
//    void paintGL() Q_DECL_OVERRIDE;
//
//public slots:
//    void cleanup();
//
//};



class GLWidget : public QOpenGLWidget,
                 protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget( QWidget* parent = NULL );
    ~GLWidget();

    void printContextInformation();

public slots:
    void cleanup();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;

private:
    Shader* m_shader;
    Texture* m_texture;
    RenderRect* m_render;
};

#endif //SEVENGINE_WORKSHOP_OPENGLWIDGET_HH
