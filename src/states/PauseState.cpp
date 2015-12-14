#include "PauseState.hpp"
#include <engine/Context.hpp>
#include <engine/ResourceCache.hpp>
#include <engine/Utility.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

///////////////////////////////////////////////////////////////////////////////

PauseState::PauseState( StateStack& stack, States id )
  : State( stack, id )
  , mBackgroundShape()
  , mPauseText()
  , mMenu( getContext()->fonts->get( Fonts::C64_Pixel ), 30u, 15u,
           getContext()->blackboard->keyEventType )
{
  auto winSize = sf::Vector2f{ static_cast<float>( getContext()->
                                                   window->getSize().x ),
                               static_cast<float>( getContext()->
                                                   window->getSize().y ) };

  // make background whole screen and half transparent black
  mBackgroundShape.setSize( winSize );  
  mBackgroundShape.setFillColor( { 0, 0, 0, 150 } ); 

  const auto& font = getContext()->fonts->get( Fonts::C64_Pixel );

  mPauseText.setFont( font );
  mPauseText.setCharacterSize( 40u );
  mPauseText.setString( "GAME PAUSED" );
  mPauseText.setColor( sf::Color::Green );
  util::centerOrigin( mPauseText );
  mPauseText.setPosition( winSize.x / 2.f, 75.f );

  mMenu.setHighlightColor( sf::Color::Green );
  mMenu.add( "RESUME GAME" );
  mMenu.add( "EXIT TO MENU" );
  util::centerOrigin( mMenu );
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
    case util::to_integral(MenuOption::RESUME):
      requestStackPop();
      break;

    case util::to_integral(MenuOption::EXIT):
      requestStackClear();
      requestStackPush( States::MENU );
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