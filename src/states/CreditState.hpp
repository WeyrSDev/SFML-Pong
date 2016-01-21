#ifndef CREDIT_STATE_HPP
#define CREDIT_STATE_HPP
#include <engine/State.hpp>
#include <vector>
#include <memory>

namespace sf
{
  class Drawable;
}

class CreditState : public core::State
{
public:
               CreditState( core::StateStack& stack, States id );
  virtual bool handleInput( const sf::Event& event ) override;
  virtual bool update( sf::Time dt ) override;
  virtual void render() override;

private:
  std::vector<std::unique_ptr<sf::Drawable>> mDrawObjects;
};

#endif