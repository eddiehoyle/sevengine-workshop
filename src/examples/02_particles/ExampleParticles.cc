//
// Created by Eddie Hoyle on 13/11/16.
//

#include "ExampleParticles.hh"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

#include <iostream>
#include <sev/Utilities.hh>
#include <sev/core/Transform.hh>

#include <QTimer>
#include <sev/graphics/render/ParticleRender.hh>
#include <sev/graphics/shader/ShaderManager.hh>
#include <sev/graphics/texture/TextureManager2D.hh>
#include <sev/graphics/font/FontParser.hh>
#include <sev/graphics/font/Char.hh>

#include <iostream>
#include <ctime> // Needed for the true randomization
#include <cstdlib>
#include <random>

namespace E02 {


float RandomFloat(float min, float max)
{
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

    float rv = (float)uni(rng);
    return rv;
}

ExampleParticles::ExampleParticles(QWidget *parent)
        : QOpenGLWidget( parent )
{
    QTimer* aTimer = new QTimer;
    connect( aTimer, SIGNAL( timeout() ), this, SLOT( animate() ) );
    aTimer->start(30);
}

ExampleParticles::~ExampleParticles()
{
    cleanup();
}

void ExampleParticles::animate()
{
    /// TODO
}

void ExampleParticles::resizeGL( int width, int height )
{
    // TODO
}

void ExampleParticles::initializeGL() {

    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &ExampleParticles::cleanup );

    initializeOpenGLFunctions();

    glClearColor( 1, 0.35, 0.35, 1 );

    ShaderManager::instance();

    // Load bomb
    const char *path = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/grass.png";
    TextureManager2D::instance()->load( "grass", path, true );
}

void ExampleParticles::paintGL() {
    ShaderManager::instance()->use( "particle" );
    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height(),
                                       -1.0f, 1.0f );
    ShaderManager::instance()->setUnif( "uf_Projection", false, projection );
    ShaderManager::instance()->setUnif( "uf_Texture", 0 );

    // Tell 'uf_Texture' sampler in fragment shader to use the texture bound to GL_TEXTURE0
    TextureManager2D::instance()->bind( "grass", 0 );
    TextureManager2D::instance()->setResizeMode( GL_LINEAR, GL_LINEAR );
    TextureManager2D::instance()->setWrapMode( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );


    // ------------------------------------------------------------

    ParticleBuffer buffer;

    int minHPos = 0;
    int minWPos = 0;
    int maxHPos = height();
    int maxWPos = width();

    int x, y;
    int num = 100;

    for ( int i = 0; i < num; i++ ) {

        x = RandomFloat( ( float )minWPos, float( maxWPos ) );
        y = RandomFloat( ( float )minHPos, float( maxHPos ) );

        Particle p;
        p.setPosition( glm::vec2( x, y) );
        p.setSize( 64 );
        p.setColor( 255, 255, 255, 255 );

        buffer.add( p );
    }

    ParticleRender render( buffer );
    render.bind();

    ShaderManager::instance()->enable();

    render.draw();
    render.release();

    buffer.clear();

    ShaderManager::instance()->disable();
    ShaderManager::instance()->release();
}

void ExampleParticles::cleanup()
{
    TextureManager2D::instance()->unload( "grass" );
}

}