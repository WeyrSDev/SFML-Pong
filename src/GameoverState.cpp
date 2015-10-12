#include <pong/GameoverState.hpp>
#include <pong/Context.hpp>
#include <pong/ResourceCache.hpp>
#include <pong/Utility.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

GameoverState::GameoverState( StateStack& stack )
  : State( stack )
  , mBackgroundSprite()
  , mGameoverText()
  , mMenuOptions()
  , mMenuIndex( 0 )
{
  mBackgroundSprite.setTexture( getContext()->textures->get( Textures::TITLE_BG ) );
  auto winSize = sf::Vector2f{ static_cast<float>( getContext()->window->getSize().x ),
                               static_cast<float>( getContext()->window->getSize().y ) };

  mGameoverText.setFont( getContext()->fonts->get( Fonts::SDS_8BIT ) );
  if( getContext()->blackboard->playerWon ) {
    mGameoverText.setString( "CONGRATULATIONS,\nYOU HAVE WON!" );
  } else {
    mGameoverText.setString( "SORRY, YOU HAVE LOST!" );
  }
  util::centerOrigin( mGameoverText );
  mGameoverText.setPosition( winSize.x / 2.f, 60.f );
  
  const auto& font = getContext()->fonts->get( Fonts::SDS_8BIT );

  sf::Text playOption( "PLAY AGAIN", font );
  util::centerOrigin( playOption );
  playOption.setPosition( winSize / 2.f - sf::Vector2f( 0.f, 20.f ) );
  mMenuOptions.push_back( playOption );

  sf::Text exitOption( "EXIT TO MENU", font );
  util::centerOrigin( exitOption );
  exitOption.setPosition( playOption.getPosition() + sf::Vector2f( 0.f, 40.f ) );
  mMenuOptions.push_back( exitOption );

  sf::Text quitOption( "EXIT GAME", font );
  util::centerOrigin( quitOption );
  quitOption.setPosition( exitOption.getPosition() + sf::Vector2f( 0.f, 40.f ) );
  mMenuOptions.push_back( quitOption );

  updateMenuText();
}

bool GameoverState::handleInput( const sf::Event& event )
{
  if( event.type == sf::Event::KeyReleased ) {
    if( event.key.code == sf::Keyboard::Return ) {
      if( mMenuIndex == static_cast<std::size_t>( MenuOptions::PLAY ) ) {
        requestStackPop();
        requestStackPush( States::GAME );
      } else if( mMenuIndex == static_cast<std::size_t>( MenuOptions::MENU ) ) {
        requestStackPop();
        requestStackPush( States::MENU );
      } else if( mMenuIndex == static_cast<std::size_t>( MenuOptions::EXIT ) ) {
        requestStackClear();
      }
    }
    if( event.key.code == sf::Keyboard::Up ) {
      if( mMenuIndex > 0 ) {
        --mMenuIndex;
      } else {
        mMenuIndex = mMenuOptions.size() - 1;
      }

      updateMenuText();
    }
    if( event.key.code == sf::Keyboard::Down ) {
      if( mMenuIndex < mMenuOptions.size() - 1 ) {
        ++mMenuIndex;
      } else {
        mMenuIndex = 0;
      }

      updateMenuText();
    }
  }
  return true;
}

bool GameoverState::update( const sf::Time dt )
{
  return true;
}

void GameoverState::render()
{
  sf::RenderWindow& window = *getContext()->window;
  window.draw( mBackgroundSprite );
  window.draw( mGameoverText );
  for( const auto& option : mMenuOptions ) {
    window.draw( option );
  }
}

// end public interface

void GameoverState::updateMenuText()
{
  if( mMenuOptions.empty() ) {
    return;
  }

  for( auto& option : mMenuOptions ) {
    option.setColor( sf::Color::White );
  }

  mMenuOptions[ mMenuIndex ].setColor( sf::Color::Green );
}