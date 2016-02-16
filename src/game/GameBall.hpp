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
  explicit GameBall( core::Context context );
  void setColor( const sf::Color& color ) override;
  sf::FloatRect getLocalBounds() const override;
  sf::FloatRect getGlobalBounds() const override;

private:
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

  const core::Context* mContext;
  sf::Sprite mSprite;
};

#endif