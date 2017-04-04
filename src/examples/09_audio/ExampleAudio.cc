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

    QLabel* birdLabel = new QLabel( "Bird" );
    QPushButton* birdButtonPlay = new QPushButton( "Play" );
    QPushButton* birdButtonStop = new QPushButton( "Stop" );
    QHBoxLayout* birdLayout = new QHBoxLayout();
    birdLayout->addWidget( birdButtonPlay );
    birdLayout->addWidget( birdButtonStop );

    connect( birdButtonPlay, SIGNAL( clicked() ), this, SLOT( playBird() ) );
    connect( birdButtonStop, SIGNAL( clicked() ), this, SLOT( stop() ) );
    layout->addRow( birdLabel, birdLayout );


    QLabel* chickenLabel = new QLabel( "Chicken" );
    QPushButton* chickenButtonPlay = new QPushButton( "Play" );
    QPushButton* chickenButtonStop = new QPushButton( "Stop" );
    QHBoxLayout* chickenLayout = new QHBoxLayout();
    chickenLayout->addWidget( chickenButtonPlay );
    chickenLayout->addWidget( chickenButtonStop );

    connect( chickenButtonPlay, SIGNAL( clicked() ), this, SLOT( playChicken() ) );
    connect( chickenButtonStop, SIGNAL( clicked() ), this, SLOT( stop() ) );
    layout->addRow( chickenLabel, chickenLayout );

    AudioManager::instance();
}

ExampleAudio::~ExampleAudio() {
}

void ExampleAudio::playBell() {
    std::cerr << "Playing: Bicycle Bell" << std::endl;
    AudioManager::instance()->acquire( "bell" );
    AudioManager::instance()->play( "bell" );
//    AudioManager::instance()->release( "bell" );
}

void ExampleAudio::playBoing() {
    std::cerr << "Playing: Boing" << std::endl;
    AudioManager::instance()->acquire( "boing" );
    AudioManager::instance()->play( "boing" );
//    AudioManager::instance()->release( "boing" );
}

void ExampleAudio::playBird() {
    std::cerr << "Playing: Bird" << std::endl;
    AudioManager::instance()->acquire( "bird" );
    AudioManager::instance()->play( "bird" );
//    AudioManager::instance()->release( "bird" );
}

void ExampleAudio::playChicken() {
    std::cerr << "Playing: Chicken" << std::endl;
    AudioManager::instance()->acquire( "chicken" );
    AudioManager::instance()->play( "chicken" );
//    AudioManager::instance()->release( "chicken" );
}

void ExampleAudio::stop() {
    AudioManager::instance()->stop( "bell" );
    AudioManager::instance()->stop( "boing" );
    AudioManager::instance()->stop( "bird" );
    AudioManager::instance()->stop( "chicken" );

    AudioManager::instance()->release( "bell" );
    AudioManager::instance()->release( "boing" );
    AudioManager::instance()->release( "bird" );
    AudioManager::instance()->release( "chicken" );

}

void ExampleAudio::mousePressEvent( QMouseEvent* event ) {
//    m_click.x = event->x();
//    m_click.y = height() - event->y();
}


}