#include <game/Application.hpp>
#include <states/TitleState.hpp>
#include <states/GameState.hpp>
#include <states/MenuState.hpp>
#include <states/PauseState.hpp>
#include <states/GameoverState.hpp>
#include <states/CreditState.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////

Application::Application()
  : mWindow( { 1000, 600 }, "Pong for #1GAM", sf::Style::Close )
  , mLog( "pong.log", core::LogType::DEBUG )
  , mFpsDisplay( nullptr )
  , mTextures( &mLog )
  , mFonts( &mLog )
  , mBBoard()
  , mContext( mWindow, mTextures, mFonts, mBBoard, mLog )
  , mStack( mContext )
  , mTimeStep( sf::seconds( 1.f / 60.f ) )  
{
  mWindow.setKeyRepeatEnabled( false );
  mWindow.setFramerateLimit( 200u );
  mWindow.setMouseCursorVisible( false );

  mTextures.load( Textures::TITLE_BG, "../data/gfx/title-bg.png" );
  mFonts.load( Fonts::SDS_8BIT, "../data/fonts/SDS_8BIT.ttf" );
  mFonts.load( Fonts::C64_Pixel, "../data/fonts/C64-Pixel.ttf" );
  mFonts.load( Fonts::MONOSPACE, "../data/fonts/DejaVuSansMono.ttf" );
  mFonts.load( Fonts::DP_COMIC, "../data/fonts/dpcomic.ttf" );

  mBBoard.keyEventType = sf::Event::EventType::KeyReleased;
  mLog.write( "keyEventType set to " + core::eventToString( mBBoard.keyEventType ),
              core::LogType::INFO );

  mFpsDisplay = std::make_unique<core::FpsDisplay>( mFonts.get( Fonts::MONOSPACE ) );
  mFpsDisplay->setPosition( 10.f, 10.f );

  mStack.registerState<TitleState>( States::TITLE );
  mStack.registerState<MenuState>( States::MENU );
  mStack.registerState<GameState>( States::GAME );
  mStack.registerState<PauseState>( States::PAUSE );
  mStack.registerState<GameoverState>( States::GAMEOVER );
  mStack.registerState<CreditState>( States::CREDITS );

  mLog.write( "Application initialized successfully", core::LogType::INFO );
  mLog.write( "Starting StateStack", core::LogType::INFO );
  mStack.pushState( States::TITLE );
}

///////////////////////////////////////////////////////////////////////////////

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
      update();

      // if after update state stack is empty, close window to shutdown
      if( mStack.isEmpty() ) {
        mWindow.close();
      }
    }
    mFpsDisplay->update( dt );
    render();    
  }

  mLog.write( "Shutting down application", core::LogType::INFO );
}

// end public interface
///////////////////////////////////////////////////////////////////////////////

void Application::handleInput()
{
  sf::Event event;
  while( mWindow.pollEvent( event ) ) {
    if( filterEvent( event.type ) ) {
      mLog.write( "Application::handleInput() event " + core::eventToString( event.type )
                  + " registered", core::LogType::DEBUG );
    }
    mStack.handleInput( event );

    if( event.type == sf::Event::Closed ){
      mWindow.close();
    }    
  }
}

///////////////////////////////////////////////////////////////////////////////

void Application::update()
{
  mStack.update( mTimeStep );
}

///////////////////////////////////////////////////////////////////////////////

void Application::render()
{
  mWindow.clear();
  mStack.render();
  mWindow.draw( *mFpsDisplay );
  mWindow.display();
}

///////////////////////////////////////////////////////////////////////////////

// checking for events we are interested in
// returns true for interesting events
// otherwise returns false
bool Application::filterEvent( sf::Event::EventType eventType )
{
  switch( eventType ) {
    case sf::Event::EventType::MouseMoved:
    case sf::Event::EventType::MouseButtonPressed:
    case sf::Event::EventType::MouseButtonReleased:
    case sf::Event::EventType::MouseEntered:
    case sf::Event::EventType::MouseLeft:
    case sf::Event::EventType::MouseWheelMoved:
    case sf::Event::EventType::MouseWheelScrolled:
    case sf::Event::EventType::TextEntered:
      return false;
    default:
      return true;
  }
}

///////////////////////////////////////////////////////////////////////////////