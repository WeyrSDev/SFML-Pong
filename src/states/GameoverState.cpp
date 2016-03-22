#include "GameoverState.hpp"
#include <game/DataTables.hpp>
#include <engine/Context.hpp>
#include <game/Blackboard.hpp>
#include <game/ResourceIdentifiers.hpp>
#include <engine/ResourceCache.hpp>
#include <engine/Utility.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

///////////////////////////////////////////////////////////////////////////////

namespace
{
const GameoverStateStringData Strings = initGameoverStrings();
}

///////////////////////////////////////////////////////////////////////////////

GameoverState::GameoverState( core::StateStack& stack, States id )
  : State( stack, id )
  , mMenu( getContext()->fonts->get( Fonts::C64 ), 30u, 15u,
           getContext()->blackboard->keyEventType )
  , mDrawObjects()
{
  auto winSize = sf::Vector2f{ static_cast<float>( getContext()->window->getSize().x ),
                               static_cast<float>( getContext()->window->getSize().y ) };

  mMenu.setHighlightColor( sf::Color::Green );
  mMenu.add( Strings.play );
  mMenu.add( Strings.menu );
  mMenu.add( Strings.exit );
  core::centerOrigin( mMenu );
  mMenu.setPosition( winSize / 2.f );

  std::string textLine1;
  std::string textLine2;
  sf::Color backColor;

  if( getContext()->blackboard->playerWon ) {
    textLine1 = { Strings.line1Won };
    textLine2 = { Strings.line2Won };
    backColor = { 0, 150, 0, 150 };
  } else {
    textLine1 = { Strings.line1Lost };
    textLine2 = { Strings.line2Lost };
    backColor = { 150, 0, 0, 150 };
  }

  auto background = std::make_unique<sf::RectangleShape>( winSize );
  background->setFillColor( backColor );
  

  auto text1 = std::make_unique<sf::Text>
    ( textLine1, getContext()->fonts->get( Fonts::C64 ) );
  core::centerOrigin( *text1 );
  text1->setPosition( winSize.x / 2.f, 75.f );
  

  auto text2 = std::make_unique<sf::Text>
    ( textLine2, getContext()->fonts->get( Fonts::C64 ) );
  core::centerOrigin( *text2 );
  text2->setPosition( text1->getPosition() +
                      sf::Vector2f( 0.f, text1->getCharacterSize() + 10.f ) );  

  mDrawObjects.push_back( std::move( background ) );
  mDrawObjects.push_back( std::move( text1 ) );
  mDrawObjects.push_back( std::move( text2 ) );
}

///////////////////////////////////////////////////////////////////////////////

bool GameoverState::handleInput( const sf::Event& event )
{
  int menuResult = mMenu.handleInput( event );
  switch( menuResult ) {
    case core::to_integral( MenuOption::PLAY):
      requestStackClear();
      requestStackPush( States::GAME );
      break;

    case core::to_integral(MenuOption::MENU):
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

bool GameoverState::update( const sf::Time dt )
{
  return false;
}

///////////////////////////////////////////////////////////////////////////////

void GameoverState::render()
{
  sf::RenderWindow& window = *getContext()->window;
  for( const auto& drawObject : mDrawObjects ) {
    window.draw( *drawObject );
  }
  window.draw( mMenu );  
}

// end public interface
///////////////////////////////////////////////////////////////////////////////