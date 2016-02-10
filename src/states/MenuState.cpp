#include "MenuState.hpp"
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

MenuState::MenuState( core::StateStack& stack, States id )
  : State( stack, id )
  , mMenu( getContext()->fonts->get( Fonts::SDS_8BIT ), 30u, 15u,
           getContext()->blackboard->keyEventType )
  , mDrawObjects()
{
  const auto& font = getContext()->fonts->get( Fonts::C64_Pixel );
  auto winSize = getContext()->window->getView().getSize();

  auto bgSprite = std::make_unique<sf::Sprite>
    ( getContext()->textures->get( Textures::TITLE_BG ) );
  mDrawObjects.push_back( std::move( bgSprite ) );

  auto title = std::make_unique<sf::Text>( "P O N G", font, 100u );
  title->setColor( sf::Color::Green );
  core::centerOrigin( *title );
  title->setPosition( winSize.x / 2.f, 100.f );
  mDrawObjects.push_back( std::move( title ) );

  auto nameText = std::make_unique<sf::Text>
    ( "created by Sebastian 'SeriousITGuy' Brack",
      getContext()->fonts->get( Fonts::DP_COMIC ), 24u );
  core::centerOrigin( *nameText );
  nameText->setPosition( winSize.x / 2.f, winSize.y - 30.f );
  mDrawObjects.push_back( std::move( nameText ) );

  mMenu.setHighlightColor( sf::Color::Green );
  mMenu.add( "PLAY" );
  mMenu.add( "OPTIONS" );
  mMenu.add( "CREDITS" );
  mMenu.add( "EXIT" );
  core::centerOrigin( mMenu );
  mMenu.setPosition( winSize / 2.f );

  // simple implementation of drawing AABB for menu
  //auto menuBackdrop = std::make_unique<sf::RectangleShape>
  //  ( core::getSize( mMenu.getLocalBounds() ) + sf::Vector2f( 1.f, 1.f ) );
  //core::centerOrigin( *menuBackdrop );
  //menuBackdrop->setFillColor( sf::Color::Transparent );
  //menuBackdrop->setOutlineColor( sf::Color::Green );
  //menuBackdrop->setOutlineThickness( 2.f );
  //menuBackdrop->setPosition( winSize / 2.f );
  //mDrawObjects.push_back( std::move( menuBackdrop ) );
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