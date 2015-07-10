#include <pong/Application.hpp>
#include <SFML/Window/Event.hpp>

Application::Application()
  : mWindow( { 800, 600 }, "Pong Tutorial 1", sf::Style::Close )
  , mPlayer( { 20.f, 100.f } )
  , mMoveUp( false )
  , mMoveDown( false )
{
  auto playerBounds = mPlayer.getLocalBounds();
  sf::Vector2f center{ static_cast<float>( mWindow.getSize().x ) / 2.f,
                       static_cast<float>( mWindow.getSize().y ) / 2.f };
  mPlayer.setFillColor( sf::Color::Green );  
  mPlayer.setOrigin( playerBounds.width / 2.f, playerBounds.height / 2.f );  
  mPlayer.setPosition( center );
}

void Application::run()
{
  while( mWindow.isOpen() ) {
    handle();
    update();
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

void Application::update()
{
  if( mMoveUp ) {
    mPlayer.move( 0.f, -1.f );
    mMoveUp = false;
  }
  if( mMoveDown ) {
    mPlayer.move( 0.f, 1.f );
    mMoveDown = false;
  }
}

void Application::render()
{
  mWindow.clear();
  mWindow.draw( mPlayer );
  mWindow.display();
}