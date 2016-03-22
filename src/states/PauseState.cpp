#include "PauseState.hpp"
#include <game/DataTables.hpp>
#include <engine/Context.hpp>
#include <game/Blackboard.hpp>
#include <game/ResourceIdentifiers.hpp>
#include <engine/ResourceCache.hpp>
#include <engine/Utility.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

///////////////////////////////////////////////////////////////////////////////

namespace
{
const PauseStateStringData Strings = initPauseStrings();
}

///////////////////////////////////////////////////////////////////////////////

PauseState::PauseState( core::StateStack& stack, States id )
  : State( stack, id )
  , mBackgroundShape()
  , mPauseText()
  , mMenu( getContext()->fonts->get( Fonts::C64 ), 30u, 15u,
           getContext()->blackboard->keyEventType )
{
  auto winSize = getContext()->window->getView().getSize();

  // make background whole screen and half transparent black
  mBackgroundShape.setSize( winSize );  
  mBackgroundShape.setFillColor( { 0, 0, 0, 150 } ); 

  const auto& font = getContext()->fonts->get( Fonts::C64 );

  mPauseText.setFont( font );
  mPauseText.setCharacterSize( 40u );
  mPauseText.setString( Strings.pause );
  mPauseText.setColor( sf::Color::Green );
  core::centerOrigin( mPauseText );
  mPauseText.setPosition( winSize.x / 2.f, 75.f );

  mMenu.setHighlightColor( sf::Color::Green );
  mMenu.add( Strings.resume );
  mMenu.add( Strings.restart );
  mMenu.add( Strings.menu );
  mMenu.add( Strings.exit );
  core::centerOrigin( mMenu );
  mMenu.setPosition( winSize / 2.f );
}

///////////////////////////////////////////////////////////////////////////////

bool PauseState::handleInput( const sf::Event& event )
{
  if( event.type == getContext()->blackboard->keyEventType ) {
    if( event.key.code == sf::Keyboard::Escape ) {
      requestStackPop();
    }
  }

  int menuResult = mMenu.handleInput( event );
  switch( menuResult ) {
    case core::to_integral(MenuOption::RESUME):
      requestStackPop();
      break;

    case core::to_integral(MenuOption::RESTART):
      requestStackClear();
      requestStackPush( States::GAME );
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
