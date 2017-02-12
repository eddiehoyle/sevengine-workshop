//
// Created by Eddie Hoyle on 31/01/17.
//

#ifndef SEVENGINE_WORKSHOP_EXAMPLEMULTITEXTURE_HH
#define SEVENGINE_WORKSHOP_EXAMPLEMULTITEXTURE_HH

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

#include <sev/graphics/Texture.hh>
#include <sev/graphics/render/QuadRender.hh>
#include <sev/graphics/shader/ShaderManager.hh>

namespace E07 {

class ExampleMultiTexture
        : public QOpenGLWidget,
          protected QOpenGLFunctions {
Q_OBJECT

public:
    explicit ExampleMultiTexture( QWidget* parent = NULL );
    ~ExampleMultiTexture();

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL( int width, int height ) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

public slots:
    void cleanup();
    void animate();

private:
    Texture2D* m_bomb;
    Texture2D* m_cat;
};

}


#endif //SEVENGINE_WORKSHOP_EXAMPLEMULTITEXTURE_HH
