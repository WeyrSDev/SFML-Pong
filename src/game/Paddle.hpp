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

  Paddle( Type type, core::Context* context );
  void setColor( const sf::Color& color );
  void setSpeed( float speed );
  float getSpeed() const;
  float getBaseSpeed() const;
  virtual sf::FloatRect getLocalBounds() const override;
  virtual sf::FloatRect getGlobalBounds() const override;

private:
  virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const override;

  Type mType;
  sf::Sprite mSprite;
  float mBaseSpeed;
  float mCurrentSpeed;
};


#endif