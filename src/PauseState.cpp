#include <pong/PauseState.hpp>
#include <pong/Context.hpp>
#include <pong/ResourceCache.hpp>
#include <pong/Utility.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

PauseState::PauseState( StateStack& stack )
  : State( stack )
  , mBackgroundShape()
  , mPauseText()
  , mMenuOptions()
  , mMenuIndex( 0 )
{
  auto winSize = sf::Vector2f{ static_cast<float>( getContext()->window->getSize().x ),
                               static_cast<float>( getContext()->window->getSize().y ) };

  mBackgroundShape.setSize( winSize );
  mBackgroundShape.setFillColor( sf::Color{ 0, 0, 0, 150 } ); // half transparent black

  const auto& font = getContext()->fonts->get( Fonts::SDS_8BIT );

  mPauseText.setFont( font );
  mPauseText.setString( "GAME PAUSED" );
  mPauseText.setColor( sf::Color::Green );
  util::centerOrigin( mPauseText );
  mPauseText.setPosition( winSize.x / 2.f, 75.f );

  sf::Text resumeOption( "RESUME GAME", font );
  util::centerOrigin( resumeOption );
  resumeOption.setPosition( winSize.x / 2.f, winSize.y / 2.f - 20.f );
  mMenuOptions.push_back( resumeOption );

  sf::Text exitOption( "EXIT TO MENU", font );
  util::centerOrigin( exitOption );
  exitOption.setPosition( resumeOption.getPosition() + sf::Vector2f( 0.f, 40.f ) );
  mMenuOptions.push_back( exitOption );

  updateMenuText();
}

bool PauseState::handleInput( const sf::Event& event )
{
  if( event.type == sf::Event::KeyReleased ) {
    if( event.key.code == sf::Keyboard::Escape ) {
      requestStackPop();
    }

    if( event.key.code == sf::Keyboard::Return ) {
      if( mMenuIndex == static_cast<std::size_t>( MenuOptions::RESUME ) ) {
        requestStackPop();
      }
      if( mMenuIndex == static_cast<std::size_t>( MenuOptions::EXIT ) ) {
        requestStackClear();
        requestStackPush( States::MENU );
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

  return false;
}


bool PauseState::update( const sf::Time dt )
{

  return false;
}

void PauseState::render()
{
  sf::RenderWindow& window = *getContext()->window;
  window.setView( window.getDefaultView() );

  window.draw( mBackgroundShape );
  window.draw( mPauseText );
  for( const auto& option : mMenuOptions ) {
    window.draw( option );
  }
}

// end public interface

void PauseState::updateMenuText()
{
  if( mMenuOptions.empty() ) {
    return;
  }

  for( auto& option : mMenuOptions ) {
    option.setColor( sf::Color::White );
  }

  mMenuOptions[ mMenuIndex ].setColor( sf::Color::Green );
}