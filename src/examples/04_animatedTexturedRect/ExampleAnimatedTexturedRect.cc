//
// Created by Eddie Hoyle on 13/11/16.
//

#include "ExampleAnimatedTexturedRect.hh"

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

#include <iostream>
#include <ctime> // Needed for the true randomization
#include <cstdlib>
#include <random>




int getRandom( int floor, int ceiling ) {
    srand(time(0));
    int range = (ceiling - floor);
    int rnd = floor + int(((double)range * rand()) / (RAND_MAX + 1.0));
    return rnd;
}

float RandomFloat(float min, float max)
{
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

    float rv = (float)uni(rng);
    return rv;
}

namespace E04 {

static float angle = 0.0f;
static float translateY = 0.0f;
static glm::vec2 position = glm::vec2( 0.0f, 0.0f );
static float scale = 1.0f;

ExampleAnimatedTexturedRect::ExampleAnimatedTexturedRect(QWidget *parent)
        : QOpenGLWidget( parent )
{
    QTimer* aTimer = new QTimer;
    QObject::connect( aTimer, SIGNAL( timeout() ), this, SLOT( animate() ) );
    aTimer->start( 15 );
}

ExampleAnimatedTexturedRect::~ExampleAnimatedTexturedRect()
{
    cleanup();
}

void ExampleAnimatedTexturedRect::animate()
{
    // Rotate
//    angle += 1.0f;

    // Position
    position.y = std::sin( translateY += 0.1f ) * 20;
    position.y += 50.0f;
    position.x = ( float )( width() / 2 ) - 50;

    // Schedule paint
    update();
}

void ExampleAnimatedTexturedRect::resizeGL( int width, int height )
{
    m_positions.clear();

    srand( time( 0 ) ); // This will ensure a really randomized number by help of time.

    int xRan;
    int minHPos, minWPos;
    minHPos = minWPos = - 200;
    int maxHPos = height;
    int maxWPos = width;
    int numItems = 1000;

    int x, y;
    for ( int index = 0; index < numItems; index++ ) {

        x = RandomFloat( (float)minWPos, float(maxWPos));
        y = RandomFloat( (float)minHPos, float(maxHPos));

        m_positions.push_back( std::pair< int, int >( x, y ) );
    }
}

void ExampleAnimatedTexturedRect::initializeGL() {

    connect( context(), &QOpenGLContext::aboutToBeDestroyed, this, &ExampleAnimatedTexturedRect::cleanup );

    initializeOpenGLFunctions();

    glClearColor(1, 0.35, 0.35, 1);

    ShaderManager::instance();

    const char* path = "/Users/eddiehoyle/Code/cpp/game/sevengine-workshop/resources/bomb.png";
    TextureManager2D::instance()->load( "bomb", path );
}

void ExampleAnimatedTexturedRect::paintGL()
{
    ShaderManager::instance()->use( "texture" );
    glm::mat4 projection = glm::ortho( 0.0f, ( float )width(),
                                       0.0f, ( float )height() );
    ShaderManager::instance()->setUnif( "uf_Projection", false, projection );
    ShaderManager::instance()->setUnif( "uf_Texture", 0 );

    // Tell 'uf_Texture' sampler in fragment shader to use the texture bound to GL_TEXTURE0
    TextureManager2D::instance()->bind( "bomb", 0 );
    TextureManager2D::instance()->setResizeMode( GL_NEAREST, GL_NEAREST );
    TextureManager2D::instance()->setWrapMode( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );

    // Create quads
    QuadBuffer buffer = QuadBuffer();

    int size = 100;
    for ( int index = 0; index < m_positions.size(); index++ ) {

        int x = m_positions[index].first;
        int y = m_positions[index].second;

        Transform transform( glm::vec2( 0, 0 ), 0.0f, glm::vec2( 1.0f, 1.0f ) );
        transform.setPivot( glm::vec2( size / 2, size / 2 ) );

        glm::vec2 position2( x, y + position.y );
        if ( index % 2 == 0 ) {
            position.y *= 1.003;
            transform.setAngle( angle * 1.05 );
        } else if ( index % 7 == 0 ) {
            position.y *= 0.997;
        }
        transform.setAngle( angle );
        transform.setPosition( position2 );
        transform.setScale( scale, scale );

        Quad q( size, size );
        q.setUV( 0.0, 1.0, 0.0, 1.0 );
        q.setMatrix( transform.getMatrix() );
        buffer.add( q );
    }

    QuadRender render = QuadRender( buffer );
    render.bind();

    ShaderManager::instance()->enable();

    render.draw();
    render.release();

    buffer.clear();
    ShaderManager::instance()->disable();
    ShaderManager::instance()->release();
}

void ExampleAnimatedTexturedRect::cleanup()
{
    TextureManager2D::instance()->unload( "bomb" );
}

}