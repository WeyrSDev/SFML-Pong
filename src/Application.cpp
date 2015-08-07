#include <pong/Application.hpp>
#include <SFML/Window/Event.hpp>

Application::Application()
  : mWindow( { 800, 600 }, "Pong for #1GAM", sf::Style::Close )
  , mFpsDisplay()
  , mTimeStep( sf::seconds( 1.f / 60.f ) )
  , mContext( mWindow )
  , mWorld( mContext )
{
  mWindow.setKeyRepeatEnabled( false );
  mWindow.setFramerateLimit( 200u );
  mFpsDisplay.setPosition( 10.f, 10.f );
}

void Application::run()
{
  sf::Clock appClock;
  sf::Time timeSinceLastFrame{ sf::Time::Zero };

  while( mWindow.isOpen() ) {
    sf::Time dt{ appClock.restart() };
    timeSinceLastFrame += dt;
    handleEvents();
    while( timeSinceLastFrame > mTimeStep ) {
      timeSinceLastFrame -= mTimeStep;
      update( mTimeStep );
    }
    mFpsDisplay.update( dt );
    draw();
  }
}

// end public interface

void Application::handleEvents()
{
  sf::Event event;
  while( mWindow.pollEvent( event ) ) {
    if( event.type == sf::Event::Closed ){
      mWindow.close();
    }    
  }

  mWorld.handleEvents( event );
}

void Application::update( const sf::Time dt )
{
  mWorld.update( dt );
}

void Application::draw()
{
  mWindow.clear();
  mWorld.draw();
  mWindow.draw( mFpsDisplay );
  mWindow.display();
}