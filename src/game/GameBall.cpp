#include "GameBall.hpp"
#include "ResourceIdentifiers.hpp"
#include "Blackboard.hpp"
#include <engine/Context.hpp>
#include <engine/ResourceCache.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

///////////////////////////////////////////////////////////////////////////////

GameBall::GameBall( core::Context* context )
  : core::Entity{ context }
  , mSprite{}
{
  mSprite.setTexture( mContext->textures->get(Textures::TILES) );
  mSprite.setTextureRect( sf::IntRect { 32,0,16,16 } );
}

///////////////////////////////////////////////////////////////////////////////

void GameBall::setColor( const sf::Color& color )
{
  mSprite.setColor( color );
}

///////////////////////////////////////////////////////////////////////////////

sf::FloatRect GameBall::getLocalBounds() const
{
  return mSprite.getLocalBounds();
}

///////////////////////////////////////////////////////////////////////////////

sf::FloatRect GameBall::getGlobalBounds() const
{
  return getTransform().transformRect( getLocalBounds() );
}

///////////////////////////////////////////////////////////////////////////////

void GameBall::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const
{  
  target.draw( mSprite, states );
}

///////////////////////////////////////////////////////////////////////////////