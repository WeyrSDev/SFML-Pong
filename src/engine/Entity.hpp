#ifndef CORE_ENTITY_HPP
#define CORE_ENTITY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Color.hpp>

namespace core
{

// interface class for game entities
class Entity : public sf::Drawable, public sf::Transformable
{
public:
  virtual ~Entity() = default;
  virtual void setColor( const sf::Color& ) = 0;
  virtual sf::FloatRect getLocalBounds() const = 0;
  virtual sf::FloatRect getGlobalBounds() const = 0;
  
private:
  virtual void draw( sf::RenderTarget&, sf::RenderStates ) const = 0;
};

} // end namespace core

#endif