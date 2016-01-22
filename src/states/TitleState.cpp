#include "TitleState.hpp"
#include <engine/Context.hpp>
#include <game/Blackboard.hpp>
#include <engine/ResourceCache.hpp>
#include <engine/Utility.hpp>
#include <engine/LogSystem.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////

TitleState::TitleState( core::StateStack& stack, States id )
  : State( stack, id )
  , mStartText()
  , mShowText( true )
  , mTextEffectTime( sf::seconds( 0.66f ) )
  , mFrameTime( sf::Time::Zero )
  , mDrawObjects()
{
  const auto& font = getContext()->fonts->get( Fonts::C64_Pixel );
  auto winSize = getContext()->window->getView().getSize();

  mStartText.setFont( font );
  mStartText.setString( "< Press any key to start >" );
  mStartText.setCharacterSize( 24u );
  mStartText.setColor( sf::Color::Green );
  core::centerOrigin( mStartText );
  mStartText.setPosition( winSize / 2.f );

  auto bgSprite = std::make_unique<sf::Sprite>
    ( getContext()->textures->get( Textures::TITLE_BG ) );
  mDrawObjects.push_back( std::move( bgSprite ) );
    
  auto title = std::make_unique<sf::Text>
    ( "P O N G", font, 100u );
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
}

///////////////////////////////////////////////////////////////////////////////

bool TitleState::handleInput( const sf::Event& event )
{
  if( event.type == getContext()->blackboard->keyEventType ) {
    //getContext()->log->write( "TitleState::handleInput - event received", core::LogType::DEBUG );
    requestStackPop();
    requestStackPush( States::MENU );
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////

bool TitleState::update( const sf::Time dt )
{
  mFrameTime += dt;
  if( mFrameTime > mTextEffectTime ) {
    mShowText = !mShowText;
    mFrameTime = sf::Time::Zero;
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////

void TitleState::render()
{
  sf::RenderWindow& window = *getContext()->window;
  for( const auto& drawObject : mDrawObjects ) {
    window.draw( *drawObject );
  }  
  if( mShowText ) {
    window.draw( mStartText );
  }
}

///////////////////////////////////////////////////////////////////////////////