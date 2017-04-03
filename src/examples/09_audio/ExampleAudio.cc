//
// Created by Eddie Hoyle on 28/02/17.
//

#include "ExampleAudio.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <QFormLayout>
#include <QPushButton>
#include <QLabel>

#include <sev/audio/AudioManager.hh>


namespace E09 {


ExampleAudio::ExampleAudio(QWidget *parent)
        : QWidget( parent ) {

    QFormLayout* layout = new QFormLayout();
    setLayout( layout );

    QLabel* bellLabel = new QLabel( "Bicycle Bell" );
    QPushButton* bellButtonPlay = new QPushButton( "Play" );
    QPushButton* bellButtonStop = new QPushButton( "Stop" );
    QHBoxLayout* bellLayout = new QHBoxLayout();
    bellLayout->addWidget( bellButtonPlay );
    bellLayout->addWidget( bellButtonStop );

    connect( bellButtonPlay, SIGNAL( clicked() ), this, SLOT( playBell() ) );
    connect( bellButtonStop, SIGNAL( clicked() ), this, SLOT( stop() ) );
    layout->addRow( bellLabel, bellLayout );

    QLabel* boingLabel = new QLabel( "Boing" );
    QPushButton* boingButtonPlay = new QPushButton( "Play" );
    QPushButton* boingButtonStop = new QPushButton( "Stop" );
    QHBoxLayout* boingLayout = new QHBoxLayout();
    boingLayout->addWidget( boingButtonPlay );
    boingLayout->addWidget( boingButtonStop );

    connect( boingButtonPlay, SIGNAL( clicked() ), this, SLOT( playBoing() ) );
    connect( boingButtonStop, SIGNAL( clicked() ), this, SLOT( stop() ) );
    layout->addRow( boingLabel, boingLayout );

    AudioManager2::instance();
}

ExampleAudio::~ExampleAudio() {
}

void ExampleAudio::playBell() {
    std::cerr << "Playing: Bicycle Bell" << std::endl;
    const std::string path = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/audio/bell.wav";
    AudioBuffer buffer( path );
//    AudioManager::instance()->play( path );
    AudioManager2::instance()->acquire( "bell" );
    AudioManager2::instance()->play( "bell" );
//    AudioManager2::instance()->release( "bell" );
}

void ExampleAudio::playBoing() {
    std::cerr << "Playing: Boing" << std::endl;
    const std::string path = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/audio/boing.wav";
    AudioBuffer buffer( path );
//    AudioManager::instance()->play( path );
    AudioManager2::instance()->acquire( "boing" );
    AudioManager2::instance()->play( "boing" );
//    AudioManager2::instance()->release( "boing" );
}

void ExampleAudio::stop() {
    AudioManager2::instance()->stop( "bell" );
    AudioManager2::instance()->stop( "boing" );
}

void ExampleAudio::mousePressEvent( QMouseEvent* event ) {
//    m_click.x = event->x();
//    m_click.y = height() - event->y();
}


}