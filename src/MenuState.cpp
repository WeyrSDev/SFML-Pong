#include <pong/MenuState.hpp>
#include <pong/Context.hpp>
#include <pong/ResourceIdentifiers.hpp>
#include <pong/ResourceCache.hpp>
#include <pong/Utility.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

MenuState::MenuState( StateStack& stack )
  : State( stack )
  , mBackgroundSprite()
  , mTitle()
  , mMenuOptions()
  , mMenuIndex( 0 )
{
  const auto& font = getContext()->fonts->get( Fonts::SDS_8BIT );
  auto winSize = getContext()->window->getView().getSize();

  mTitle.setFont( font );
  mTitle.setString( "P O N G" );
  mTitle.setCharacterSize( 80u );
  mTitle.setColor( sf::Color::Green );
  util::centerOrigin( mTitle );  
  mTitle.setPosition( winSize.x / 2.f, 100.f );

  sf::Text playOption( "PLAY", font );
  util::centerOrigin( playOption );
  playOption.setPosition( winSize / 2.f - sf::Vector2f( 0.f, 75.f ) );
  mMenuOptions.push_back( playOption );

  sf::Text settingsOption( "SETTINGS", font );
  util::centerOrigin( settingsOption );
  settingsOption.setPosition( playOption.getPosition() + sf::Vector2f( 0.f, 40.f ) );
  mMenuOptions.push_back( settingsOption );

  sf::Text creditsOption( "CREDITS", font );
  util::centerOrigin( creditsOption );
  creditsOption.setPosition( settingsOption.getPosition() + sf::Vector2f( 0.f, 40.f ) );
  mMenuOptions.push_back( creditsOption );

  sf::Text exitOption("EXIT", font);
  util::centerOrigin( exitOption );
  exitOption.setPosition( creditsOption.getPosition() + sf::Vector2f( 0.f, 40.f ) );
  mMenuOptions.push_back( exitOption );

  mBackgroundSprite.setTexture( getContext()->textures->get( Textures::TITLE_BG ) );

  updateMenuText();
}

bool MenuState::handleInput( const sf::Event& event )
{
  if( event.type == sf::Event::KeyReleased ) {
    if( event.key.code == sf::Keyboard::Return ) {
      if( mMenuIndex == static_cast<std::size_t>( MenuOptions::PLAY ) ) {
        requestStackPop();
        requestStackPush( States::GAME );
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

bool MenuState::update( const sf::Time dt )
{
  return true;
}

void MenuState::render()
{
  sf::RenderWindow& window = *getContext()->window;
  window.setView( window.getDefaultView() );
  
  window.draw( mBackgroundSprite );
  window.draw( mTitle );

  for( const auto& option : mMenuOptions ) {
    window.draw( option );
  }
}

// end public interface

void MenuState::updateMenuText()
{
  if( mMenuOptions.empty() ) {
    return;
  }

  for( auto& option : mMenuOptions ) {
    option.setColor( sf::Color::White );
  }

  mMenuOptions[ mMenuIndex ].setColor( sf::Color::Green );
}