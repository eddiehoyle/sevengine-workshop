#include <QApplication>

#include "src/ui/MainWindow.hh"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    QSurfaceFormat format;
//    format.setRenderableType(QSurfaceFormat::OpenGL);
//    format.setProfile(QSurfaceFormat::CoreProfile);
//    format.setVersion(2, 1);
//    QSurfaceFormat::setDefaultFormat( format );

    QSurfaceFormat format;
    format.setRenderableType( QSurfaceFormat::OpenGL );
    format.setProfile( QSurfaceFormat::CoreProfile );
    format.setVersion( 2, 1 );
    QSurfaceFormat::setDefaultFormat( format );


    MainWindow mw;
    mw.show();
    mw.resize( QSize( 400, 180 ) );



    return app.exec();
}