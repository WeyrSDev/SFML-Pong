#include <game/Application.hpp>
#include <states/TitleState.hpp>
#include <states/GameState.hpp>
#include <states/MenuState.hpp>
#include <states/PauseState.hpp>
#include <states/GameoverState.hpp>
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

  mFonts.load( Fonts::SDS_8BIT, "../media/fonts/SDS_8BIT.ttf" );
  mFonts.load( Fonts::C64_Pixel, "../media/fonts/C64-Pixel.ttf" );
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