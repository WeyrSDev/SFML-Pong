#include "MenuState.hpp"
#include <engine/Context.hpp>
#include <engine/ResourceCache.hpp>
#include <engine/Utility.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

///////////////////////////////////////////////////////////////////////////////

MenuState::MenuState( StateStack& stack )
  : State( stack )
  , mBackgroundSprite()
  , mTitle()
  , mMenu( getContext()->fonts->get( Fonts::C64_Pixel ), 30u, 15u )
{
  const auto& font = getContext()->fonts->get( Fonts::C64_Pixel );
  auto winSize = getContext()->window->getView().getSize();

  mTitle.setFont( font );
  mTitle.setString( "P O N G" );
  mTitle.setCharacterSize( 80u );
  mTitle.setColor( sf::Color::Green );
  util::centerOrigin( mTitle );  
  mTitle.setPosition( winSize.x / 2.f, 100.f );

  mMenu.setHighlightColor( sf::Color::Green );
  mMenu.add( "PLAY" );
  mMenu.add( "OPTIONS" );
  mMenu.add( "CREDITS" );
  mMenu.add( "EXIT" );
  util::centerOrigin( mMenu );
  mMenu.setPosition( winSize / 2.f );

  mBackgroundSprite.setTexture( getContext()->textures
                                ->get( Textures::TITLE_BG ) );
}

///////////////////////////////////////////////////////////////////////////////

bool MenuState::handleInput( const sf::Event& event )
{
  int menuResult = mMenu.handleInput( event );
  switch( menuResult ) {
    case util::to_integral( MenuOption::PLAY ):
      requestStackPop();
      requestStackPush( States::GAME );
      break;

    case util::to_integral( MenuOption::OPTIONS):
      // nothing happens here now
      break;

    case util::to_integral( MenuOption::CREDITS):
      // nothing happens here now
      break;

    case util::to_integral( MenuOption::EXIT ):
      requestStackClear();
      break;

    default:
      break;
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////

bool MenuState::update( const sf::Time dt )
{
  mMenu.update( dt );
  return true;
}

///////////////////////////////////////////////////////////////////////////////

void MenuState::render()
{
  sf::RenderWindow& window = *getContext()->window;
  window.setView( window.getDefaultView() );
  
  window.draw( mBackgroundSprite );
  window.draw( mTitle );
  window.draw( mMenu );
}

// end public interface
///////////////////////////////////////////////////////////////////////////////