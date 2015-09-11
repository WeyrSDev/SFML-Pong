#include <pong/TitleState.hpp>
#include <pong/Context.hpp>
#include <pong/ResourceCache.hpp>
#include <pong/Utility.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

TitleState::TitleState( StateStack& stack )
  : State( stack )
  , mBackgroundSprite()
  , mTitle()
  , mText()
  , mShowText( false )
  , mTextEffectTime( sf::seconds( 1.f ) )
  , mFrameTime( sf::Time::Zero )
{
  const auto& font = getContext()->fonts->get( Fonts::GREENSCREEN );

  mBackgroundSprite.setTexture( getContext()->textures->get( Textures::TITLE_BG ) );
  
  mTitle.setFont( font );
  mTitle.setString( "P O N G" );
  mTitle.setCharacterSize( 50u );
  mTitle.setColor( sf::Color::Green );
  util::centerOrigin( mTitle );
  auto center = getContext()->window->getSize() / 2u;
  mTitle.setPosition( static_cast<float>( center.x ), 200.f );

  mText.setFont( font );
  mText.setString( "< Press any key to start >" );
  mText.setCharacterSize( 24u );
  mText.setColor( sf::Color::Green );
  util::centerOrigin( mText );
  mText.setPosition( static_cast<float>( center.x ), mTitle.getPosition().y + 100.f );
}

bool TitleState::handleInput( const sf::Event& event )
{
  if( event.type == sf::Event::KeyReleased ) {
    requestStackPop();
    requestStackPush( States::MENU );
  }
  return true;
}

bool TitleState::update( const sf::Time dt )
{
  mFrameTime += dt;
  if( mFrameTime > mTextEffectTime ) {
    mShowText = !mShowText;
    mFrameTime = sf::Time::Zero;
  }

  return true;
}

void TitleState::render()
{
  sf::RenderWindow& window = *getContext()->window;
  window.draw( mBackgroundSprite );
  window.draw( mTitle );
  if( mShowText ) {
    window.draw( mText );
  }
}