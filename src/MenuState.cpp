#include <pong/MenuState.hpp>
#include <pong/Context.hpp>
#include <pong/ResourceIdentifiers.hpp>
#include <pong/ResourceCache.hpp>
#include <pong/Utility.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

MenuState::MenuState( StateStack& stack )
  : State( stack )
  , mOptions()
  , mOptionsIndex( 0 )
{
  const auto& font = getContext()->fonts->get( Fonts::GREENSCREEN );
  sf::Text playOption;
  playOption.setFont( font );
  playOption.setString( "PLAY" );
  util::centerOrigin( playOption );
  playOption.setPosition( getContext()->window->getView().getSize() / 2.f - sf::Vector2f( 0.f, 20.f ) );
  mOptions.push_back( playOption );

  sf::Text exitOption;
  exitOption.setFont( font );
  exitOption.setString( "EXIT" );
  util::centerOrigin( exitOption );
  exitOption.setPosition( playOption.getPosition() + sf::Vector2f( 0.f, 40.f ) );
  mOptions.push_back( exitOption );

  updateMenuText();
}

bool MenuState::handleInput( const sf::Event& event )
{
  if( event.type == sf::Event::KeyReleased ) {
    if( event.key.code == sf::Keyboard::Return ) {
      if( mOptionsIndex == static_cast<std::size_t>( MenuOptions::PLAY ) ) {
        requestStackPop();
        requestStackPush( States::GAME );
      } else if( mOptionsIndex == static_cast<std::size_t>( MenuOptions::EXIT ) ) {
        requestStackClear();
      }
    }
    if( event.key.code == sf::Keyboard::Up ) {
      if( mOptionsIndex > 0 ) {
        --mOptionsIndex;
      } else {
        mOptionsIndex = mOptions.size() - 1;
      }

      updateMenuText();
    }
    if( event.key.code == sf::Keyboard::Down ) {
      if( mOptionsIndex < mOptions.size() - 1 ) {
        ++mOptionsIndex;
      } else {
        mOptionsIndex = 0;
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
  for( const auto& option : mOptions ) {
    window.draw( option );
  }
}

// end public interface

void MenuState::updateMenuText()
{
  if( mOptions.empty() ) {
    return;
  }

  for( auto& option : mOptions ) {
    option.setColor( sf::Color::White );
  }

  mOptions[ mOptionsIndex ].setColor( sf::Color::Green );
}