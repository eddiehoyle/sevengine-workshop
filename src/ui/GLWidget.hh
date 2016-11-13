//
// Created by Eddie Hoyle on 12/11/16.
//

#ifndef SEVENGINE_WORKSHOP_OPENGLWIDGET_HH
#define SEVENGINE_WORKSHOP_OPENGLWIDGET_HH

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>


class GLWidget
        : public QOpenGLWidget,
          protected QOpenGLFunctions
{

public:
    explicit GLWidget( QWidget* parent = NULL );

    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

public slots:
    void cleanup();

};


#endif //SEVENGINE_WORKSHOP_OPENGLWIDGET_HH
