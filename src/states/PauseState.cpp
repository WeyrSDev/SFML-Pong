#include "PauseState.hpp"
#include <engine/Context.hpp>
#include <game/Blackboard.hpp>
#include <game/ResourceIdentifiers.hpp>
#include <engine/ResourceCache.hpp>
#include <engine/Utility.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

///////////////////////////////////////////////////////////////////////////////

PauseState::PauseState( core::StateStack& stack, States id )
  : State( stack, id )
  , mBackgroundShape()
  , mPauseText()
  , mMenu( getContext()->fonts->get( Fonts::C64_Pixel ), 30u, 15u,
           getContext()->blackboard->keyEventType )
{
  auto winSize = getContext()->window->getView().getSize();

  // make background whole screen and half transparent black
  mBackgroundShape.setSize( winSize );  
  mBackgroundShape.setFillColor( { 0, 0, 0, 150 } ); 

  const auto& font = getContext()->fonts->get( Fonts::C64_Pixel );

  mPauseText.setFont( font );
  mPauseText.setCharacterSize( 40u );
  mPauseText.setString( "GAME PAUSED" );
  mPauseText.setColor( sf::Color::Green );
  core::centerOrigin( mPauseText );
  mPauseText.setPosition( winSize.x / 2.f, 75.f );

  mMenu.setHighlightColor( sf::Color::Green );
  mMenu.add( "RESUME GAME" );
  mMenu.add( "EXIT TO MENU" );
  mMenu.add( "EXIT GAME" );
  core::centerOrigin( mMenu );
  mMenu.setPosition( winSize / 2.f );
}

///////////////////////////////////////////////////////////////////////////////

bool PauseState::handleInput( const sf::Event& event )
{
  if( event.type == sf::Event::KeyPressed ) {
    if( event.key.code == sf::Keyboard::Escape ) {
      requestStackPop();
    }
  }

  int menuResult = mMenu.handleInput( event );
  switch( menuResult ) {
    case core::to_integral(MenuOption::RESUME):
      requestStackPop();
      break;

    case core::to_integral(MenuOption::EXIT_MENU):
      requestStackClear();
      requestStackPush( States::MENU );
      break;

    case core::to_integral(MenuOption::EXIT):
      requestStackClear();
      break;

    default:
      break;
  } 

  return false;
}

///////////////////////////////////////////////////////////////////////////////

bool PauseState::update( const sf::Time dt )
{
  return false;
}

///////////////////////////////////////////////////////////////////////////////

void PauseState::render()
{
  sf::RenderWindow& window = *getContext()->window;
  window.setView( window.getDefaultView() );

  window.draw( mBackgroundShape );
  window.draw( mPauseText );
  window.draw( mMenu );
}

// end public interface
///////////////////////////////////////////////////////////////////////////////
