#include <game/Application.hpp>
#include <states/TitleState.hpp>
#include <states/GameState.hpp>
#include <states/MenuState.hpp>
#include <states/PauseState.hpp>
#include <states/GameoverState.hpp>
#include <states/CreditState.hpp>
#include <SFML/Window/Event.hpp>

///////////////////////////////////////////////////////////////////////////////

Application::Application()
  : mWindow( { 1000, 600 }, "Pong for #1GAM", sf::Style::Close )
  , mFpsDisplay( nullptr )
  , mTextures()
  , mFonts()
  , mBBoard()
  , mContext( mWindow, mTextures, mFonts, mBBoard )
  , mStack( mContext )
  , mTimeStep( sf::seconds( 1.f / 60.f ) )
{
  mWindow.setKeyRepeatEnabled( false );
  mWindow.setFramerateLimit( 200u );
  mWindow.setMouseCursorVisible( false );

  mBBoard.keyEventType = sf::Event::EventType::KeyReleased;

  mFonts.load( Fonts::SDS_8BIT, "../media/fonts/SDS_8BIT.ttf" );
  mFonts.load( Fonts::C64_Pixel, "../media/fonts/C64-Pixel.ttf" );
  mFonts.load( Fonts::MONOSPACE, "../media/fonts/DejaVuSansMono.ttf" );
  mFonts.load( Fonts::DP_COMIC, "../media/fonts/dpcomic.ttf" );
  mTextures.load( Textures::TITLE_BG, "../media/gfx/title-bg.png" );

  mFpsDisplay = std::make_unique<FpsDisplay>( mFonts.get( Fonts::MONOSPACE ) );
  mFpsDisplay->setPosition( 10.f, 10.f );

  mStack.registerState<TitleState>( States::TITLE );
  mStack.registerState<MenuState>( States::MENU );
  mStack.registerState<GameState>( States::GAME );
  mStack.registerState<PauseState>( States::PAUSE );
  mStack.registerState<GameoverState>( States::GAMEOVER );
  mStack.registerState<CreditState>( States::CREDITS );
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
}

// end public interface
///////////////////////////////////////////////////////////////////////////////

void Application::handleInput()
{
  sf::Event event;
  while( mWindow.pollEvent( event ) ) {
#ifdef _DEBUG
    std::cout << "Application::handleInput::pollEvent - Tick" << std::endl;
#endif
    mStack.handleInput( event );

    if( event.type == sf::Event::Closed ){
      mWindow.close();
    }    
  }
  //mStack.handleInput( event );
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