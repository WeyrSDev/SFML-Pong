#ifndef TITLESTATE_HPP
#define TITLESTATE_HPP

#include <engine/State.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <memory>

class TitleState : public core::State
{
public:
               TitleState( core::StateStack& stack, States id );

  virtual bool handleInput( const sf::Event& event ) override;
  virtual bool update( sf::Time dt ) override;
  virtual void render() override;

private:
  sf::Text     mStartText;
  float        mTextEffectTime;
  sf::Time     mFrameTime;
  std::vector<std::unique_ptr<sf::Drawable>> mDrawObjects;
};

#endif