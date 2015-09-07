#include <pong/GameState.hpp>
#include <pong/StateStack.hpp>

GameState::GameState( StateStack& stack )
  : State( stack )
  , mWorld( *stack.getContext() )
{}

bool GameState::handleInput( const sf::Event& event )
{
  mWorld.handleInput( event );
  return true;
}

bool GameState::update( const sf::Time dt )
{
  mWorld.update( dt );
  return true;
}

void GameState::render()
{
  mWorld.render();
}