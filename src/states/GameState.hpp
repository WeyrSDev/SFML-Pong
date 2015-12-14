#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <engine/State.hpp>
#include <game/GameWorld.hpp>

class GameState : public State
{
public:
                GameState( StateStack& stack, States id );
  virtual bool  handleInput( const sf::Event& event ) override;
  virtual bool  update( sf::Time dt ) override;
  virtual void  render() override;

private:
  GameWorld     mWorld;
};

#endif