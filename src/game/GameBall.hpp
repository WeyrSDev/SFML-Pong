#ifndef GAMEBALL_HPP
#define GAMEBALL_HPP

#include <engine/Entity.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace core
{
struct Context;
}

class GameBall : public core::Entity
{
public:
  explicit GameBall( core::Context* context );
  void setColor( const sf::Color& color );
  virtual sf::FloatRect getLocalBounds() const override;
  virtual sf::FloatRect getGlobalBounds() const override;

private:
  virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const override;

  sf::Sprite mSprite;
};

#endif