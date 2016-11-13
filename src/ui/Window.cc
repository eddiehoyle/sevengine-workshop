//
// Created by Eddie Hoyle on 12/11/16.
//

#include <QMainWindow>
#include <QComboBox>
#include <QOpenGLWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "Window.hh"
#include "../examples/Examples.hh"



Window::Window()
{
    setWindowTitle( "Sevengine - Workshop" );
    QWidget* widget = new QWidget();
    setCentralWidget( widget );

    QLabel* label = new QLabel( "Example:");
    QComboBox* combo = new QComboBox();
    combo->setFixedWidth( 140 );

    QStringList items;
    items << "Triangle";
    items << "Rect";
    items << "Textured Rect";
    combo->addItems( items );
    connect( combo, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( change( int ) ) );

    QHBoxLayout* comboLayout = new QHBoxLayout();
    comboLayout->addStretch( 0 );
    comboLayout->addWidget( label );
    comboLayout->addWidget( combo, Qt::AlignRight );

    // Temp
    m_layout = new QVBoxLayout( widget );
    m_layout->addLayout( comboLayout );
    setExperiment( ( ExampleType )combo->currentIndex() );
}

void Window::change( int index )
{
    cleanup();
    setExperiment( ( ExampleType )index );
    m_gl->update();
}

void Window::cleanup()
{
    if ( m_gl )
    {
        delete m_gl;
    }
}

void Window::setExperiment( ExampleType type )
{
    switch( type )
    {
        case kExampleTriangle:
            qDebug( "Changing: Triangle" );
            m_gl = new E01::Example();
            break;
        case kExampleRect:
            qDebug( "Changing: Rect" );
            m_gl = new E02::Example();
            break;
        default:
            m_gl = new QOpenGLWidget();
    }
    m_gl->setFormat( QSurfaceFormat::defaultFormat() );
    m_layout->addWidget( m_gl );
}
