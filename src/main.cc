#include <QApplication>

#include "ui/Window.hh"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);



    Window window;
//    window.setFormat( format );
    window.show();
    window.resize( QSize( 400, 180 ) );

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(2, 1);
    QSurfaceFormat::setDefaultFormat( format );



    return app.exec();
}