#ifndef TITLESTATE_HPP
#define TITLESTATE_HPP

#include "State.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class TitleState : public State
{
public:
  explicit     TitleState( StateStack& stack );

  virtual bool handleInput( const sf::Event& event ) override;
  virtual bool update( sf::Time dt ) override;
  virtual void render() override;

private:
  sf::Sprite   mBackgroundSprite;
  sf::Text     mTitle;
  sf::Text     mText;
  bool         mShowText;
  sf::Time     mTextEffectTime;
  sf::Time     mFrameTime;
};

#endif