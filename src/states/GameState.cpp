#include "GameState.hpp"
#include <engine/StateStack.hpp>

GameState::GameState( StateStack& stack )
  : State( stack )
  , mWorld( *stack.getContext() )
{
  getContext()->blackboard->gameOver = false;
  getContext()->blackboard->playerWon = false;
}

bool GameState::handleInput( const sf::Event& event )
{
  mWorld.handleInput( event );
  if( event.type == sf::Event::KeyReleased ) {
    if( event.key.code == sf::Keyboard::Escape ) {
      requestStackPush( States::PAUSE );
    }
  }
  return true;
}

bool GameState::update( const sf::Time dt )
{
  mWorld.update( dt );
  if( getContext()->blackboard->gameOver ) {
    requestStackPop();
    requestStackPush( States::GAMEOVER );
  }

  return true;
}

void GameState::render()
{
  mWorld.render();
}