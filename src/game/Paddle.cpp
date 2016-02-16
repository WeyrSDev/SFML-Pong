#include "Paddle.hpp"
#include "ResourceIdentifiers.hpp"
#include "Blackboard.hpp"
#include <engine/Context.hpp>
#include <engine/ResourceCache.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

///////////////////////////////////////////////////////////////////////////////

Paddle::Paddle( Type type, core::Context context )
  : mType( type )
  , mContext( &context )
  , mSprite()
{  
  sf::IntRect textureRect { 0,0,0,0 };
  if( mType == Type::Player ) {
    textureRect = sf::IntRect { 0,0,16,80 };
  } else if( mType == Type::Computer ) {
    textureRect = sf::IntRect { 16,0,16,80 };
  }
  mSprite.setTexture( mContext->textures->get( Textures::TILES ) );
  mSprite.setTextureRect( textureRect );
}

///////////////////////////////////////////////////////////////////////////////

void Paddle::setColor( const sf::Color & color )
{
  mSprite.setColor( color );
}

///////////////////////////////////////////////////////////////////////////////

sf::FloatRect Paddle::getLocalBounds() const
{
  return mSprite.getLocalBounds();
}

///////////////////////////////////////////////////////////////////////////////

sf::FloatRect Paddle::getGlobalBounds() const
{
  return getTransform().transformRect( getLocalBounds() );
}

///////////////////////////////////////////////////////////////////////////////

void Paddle::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  states.transform *= getTransform();
  target.draw( mSprite, states );
}

///////////////////////////////////////////////////////////////////////////////