#include "MenuState.hpp"
#include <game/DataTables.hpp>
#include <engine/Context.hpp>
#include <game/Blackboard.hpp>
#include <game/ResourceIdentifiers.hpp>
#include <engine/ResourceCache.hpp>
#include <engine/Utility.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

///////////////////////////////////////////////////////////////////////////////

namespace
{
const MenuStateStringData Strings = initMenuStrings();
}

///////////////////////////////////////////////////////////////////////////////

MenuState::MenuState( core::StateStack& stack, States id )
  : State( stack, id )
  , mMenu( getContext()->fonts->get( Fonts::C64 ), 32u, 16u,
           getContext()->blackboard->keyEventType )
  , mDrawObjects()
{
  const auto& font = getContext()->fonts->get( Fonts::C64 );
  auto winSize = getContext()->window->getView().getSize();

  auto bgSprite = std::make_unique<sf::Sprite>
    ( getContext()->textures->get( Textures::TITLE_BG ) );
  mDrawObjects.push_back( std::move( bgSprite ) );

  auto title = std::make_unique<sf::Text>( Strings.title, font, 96u );
  title->setColor( sf::Color::Green );
  core::centerOrigin( *title );
  title->setPosition( winSize.x / 2.f, 100.f );
  mDrawObjects.push_back( std::move( title ) );

  auto nameText = std::make_unique<sf::Text>
    ( Strings.creator, getContext()->fonts->get( Fonts::COMIC ), 24u );
  core::centerOrigin( *nameText );
  nameText->setPosition( winSize.x / 2.f, winSize.y - 30.f );
  mDrawObjects.push_back( std::move( nameText ) );

  mMenu.setHighlightColor( sf::Color::Green );
  mMenu.add( Strings.play );
  mMenu.add( Strings.options );
  mMenu.add( Strings.credits );
  mMenu.add( Strings.exit );
  core::centerOrigin( mMenu );
  mMenu.setPosition( winSize / 2.f );
}

///////////////////////////////////////////////////////////////////////////////

bool MenuState::handleInput( const sf::Event& event )
{
  // forward input to menu and get selected result
  int menuResult = mMenu.handleInput( event );

  switch( menuResult ) {
    case core::to_integral( MenuOption::PLAY ):
      requestStackPop();
      requestStackPush( States::GAME );
      break;

    case core::to_integral( MenuOption::OPTIONS ):
      // nothing happens here now
      break;

    case core::to_integral( MenuOption::CREDITS ):
      requestStackPush( States::CREDITS );
      break;

    case core::to_integral( MenuOption::EXIT ):
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
  
  for( const auto& drawObject : mDrawObjects ) {
    window.draw( *drawObject );
  }
  window.draw( mMenu );
}

// end public interface
///////////////////////////////////////////////////////////////////////////////