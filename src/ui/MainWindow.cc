//
// Created by Eddie Hoyle on 12/11/16.
//

#include <QMainWindow>
#include <QComboBox>
#include <QOpenGLWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "MainWindow.hh"
#include "../examples/Examples.hh"



MainWindow::MainWindow()
        : m_gl(),
          m_audio() {

    setWindowTitle( "Sevengine - Workshop" );

    QWidget* widget = new QWidget();
    m_layout = new QVBoxLayout( widget );
    setCentralWidget( widget );

    QLabel* label = new QLabel( "ExampleTriangle:");
    QComboBox* combo = new QComboBox();
    combo->setFixedWidth( 140 );

    QStringList items;
    items << "Triangle";
    items << "Particles";
    items << "4 cats";
    items << "Lots of bombs";
    items << "Font";
    items << "Atlas Font Texture";
    items << "Multi Texture";
    items << "Lines";
    items << "Audio";

    combo->addItems( items );

    connect( combo, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( change( int ) ) );

    QHBoxLayout* optionLayout = new QHBoxLayout();
    optionLayout->addStretch( 0 );
    optionLayout->addWidget( label );
    optionLayout->addWidget( combo, Qt::AlignRight );

    m_layout->addLayout( optionLayout );

    setExperiment( kExampleAudio );
    combo->setCurrentIndex( 8 );
}

void MainWindow::change( int index )
{
    cleanup();
    setExperiment( ( ExampleType )index );
}

void MainWindow::cleanup()
{
    if ( m_gl ) { delete m_gl; }
    if ( m_audio ) { delete m_audio; }
    m_gl = NULL;
    m_audio = NULL;
}

void MainWindow::setExperiment( ExampleType type )
{
    switch( type )
    {
        case kExampleTriangle:
            m_gl = new E01::ExampleTriangle();
            break;
        case kExampleParticles:
            m_gl = new E02::ExampleParticles();
            break;
        case kExampleRectTexture:
            m_gl = new E03::ExampleTexturedRect();
            break;
        case kExampleRectTextureAlpha:
            m_gl = new E04::ExampleAnimatedTexturedRect();
            break;
        case kExampleText:
            m_gl = new E05::ExampleFreeTypeFont();
            break;
        case kExampleAtlasFont:
            m_gl = new E06::ExampleTextureAtlasFont();
            break;
        case kExampleMultiTexture:
            m_gl = new E07::ExampleMultiTexture();
            break;
        case kExampleLines:
            m_gl = new E08::ExampleLines();
            break;
        case kExampleAudio:
            m_audio = new E09::ExampleAudio();
            break;
        default:
            m_gl = new E01::ExampleTriangle();
            break;
    }

    if ( m_gl ) {
        m_layout->addWidget( m_gl );
        m_gl->setFormat( QSurfaceFormat::defaultFormat() );
    } else {
        m_layout->addWidget( m_audio );
    }
}


// ----------------------------------------------------------------------------------------------- //

//MainWindow2::MainWindow2()
//{
////    setCentralWidget( new Window( this ) );
//
//    setWindowTitle(tr("Hello GL"));
//
//    QSurfaceFormat format;
//    format.setRenderableType( QSurfaceFormat::OpenGL );
//    format.setProfile( QSurfaceFormat::CoreProfile );
//    format.setVersion( 2, 1 );
//
//    GLWidget* glWidget = new GLWidget;
//    glWidget->setFormat( format );
//
//    QHBoxLayout* container = new QHBoxLayout;
//    container->addWidget( glWidget );
//
//    QWidget* widget = new QWidget();
//    widget->setLayout( container );
//
//    setCentralWidget( widget );
//}