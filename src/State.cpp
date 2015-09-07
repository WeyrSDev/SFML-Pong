#include <pong/State.hpp>
#include <pong/StateStack.hpp>

State::State( StateStack& stack )
  :mStack( &stack )
{}

State::~State()
{}

void State::requestStackPush( States id )
{
  mStack->pushState( id );
}

void State::requestStackPop()
{
  mStack->popState();
}

void State::requestStackClear()
{
  mStack->clearStates();
}

Context* State::getContext() const
{
  return mStack->getContext();
}