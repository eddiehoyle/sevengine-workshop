//
// Created by Eddie Hoyle on 28/02/17.
//

#include "ExampleAudio.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>

#include <sev/Utilities.hh>
#include <sev/core/Transform.hh>
#include <sev/graphics/shader/ShaderManager.hh>
#include <sev/graphics/texture/TextureManager2D.hh>
#include <sev/graphics/render/QuadRender.hh>
#include <QTimer>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>


namespace E09 {


ExampleAudio::ExampleAudio(QWidget *parent)
        : QWidget( parent ) {

    QFormLayout* layout = new QFormLayout();
    setLayout( layout );

    QPushButton* simpleButton = new QPushButton( "Play" );
    QLabel* simpleLabel = new QLabel( "Simple" );
    connect( simpleButton, SIGNAL( clicked() ), this, SLOT( playSimple() ) );
    layout->addRow( simpleLabel, simpleButton );
}

ExampleAudio::~ExampleAudio() {
}

void ExampleAudio::playSimple() {
    std::cerr << "Playing simple" << std::endl;
}

void ExampleAudio::mousePressEvent( QMouseEvent* event ) {
//    m_click.x = event->x();
//    m_click.y = height() - event->y();
}


}