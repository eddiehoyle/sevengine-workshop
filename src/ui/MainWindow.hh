#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWidget>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QSurfaceFormat>
#include <QOpenGLWindow>

enum ExampleType {
    kExampleTriangle         = 0,
    kExampleParticles        = 1,
    kExampleRectTexture      = 2,
    kExampleRectTextureAlpha = 3,
    kExampleText             = 4,
    kExampleAtlasFont        = 5,
    kExampleMultiTexture     = 6,
    kExampleLines            = 7
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    void setExperiment( ExampleType type );
    void cleanup();

private:
    QOpenGLWidget* m_gl;
    QVBoxLayout* m_layout;

public slots:
    void change( int );
};

#endif // WINDOW_H