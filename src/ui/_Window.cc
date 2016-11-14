//
// Created by Eddie Hoyle on 14/11/16.
//

#include "_Window.hh"
#include "_GLWidget.hh"

Window::Window(MainWindow *mw)
        : mainWindow(mw)
{

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(2, 1);

    GLWidget* glWidget = new GLWidget;
    glWidget->setFormat( format );

    QHBoxLayout* container = new QHBoxLayout;
    container->addWidget( glWidget );

    setLayout( container );

    setWindowTitle(tr("Hello GL"));
}