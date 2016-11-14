//
// Created by Eddie Hoyle on 14/11/16.
//

#ifndef SEVENGINE_WORKSHOP_UTIL_HH
#define SEVENGINE_WORKSHOP_UTIL_HH

#include <QString>
#include <QOpenGLContext>
#include <QSurfaceFormat>
#include <qglobal.h>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

void printContextInformation( QOpenGLContext* context,
                              const QSurfaceFormat& format )
{
    QString glType;
    QString glVersion;
    QString glProfile;

    // Get Version Information
    glType = ( context->isOpenGLES() ) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast< const char* >( glGetString( GL_VERSION ) );

    // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
    switch ( format.profile() )
    {
        CASE( NoProfile);
        CASE( CoreProfile);
        CASE( CompatibilityProfile);
    }
#undef CASE

    // qPrintable() will print our QString w/o quotes around it.
    qDebug( "%s %s %s",
            glType.toStdString().c_str(),
            glVersion.toStdString().c_str(),
            glProfile.toStdString().c_str() );
}

#endif //SEVENGINE_WORKSHOP_UTIL_HH
