//
// Created by Eddie Hoyle on 28/02/17.
//

#ifndef SEVENGINE_WORKSHOP_EXAMPLEAUDIO_HH
#define SEVENGINE_WORKSHOP_EXAMPLEAUDIO_HH



#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <QMouseEvent>

#include <sev/graphics/Texture.hh>
#include <sev/graphics/shader/ShaderManager.hh>

namespace E09 {

class ExampleAudio
        : public QWidget {
Q_OBJECT

public:
    explicit ExampleAudio( QWidget* parent = NULL );
    ~ExampleAudio();

public slots:
    void mousePressEvent( QMouseEvent* event ) Q_DECL_OVERRIDE;
    void playSimple();

};

}

#endif //SEVENGINE_WORKSHOP_EXAMPLEAUDIO_HH
