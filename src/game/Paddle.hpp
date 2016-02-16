#ifndef GAME_PADDLE_HPP
#define GAME_PADDLE_HPP

#include <engine/Entity.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace core
{
struct Context;
}

class Paddle : public core::Entity
{
public:
  enum class Type : unsigned short
  {
    Player,
    Computer,
  };

  Paddle( Type type, core::Context context );
  void setColor( const sf::Color& color ) override;
  sf::FloatRect getLocalBounds() const override;
  sf::FloatRect getGlobalBounds() const override;

private:
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

  Type mType;
  const core::Context* mContext;
  sf::Sprite mSprite;  
};


#endif