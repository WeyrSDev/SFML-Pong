#include "GameoverState.hpp"
#include <engine/Context.hpp>
#include <game/Blackboard.hpp>
#include <engine/ResourceCache.hpp>
#include <engine/Utility.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

///////////////////////////////////////////////////////////////////////////////

GameoverState::GameoverState( core::StateStack& stack, States id )
  : State( stack, id )
  , mBackgroundSprite()
  , mGameoverText()
  , mMenu( getContext()->fonts->get( Fonts::C64_Pixel ), 30u, 15u,
           getContext()->blackboard->keyEventType )
{
  mBackgroundSprite.setTexture( getContext()->textures->get( Textures::TITLE_BG ) );
  auto winSize = sf::Vector2f{ static_cast<float>( getContext()->window->getSize().x ),
                               static_cast<float>( getContext()->window->getSize().y ) };

  mGameoverText.setFont( getContext()->fonts->get( Fonts::C64_Pixel ) );
  if( getContext()->blackboard->playerWon ) {
    mGameoverText.setString( "CONGRATULATIONS,\nYOU HAVE WON!" );
  } else {
    mGameoverText.setString( "SORRY, YOU HAVE LOST!" );
  }
  core::centerOrigin( mGameoverText );
  mGameoverText.setPosition( winSize.x / 2.f, 60.f );

  mMenu.setHighlightColor( sf::Color::Green );
  mMenu.add( "PLAY AGAIN" );
  mMenu.add( "EXIT TO MENU" );
  mMenu.add( "EXIT GAME" );
  core::centerOrigin( mMenu );
  mMenu.setPosition( winSize / 2.f );
}

///////////////////////////////////////////////////////////////////////////////

bool GameoverState::handleInput( const sf::Event& event )
{
  int menuResult = mMenu.handleInput( event );
  switch( menuResult ) {
    case core::to_integral( MenuOption::PLAY):
      requestStackPop();
      requestStackPush( States::GAME );
      break;

    case core::to_integral(MenuOption::MENU):
      requestStackPop();
      requestStackPush( States::MENU );
      break;

    case core::to_integral(MenuOption::EXIT):
      requestStackClear();
      break;

    default:
      break;
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////

bool GameoverState::update( const sf::Time dt )
{
  return true;
}

///////////////////////////////////////////////////////////////////////////////

void GameoverState::render()
{
  sf::RenderWindow& window = *getContext()->window;
  window.draw( mBackgroundSprite );
  window.draw( mGameoverText );
  window.draw( mMenu );
}

// end public interface
///////////////////////////////////////////////////////////////////////////////