#include "GameState.hpp"
#include <engine/StateStack.hpp>
#include <game/Blackboard.hpp>

///////////////////////////////////////////////////////////////////////////////

GameState::GameState( core::StateStack& stack, States id )
  : State( stack, id )
  , mWorld( *stack.getContext() )
{
  getContext()->blackboard->gameOver = false;
  getContext()->blackboard->playerWon = false;
}

///////////////////////////////////////////////////////////////////////////////

bool GameState::handleInput( const sf::Event& event )
{
  mWorld.handleInput( event );

  if( event.type == getContext()->blackboard->keyEventType ) {
    if( event.key.code == sf::Keyboard::Escape ) {
      requestStackPush( States::PAUSE );
    }
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////

bool GameState::update( const sf::Time dt )
{
  mWorld.handleRealtimeInput();
  mWorld.update( dt );
  if( getContext()->blackboard->gameOver ) {
    requestStackPush( States::GAMEOVER );
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////

void GameState::render()
{
  mWorld.render();
}

///////////////////////////////////////////////////////////////////////////////