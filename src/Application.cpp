#include <pong/Application.hpp>
#include <pong/TitleState.hpp>
#include <pong/GameState.hpp>
#include <pong/MenuState.hpp>
#include <pong/PauseState.hpp>
#include <pong/GameoverState.hpp>
#include <SFML/Window/Event.hpp>

Application::Application()
  : mWindow( { 800, 600 }, "Pong for #1GAM", sf::Style::Close )
  , mFpsDisplay()
  , mTextures()
  , mFonts()
  , mBBoard()
  , mContext( mWindow, mTextures, mFonts, mBBoard )
  , mStack( mContext )
  , mTimeStep( sf::seconds( 1.f / 60.f ) )
{
  mWindow.setKeyRepeatEnabled( false );
  mWindow.setFramerateLimit( 200u );
  mFpsDisplay.setPosition( 10.f, 10.f );

  mFonts.load( Fonts::GREENSCREEN, "../media/fonts/Greenscreen.ttf" );
  mTextures.load( Textures::TITLE_BG, "../media/gfx/title-bg.png" );

  mStack.registerState<TitleState>( States::TITLE );
  mStack.registerState<MenuState>( States::MENU );
  mStack.registerState<GameState>( States::GAME );
  mStack.registerState<PauseState>( States::PAUSE );
  mStack.registerState<GameoverState>( States::GAMEOVER );
  mStack.pushState( States::TITLE );
}

void Application::run()
{
  sf::Clock appClock;
  sf::Time timeSinceLastUpdate{ sf::Time::Zero };

  while( mWindow.isOpen() ) {
    sf::Time dt{ appClock.restart() };
    timeSinceLastUpdate += dt;
    handleInput();
    while( timeSinceLastUpdate > mTimeStep ) {
      timeSinceLastUpdate -= mTimeStep;
      update( mTimeStep );
    }
    mFpsDisplay.update( dt );
    render();

    if( mStack.isEmpty() ) {
      mWindow.close();
    }
  }
}

// end public interface

void Application::handleInput()
{
  sf::Event event;
  while( mWindow.pollEvent( event ) ) {
    if( event.type == sf::Event::Closed ){
      mWindow.close();
    }    
  }
  mStack.handleInput( event );
}

void Application::update( const sf::Time dt )
{
  mStack.update( dt );
}

void Application::render()
{
  mWindow.clear();
  mStack.render();
  mWindow.draw( mFpsDisplay );
  mWindow.display();
}