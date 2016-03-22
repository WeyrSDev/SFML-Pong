#include "Entity.hpp"
#include "Context.hpp"
#include "Utility.hpp"
#include <game/ResourceIdentifiers.hpp>
#include "ResourceCache.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

///////////////////////////////////////////////////////////////////////////////

namespace core
{
Entity::Entity( core::Context* context )
  : mContext( context )
  , mDebugDraw( false )
  , mVelocity( sf::Vector2f( 0.f, 0.f ) )
{}

void Entity::update( const sf::Time& dt )
{
  if( mVelocity != sf::Vector2f( 0.f, 0.f ) ) {
    move( mVelocity );
  }
}

sf::FloatRect Entity::getLocalBounds() const
{
  return sf::FloatRect();
}

sf::FloatRect Entity::getGlobalBounds() const
{
  return sf::FloatRect();
}

void Entity::setDebugDraw( bool debugDraw )
{
  mDebugDraw = debugDraw;
}

void Entity::setVelocity( sf::Vector2f velocity )
{
  mVelocity = velocity;
}

sf::Vector2f Entity::getVelocity() const
{
  return mVelocity;
}

void Entity::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
  states.transform *= getTransform();
  drawCurrent( target, states );
  if( mDebugDraw ) {
    drawDebug( target, states );
  }
}

void Entity::drawCurrent( sf::RenderTarget & target, sf::RenderStates states ) const
{
  // Entity does not draw itself, there is no visual representation
}

void Entity::drawDebug( sf::RenderTarget & target, sf::RenderStates states ) const
{
  const auto rect = getGlobalBounds();

  sf::RectangleShape shape;
  shape.setSize( core::getSize( rect ) );
  shape.setPosition( core::getPosition( rect ) );
  shape.setFillColor( sf::Color::Transparent );
  shape.setOutlineColor( sf::Color{ 255,0,255,255 } );
  shape.setOutlineThickness( 1.f );

  sf::Text posText;
  posText.setFont( mContext->fonts->get( Fonts::MONOSPACE ) );
  posText.setString( floatToString( rect.left ) + ", " + floatToString( rect.top ) );
  posText.setCharacterSize( 8u );
  posText.setOrigin( 0.f, posText.getLocalBounds().height );
  posText.setPosition( rect.left, rect.top - 5.f );

  sf::Text orgText;
  orgText.setFont( mContext->fonts->get( Fonts::MONOSPACE ) );
  orgText.setString( floatToString( rect.left + rect.width / 2.f ) + ", " + floatToString( rect.top + rect.height / 2.f ) );
  orgText.setCharacterSize( 8u );
  orgText.setOrigin( 0.f, orgText.getLocalBounds().height / 2.f );
  orgText.setPosition( rect.left + rect.width + 5.f, rect.top + rect.height / 2.f );


  target.draw( shape );
  target.draw( posText );
  target.draw( orgText );
}

} // end namespace core