#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWidget>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QSurfaceFormat>
#include <QOpenGLWindow>

enum ExampleType {
    kExampleTriangle     = 0,
    kExampleRect         = 1,
    kExampleRectTextured = 2,
};

//class Window : public QMainWindow
//{
//    Q_OBJECT
//
//public:
//    Window();
//
//private:
//    void setExperiment( ExampleType type );
//    void cleanup();
//
//private:
//    QOpenGLWidget* m_gl;
//    QVBoxLayout* m_layout;
//
//    QSurfaceFormat m_format;
//
//
//public slots:
//
//    void change( int );
//
//};


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