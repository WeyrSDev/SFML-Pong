#include <pong/Application.hpp>
#include <SFML/Window/Event.hpp>

Application::Application()
  : mWindow( { 800, 600 }, "Pong Tutorial 1", sf::Style::Close )
  , mPlayer( { 20.f, 100.f } )
  , mMoveUp( false )
  , mMoveDown( false )
  , mFpsDisplay()
  , mTimeStep( sf::seconds( 1.f / 60.f ) )
  , mPlayerSpeed( 200.f )
{
  mWindow.setKeyRepeatEnabled( false );
  mWindow.setFramerateLimit( 200u );

  sf::Vector2f center{ static_cast<float>( mWindow.getSize().x ) / 2.f,
                       static_cast<float>( mWindow.getSize().y ) / 2.f };
  mPlayer.setFillColor( sf::Color::Green );
  mPlayer.setOrigin( mPlayer.getSize() / 2.f );
  mPlayer.setPosition( center );

  mFpsDisplay.setPosition( 10.f, 10.f );
}

void Application::run()
{
  sf::Clock appClock;
  sf::Time timeSinceLastFrame{ sf::Time::Zero };

  while( mWindow.isOpen() ) {
    sf::Time dt{ appClock.restart() };
    timeSinceLastFrame += dt;
    handle();
    while( timeSinceLastFrame > mTimeStep ) {
      timeSinceLastFrame -= mTimeStep;
      update( mTimeStep );
    }
    mFpsDisplay.update( dt );
    render();
  }
}

// end public interface

void Application::handle()
{
  sf::Event event;
  while( mWindow.pollEvent( event ) ) {
    if( event.type == sf::Event::Closed ){
      mWindow.close();
    }    
  }

  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
    mMoveUp = true;
  }
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) {
    mMoveDown = true;
  }
}

void Application::update( const sf::Time dt )
{
  auto playerMove = mPlayerSpeed * dt.asSeconds();
  if( mMoveUp ) {
    auto topPlayerYBound = mPlayer.getGlobalBounds().top;
    if( topPlayerYBound - playerMove <= 0.f ) {
      mPlayer.move( 0.f, -topPlayerYBound );
    } else {
      mPlayer.move( 0.f, -playerMove );
    }    
    mMoveUp = false;
  }
  if( mMoveDown ) {
    auto botPlayerYBound = mPlayer.getGlobalBounds().top + mPlayer.getGlobalBounds().height;
    auto botYDistance = static_cast<float>( mWindow.getSize().y ) - botPlayerYBound;
    if( botPlayerYBound >= static_cast<float>( mWindow.getSize().y ) ) {
      mPlayer.move( 0.f, botYDistance );
    } else {
      mPlayer.move( 0.f, playerMove );
    }
    mMoveDown = false;
  }
}

void Application::render()
{
  mWindow.clear();
  mWindow.draw( mPlayer );
  mWindow.draw( mFpsDisplay );
  mWindow.display();
}