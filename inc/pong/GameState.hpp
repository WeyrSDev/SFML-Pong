#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"
#include "GameWorld.hpp"

class GameState : public State
{
public:
  explicit      GameState( StateStack& stack );
  virtual bool  handleInput( const sf::Event& event ) override;
  virtual bool  update( sf::Time dt ) override;
  virtual void  render() override;

private:
  GameWorld     mWorld;
};

#endif