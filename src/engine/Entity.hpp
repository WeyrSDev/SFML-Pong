#ifndef CORE_ENTITY_HPP
#define CORE_ENTITY_HPP

#include "Context.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

namespace core
{

// base class for game entities
class Entity : public sf::Drawable, public sf::Transformable
{
public:
  Entity( core::Context* context );
  virtual ~Entity() = default;
  virtual void update( const sf::Time& dt );
  virtual sf::FloatRect getLocalBounds() const;
  virtual sf::FloatRect getGlobalBounds() const;
  void setDebugDraw( bool debugDraw );
  void setVelocity( sf::Vector2f velocity );
  sf::Vector2f getVelocity() const;

protected:
  core::Context* mContext;
  bool mDebugDraw;
  sf::Vector2f mVelocity;

private:
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
  virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;
  void drawDebug( sf::RenderTarget& target, sf::RenderStates states ) const;
};

} // end namespace core

#endif